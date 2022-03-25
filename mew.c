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
bool indentation = false; 
bool show_tabs = false; 
bool remove_empty = false; 


const char *usage = "\n\nUsage: mew [OPTION]... [FILE]...\n"
"Concatenate FILE(s) to standard output.\n"

"-f,                      file path\n"
"-b, --number-nonblank    number nonempty output lines, overrides -n\n"
"-E, --show-ends          display $ at end of each line\n"
"-n, --number             number all output lines\n"
"-T, --show-tabs          display TAB characters as ^I\n"
"-i,                      display this help and exit\n"
"-r,                      remove empty lines\n"
"-h     display this help and exit\n";


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
    while ((opt = getopt(argc, argv, "rTihEbnf:")) != -1) {
        switch (opt) {
            case 'E' : show_end = true; 
                       break; 

            case 'f': filename = optarg; 
                      break; 
            case 'b': line_count = true;  
                      break;
            case 'n': line_number = true; 
                      break ; 
            case 'i' : indentation = true;
                      break; 
            case 'T': show_tabs = true; 
                      break; 
            case 'r': remove_empty = true; 
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

void show_indentation(char  *line) { 
    int i = 0 ; 
    char buffer[1000]; 
    int bit =  0 ; 
    for(i = 0 ; line[i] != '\n'; i++){ 
        if(bit == 0 && (line[i] == ' ' || line[i] == '\t')) { 
            buffer[i] = '-';
            continue ; 
        }else { 
            bit = 1; 
            buffer[i] = line[i]; 
            continue ; 
        }
    }
    printf("%s\n", buffer); 
    // clean the buffer
    for(i = 0 ; i < strlen(buffer) ; i++) { 
        buffer[i] = ' '; 
    }
}  


void display_tabchar(char * line) { 
    int i = 0; 
    char buffer[1000]; 
    int bit = 0 ; 
    for(i = 0 ; line[i] != '\n'; i++) { 
        if(bit == 0 && (line[i] == '\t')){ 
            buffer[i] = '-'; 
            continue ; 
        }else { 
            bit = 1 ; 
            buffer[i] = line[i]; 
            continue ; 
        }
    }

    printf("%s\n", buffer); 
    // clean the buffer
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


bool line_is_empty(char * line ) { 
    int i = 0 ; 
    int bit = 0 ; 
    int len = strlen(line); 
    if (len == 1 )  { 
        return true; 
    }
    return false; 
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

        // don't process the empty line for all flags
        if(remove_empty && line_is_empty(line)){  
            continue ; 
        }

        if (show_end) {  
            append_end_delimeter(line); 
        }
        else if (line_number) {
            printf("%d %s", lines_count, line); 
        }
        else if (indentation) { 
            show_indentation(line);
        }else if (show_tabs) { 
            display_tabchar(line); 
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
