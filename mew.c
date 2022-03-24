#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 


void read_file(char* filepath);

bool show_end = false;
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

void print_line() { 
    printf("\n------------------------------------\n\n\n"); 
}

int main(int argc, char* argv[]){
     bool isCaseInsensitive = false;
    int opt;
    enum { CHARACTER_MODE, WORD_MODE, LINE_MODE } mode = CHARACTER_MODE;

    char* filename = NULL; 
    while ((opt = getopt(argc, argv, "Ef:")) != -1) {
        switch (opt) {
            case 'E' : show_end = true; 
                       break; 

            case 'f':  filename = optarg; 
                       break; 
        default:
            fprintf(stderr, "Usage: %s [-ilw] [file...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // processing  file
    if(filename != NULL) { 
        read_file(filename);
        return 0 ; 
    } else { 
        printf("\nError: file path not provided\n"); 
        exit(EXIT_FAILURE);
    }
}

void read_file(char* filepath) { 
    char ch , file_name[25]; 
    FILE* fp ; 
    fp =  fopen(filepath, "r"); // read mode
    if(fp == NULL) { 
      perror("Error while opening the file\n"); 
      exit(EXIT_FAILURE); 
    }

    print_line();

    while((ch = fgetc(fp))!= EOF)
        if (show_end)
            if(ch == '\n')
                printf("$%c",ch); 
            else 
                printf("%c", ch); 
        else printf("%c", ch); 

    fclose(fp); 
}

int test(int argc, char* argv[]){
    if (argc <=1 ) { 
        printf("Error : not enough arguments\n\n");  
        print_usage(); 
        exit(0);
    } 

    /* if (argc > 2) { */ 
    /*     /1* printf("too many arguments"); *1/ */
    /* } */

    /* char* filepath = argv[1]; */
    /* printf("file path = %s\n", filepath); */ 

    /* read_file(filepath); */ 

    return 0 ; 
}
