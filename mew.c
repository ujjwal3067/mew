#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 


void read_file(char* filepath);

bool show_end = false;
bool line_count = false; 
bool empty_line = false; 
bool line_number = false; 


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
    while ((opt = getopt(argc, argv, "hEbnf:")) != -1) {
        switch (opt) {
            case 'E' : show_end = true; 
                       break; 

            case 'f':  filename = optarg; 
                       break; 
            case 'b': line_count = true;  
                      break;
            case 'n': line_number = true; 
                      break ; 
            case 'h': 
                      print_usage();
                      exit(EXIT_SUCCESS); 
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

void append_end_delimeter(char* line){
    int i = 0 ;
    char buffer[1000]; 
    for(i = 0 ; line[i] != '\n'; i++) { 
        buffer[i] = line[i]; 
        // printf("%c", line[i]); 
    }
    buffer[++i] =  '$';
    printf("%s\n", buffer); 

    // clear the buffer
    for(i  = 0 ; i < strlen(buffer); i++) { 
        buffer[i] = ' '; 
    }

} 

void  create_large_line(char * line){ 
    char buffer[1000] ; 
    for(int i = 0 ; i < strlen(line) ; i++) { 
        buffer[i] = line[i]; 
    }
}



void read_file(char* filepath) { 
    int lines_count = 0; 

    char ch , file_name[25]; 
    char* line = NULL; 
    size_t len = 0 ; 
    ssize_t read; 


    FILE* fp ; 
    fp =  fopen(filepath, "r"); // read mode
    if(fp == NULL) { 
      perror("Error while opening the file\n"); 
      exit(EXIT_FAILURE); 
    }

    print_line();

    /* while((ch = fgetc(fp))!= EOF){ */
    /*     if (show_end) */
    /*         if(ch == '\n') { */ 
    /*             printf("$%c",ch); */ 
    /*             lines_count += 1; */ 
    /*         } */
    /*         else */ 
    /*             printf("%c", ch); */ 
        
    /*         printf("%c", ch); */ 
    /*         if (ch == '\n') */ 
    /*             lines_count +=1 ; */ 
    /*     } */
    /* } */ 
    

    char END = '$'; 
    while((read = getline(&line, &len, fp)) != -1) { 
        lines_count += 1; 
        if (show_end) {  
            append_end_delimeter(line); 
        }
        else if (line_number) {
            printf("%d %s", lines_count, line); 
            }
        else { 
            printf("%s", line); 
        }
    }


    fclose(fp); 
    if (line)
        free(line); 

    if (line_count)  { 
        printf("\n\nstats : \n"); 
        printf("total lines : %d", lines_count); 
    }
    exit(EXIT_SUCCESS); 
}
