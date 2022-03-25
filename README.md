# mew

Cat ( unix tool ) implementation in pure C. 



## Help

full set of features
note :  wip and not all feature are implemented
```bash
Usage: mew [OPTION]... [FILE]...
Concatenate FILE(s) to standard output.

-f,                      file path 
-b, --number-nonblank    number nonempty output lines, overrides -n
-E, --show-ends          display $ at end of each line
-n, --number             number all output lines
-T, --show-tabs          display TAB characters as ^I
-i,                      show indentation markers
-h                      display this help and exit

```





### Feature available

- -h  ( usage)
- -b  ( total all line counts )
- -E  ( append $ at end)
- -n  ( line number )
- -f  ( file path )
- -i  ( show indentation )

#### Todo
- Refactoring
- FIXME
    - only single command working at the moment 
