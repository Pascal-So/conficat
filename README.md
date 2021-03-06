# conficat - CONFIg file CAT

A utility for printing files to stdout, ignoring comment lines.

**Requires [argparse](https://github.com/Pascal-So/argparse)**

## Usage

Call `conficat` either with the input file as an argument, or reading from stdin.
```bash
cat apache2.conf | conficat -sri
conficat -rsi apache2.conf
```
The output for these two commands is equivalent.

```
Usage: conficat [INPUT FILE] [OPTIONS]

-r, --replace-comment    Replace a comment line by an empty line rather
                         than deleting the line
-c, --comment-string     Specify the string to use as comment sequence.
-i, --ignore-leading-ws  Ignore whitespace before the comment sequence.
-s                       Collapse whitespace blocks to a single line.
-e                       Don't print any whitespace lines.
    --help               Display this help message.
```

I usually call the tool with the flags `-rsi` set, which will always display a single empty line between non-comment lines that were not adjacent in the original file.