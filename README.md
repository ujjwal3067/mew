# mew

Cat ( unix tool ) implementation in pure C. 








## Help

full set of features
note :  wip and not all feature are implemented
```bash
Usage: dcat [OPTION]... [FILE]...
Concatenate FILE(s) to standard output.

With no FILE, or when FILE is -, read standard input.

-l, --learn              learn and read offline documentation
-A, --show-all           equivalent to -vET
-b, --number-nonblank    number nonempty output lines, overrides -n
-e                       equivalent to -vE
-E, --show-ends          display $ at end of each line
-n, --number             number all output lines
-s, --squeeze-blank      suppress repeated empty output lines
-t                       equivalent to -vT
-T, --show-tabs          display TAB characters as ^I
-u                      (ignored)
-v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB
--help     display this help and exit
--version  output version information and exit

Examples:
dcat f - g  Output f's contents, then standard input, then g's contents.
dcat        Copy standard input to standard output.

Programming by Max Base
Full documentation at: <https://github.com/basemac/dca>
or available locally via: 'dcat --learn't
```





### Feature available
- --help

