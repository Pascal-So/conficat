# conficat - CONFIg file CAT

A utility for printing files to stdout, ignoring comment lines

## Usage

```
Usage: conficat [INPUT FILE] [OPTIONS]

-r, --replace-comment    Replace a comment line by an empty line rather
                         than deleting the line-c, --comment-string     Specify the string to use as comment sequence.
-i, --ignore-leading-ws  Ignore whitespace before the comment sequence.
-s                       Collapse whitespace blocks to a single line.
-e                       Don't print any whitespace lines.
    --help               Display this help message.
```
