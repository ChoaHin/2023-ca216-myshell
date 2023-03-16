// internal commands:
// clear - clears the screen
// quit - exits from the program
// ********************************************************************
// version: 1.0
// date:    December 2003
// author:  Ian G Graham
// School of Information Technology
// Griffith University, Gold Coast
// ian.graham@griffith.edu.au
// copyright (c) Ian G Graham, 2003. All rights reserved.
// This code can be used for teaching purposes, but no warranty,
// explicit or implicit, is provided.
// *******************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

#include <unistd.h>

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "==>" ;                    // shell prompt
    /* keep reading input until "quit" command or eof of redirected input */

    while (!feof(stdin)) { 
        /* get command line from input */
        fputs (prompt, stdout); // write prompt

        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenise input

            while ((*arg++ = strtok(NULL,SEPARATORS)));

            // last entry will be NULL 
            if (args[0]) {                     // if there's anything there
                /* check for internal/external command */
                if (!strcmp(args[0],"clear")) { // "clear" command
                    system("clear");
                    continue;
                }

                if (!strcmp(args[0],"cd")) { // "cd" command
                    if (args[1] != NULL) {
                        if(chdir(args[1]) == 0){
                            printf("changed directory to %s\n", getcwd(NULL, 0));
                            if(setenv("CWD", args[1], 1) != 0) {
                                printf("error setting environment variable\n");
                            }
                        } else {
                            printf("error changing directory\n");
                        }
                    } else {
                        printf("missing cd argument");
                    }
                }

                if (!strcmp(args[0],"cat")) { // "cat" command
                    printf("\n");
                    printf(" /\\_/\\ \n");
                    printf("( o.o )\n");
                    printf(" > ^ < \n");
                    printf("\n");
                    }
                
                if (!strcmp(args[0], "clr")) { // "clr" command
                    system("clear");
                }

                if (!strcmp(args[0],"quit"))   // "quit" command
                    break;                     // break out of 'while' loop
            
                /* else pass command onto OS (or in this instance, print them out) */
                arg = args;
                while (*arg) {

                    fprintf(stdout,"%s ",*arg++);
                    fputs ("\n", stdout);
                }
            }
        }
    }
    return 0; 
}
