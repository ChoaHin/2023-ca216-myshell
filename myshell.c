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

//Reference
//https://stackoverflow.com/questions/23102627/creating-ls-command-in-c

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

#include <unistd.h> // maybe cd
#include <dirent.h> // for dlr
#include <sys/stat.h> // for dlr
#include <time.h> // for dlr

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "==>" ;                    // shell prompt
    char *cwd = getcwd(NULL, 0);               // current working directory
    printf("%s\n", cwd);

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
                            getcwd(cwd, 0);
                            if (setenv("PWD", cwd, 1) != 0) {
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

                if (!strcmp(args[0], "dir")) { // "dir" command
                    struct dirent *ent;
                    DIR *dir;
                    dir = opendir(cwd);
                    if(dir == NULL){
                        printf("error opening directory\n");
                        break;
                    }   

                    while ((ent = readdir(dir)) != NULL) {
                        struct stat info;
                        char file_path[512];
                        snprintf(file_path, 512, "%s/%s", cwd, ent->d_name);

                        if (stat(file_path, &info) == -1) {
                            printf("Failed to get file info for %s\n", ent->d_name);
                            continue;
                        }

                        //printf("%lld\t%s\t", (long long)info.st_size, ctime(&info.st_mtime));
                        printf("%s\n", ent->d_name);
                    }

                    closedir(dir);
                }

                if (!strcmp(args[0],"environ")) {//"environ" command
                    extern char **environ;
                    for(int i = 0; environ[i] != NULL; i++){
                        printf("%s\n", environ[i]);
                    }
                }
                
                if (!strcmp(args[0],"echo")) {
                    int i;
                    for (i = 1; args[i] != NULL; i++) {
                        printf("%s ", args[i]);
                    }
                    printf("\n");
                }

                if (!strcmp(args[0],"help")) { //help command
                    system("more manual.txt");
                }

                if (!strcmp(args[0],"pause")) { //pause command
                    printf("Press Enter key to continue...");
                    getchar();
                }

                if (!strcmp(args[0],"quit"))   // "quit" command
                    break;                     // break out of 'while' loop
            
                /* else pass command onto OS (or in this instance, print them out) */
                arg = args;
                while (*arg) {

                    printf("%s ",*arg);
                    arg++;
                }
            }
        }
    }
    return 0; 
}
