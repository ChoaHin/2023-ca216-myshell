#include <string.h>

int redirection(char** args, char **inputfile, char **outputfile){
    #include <string.h>
    int i;
    for (i = 0; args[i] != NULL; i++) {  // Check for input and output redirection
        if (strcmp(args[i], "<") == 0) {
            // Input redirection
            *inputfile = args[i+1];  //set input file
            args[i] = NULL;  //remove input file from command line
            return 1;
        } else if (strcmp(args[i], ">") == 0) {
            // Output redirection
            *outputfile = args[i+1];  //set output file
            args[i] = NULL;  //remove output file from command line
            return 2;
        } else if (strcmp(args[i], ">>") == 0) {
            // Output redirection (append)
            *outputfile = args[i+1]; //set output file
            args[i] = NULL;
            return 3;
        }
    }
    // No redirection found
    return 0;
}