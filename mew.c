#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

const char *usage = "Usage: mew [OPTION]... [FILE]...\n"
"Concatenate FILE(s) to standard output.\n"

"With no FILE, or when FILE is -, read standard input.\n"

"-l, --learn              learn and read offline documentation\n"
"-A, --show-all           equivalent to -vET\n"
"-b, --number-nonblank    number nonempty output lines, overrides -n\n"
"-e                       equivalent to -vE\n"
"-E, --show-ends          display $ at end of each line\n"
"-n, --number             number all output lines\n"
"-s, --squeeze-blank      suppress repeated empty output lines\n"
"-t                       equivalent to -vT\n"
"-T, --show-tabs          display TAB characters as ^I\n"
"-u                      (ignored)\n"
"-v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB\n"
"--help     display this help and exit\n"
"--version  output version information and exit\n"

"Examples:\n"
"mew f - g  Output f's contents, then standard input, then g's contents.\n"
"mew        Copy standard input to standard output.\n"

"Programming by Max Base\n"
"Full documentation at: <https://github.com/basemac/dca>\n"
"or available locally via: 'mew --learn't\n";

void print_usage(){ 
    printf("%s", usage); 
}

int main(int argc, char* argv[]){
    if (argc <=1 ) { 
        printf("Error : not enough arguments\n\n");  
        print_usage(); 
    } 

}
