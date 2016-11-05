#include<bits/stdc++.h>

#include "argparse.h"

using namespace std;

/*

  conficat - CONFIg file CAT

  A utility to print out the contents of a file to stdout, removing
  all the lines that start with the comment character.

  Pascal Sommer, November 2016

*/


// does this string consist entirely of whitespace? (tab, space)
bool string_is_whitespace(const string & s){
    for(auto c:s){
	if(!(c == ' ' ||
	     c == '\t'))
	    return false;
    }
    return true;
}

bool string_is_comment(const string & s,
		       const string & comment_string,
		       bool ignore_leading_whitespace)
{
    int pos = s.find(comment_string);
    if(pos != string::npos){
	if(ignore_leading_whitespace){
	    // check if string before match is whitespace
	    return string_is_whitespace(s.substr(0, pos));
	}else{
	    // check if match is the first thing in the line
	    return pos == 0;
	}
    }else{
	return false;
    }
}

void help_message(){
    cerr<<"conficat - CONFIg file CAT\n\n";
    
    cerr<<"A utility to print out the contents of a file to stdout, removing all\n";
    cerr<<"the lines that start with the comment character.\n\n";

    cerr<<"Usage: conficat [INPUT FILE] [OPTIONS]\n\n";
    cerr<<"-r, --replace-comment    Replace a comment line by an empty line rather\n";
    cerr<<"                         than deleting the line\n";
    cerr<<"-c, --comment-string     Specify the string to use as comment sequence.\n";
    cerr<<"-i, --ignore-leading-ws  Ignore whitespace before the comment sequence.\n";
    cerr<<"-s                       Collapse whitespace blocks to a single line.\n";
    cerr<<"-e                       Don't print any whitespace lines.\n";
    cerr<<"    --help               Display this help message.\n\n";

    cerr<<"Author: Pascal Sommer\n\n";
}

int main(int argc, char * argv[]){

    // parse options with argparse
    vector<option> argparse_options;

    // the input filename
    argparse_options.push_back({0, "", "", true}); 

    // replace comment line by empty line
    argparse_options.push_back({5, "r", "replace-comment", false});
    
    // the character used for commenting, default #
    argparse_options.push_back({1, "c", "comment-string", true});

    // if ignore_leading_whitespace is on, a line
    // starting with whitespace and then the comment
    // string will also be considered a comment
    argparse_options.push_back({2, "i", "ignore-leading-ws", false});

    // reduce blocks of empty lines to single line
    argparse_options.push_back({3, "s", "", false});

    // remove all empty lines (overwrites -s)
    argparse_options.push_back({4, "e", "", false});

    argparse_options.push_back({99, "", "help", false});
    
    auto parsed_options = argparse(argparse_options, argc, argv);

    // exit if argparse returned an error
    if(parsed_options.find(-1) != parsed_options.end()){
	help_message();
	return 1;
    }

    // display help message
    if(parsed_options.find(99) != parsed_options.end()){
	help_message();
	return 0;
    }


    // get values from options
    ifstream file_input;
    bool replace_comment = (parsed_options.find(5)!=parsed_options.end());
    string comment_string = "#";
    bool ignore_leading_whitespace = (parsed_options.find(2)!=parsed_options.end());
    bool ws_blocks_to_single = (parsed_options.find(3)!=parsed_options.end());
    bool ws_blocks_remove = (parsed_options.find(4)!=parsed_options.end());

    if(ws_blocks_remove) ws_blocks_to_single = false;
    
    // setup input stream
    bool read_from_stdin = (parsed_options.find(0) == parsed_options.end());
    if(!read_from_stdin){
	string filename = parsed_options[0];
	file_input.open(filename);
	if(!file_input){
	    cerr<< "Cannot open input file '"<<filename<<"'\n";
	    return 1;
	}
    }
    istream& input = read_from_stdin ? cin : file_input;
        
    // set comment character
    if(parsed_options.find(1)!=parsed_options.end()){
	comment_string = parsed_options[1];
    }

    // holds the current line
    string line;
    
    // was the last line pure whitespace?
    bool last_line_ws = true;
    while(getline(input, line)){
	// detect if line is a comment line
	bool is_comment = string_is_comment(line, comment_string, ignore_leading_whitespace);

	// do this if the option "replace comments by
	// empty line" is active. It's important to do
	// this here, so that the line will later be
	// recognized as a whitespace line and will be
	// handled by the whitespace options accordingly.
	if(is_comment && replace_comment){
	    is_comment = false;
	    line = "";
	}
	if(is_comment) continue;
	
	// detect if line is whitespace
	bool is_ws = false;
	if(ignore_leading_whitespace){
	    is_ws = string_is_whitespace(line);
	}else{
	    is_ws = (line == "");
	}

	// ignore current line if it is whitespace and
	// the args are set up to ignore all whitespace
	if(ws_blocks_remove && is_ws) continue;

	// ignore current line if current line and last
	// printed line are both whitespace and argument
	// reduce whitespace blocks to single whitespace
	// line is given
	if(ws_blocks_to_single && last_line_ws && is_ws) continue;
	
	cout<<line<<"\n";

	last_line_ws = is_ws;
    }
}
