// internal commands:
// cd  - change the current default directory. If the  argument is not present, report the current directory. If the directory does not exist an appropriate error should be reported. This command should also change the PWD environment variable.
// clr - clear the screen.
// dir  - list the contents of directory e.g. ls -al <directory>
// environ - list all the environment strings
// echo  - echo  on the display followed by a new line (multiple spaces/tabs may be reduced to a single space)
// help - display the user manual using the more filter.  
// pause - pause operation of the shell until 'Enter' is pressed
// quit - quit the shell
// ********************************************************************
// date:    March 2023
// author:  Chee Hin Choa
// student number:  21100497
// A simple shell program with some built-in commands
// *******************************************************************/

//Reference
//https://stackoverflow.com/questions/23102627/creating-ls-command-in-c

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

#include <unistd.h> // for cd
#include <dirent.h> // for dlr
#include <sys/stat.h> // for dlr
#include <time.h> // for dlr
#include <sys/wait.h> // for external commands

//function prototypes
#include "myshell.h"

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "\033[32m|> " ;                    // shell prompt
    char *cwd = getcwd(NULL, 0);               // current working directory

    system("clear"); //clear screen

    //start logo graphics
    printf("  ___  ___  _   _  ____  __    __   \n");
    printf(" / __)/ __\\( )_( )( ___)(  )  (  )  \n");
    printf("( (__ \\__ \\\\ ) _ (  )__)  )(__  )(__ \n");
    printf(" \\___)(___/(_) (_)(____)(____)(____)\n");

    printf("%s\n", cwd); // show current working directory


/* batch file prototype, error infinite loop */
    // FILE *batch = NULL;
    // char command[MAX_BUFFER];
    // if(argc > 1){
    //     batch = fopen(argv[1], "r");
    //     if(!batch){
    //         printf("error opening batch file\n");
    //         return 1;
    //     }
    // }

    // while(1){
    //     if(batch){
    //         if(!fgets(command, MAX_BUFFER, batch)){
    //             //end of file reached
    //             break;
    //         }
    //     } else {
    //         printf("%s", prompt);
    //         if(!fgets(command, MAX_BUFFER, stdin)){
    //             //end of input reached
    //             break;
    //         }
    //     }

    //     command[strcspn(command, "\n")] = '\0';
    //     printf("Command: %s", command);
    // }
    //     if(batch){
    //         fclose(batch);
    //     }
    //     return 0;

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
                printf("\033[31m");  //set output in red
                /* check for internal/external command */
                if (!strcmp(args[0],"clear")) { // "clear" command
                    system("clear");
                    continue;
                }

                if (!strcmp(args[0],"cd")) { // "cd" command
                // if directory is present, and only one
                    if (args[1] != NULL) {
                        if(chdir(args[1]) == 0){
                            //change working directory and change environment elements aswell
                            printf("changed directory to %s\n", getcwd(NULL, 0));
                            getcwd(cwd, 0);
                            if (setenv("PWD", cwd, 1) != 0) {
                                printf("error setting environment variable\n");
                            }
                        } else {
                            printf("error changing directory\n");
                        }
                    } else {
                        printf("missing cd argument\n");
                    }
                }

                if (!strcmp(args[0],"cat")) { // "cat" command
                    cat();
                }
                
                if (!strcmp(args[0], "clr")) { // "clr" command
                    system("clear");
                }

                if (!strcmp(args[0], "dir")) { // "dir" command
                    struct dirent *ent; //directory entry
                    DIR *dir; //directory
                    if(args[1]){ //if directory is present
                        dir = opendir(args[1]); //open directory
                    } else {
                        dir = opendir(cwd); //else open current directory
                    }
                    if(dir == NULL){ //if directory is not present
                        printf("error opening directory\n");
                        break;
                    }   

                    while ((ent = readdir(dir)) != NULL) {
                        struct stat info; //file info
                        char file_path[512];  
                        snprintf(file_path, 512, "%s/%s", cwd, ent->d_name);  //get file path

                        if (stat(file_path, &info) == -1) {  
                            printf("Failed to get file info for %s\n", ent->d_name);
                            continue;
                        }

                        printf("%lld\t%s\t%s\n", (long long)info.st_size, ctime(&info.st_mtime), ent->d_name);
                    }
                    closedir(dir);
                }

                if (!strcmp(args[0],"environ")) {//"environ" command
                    extern char **environ;
                    for(int i = 0; environ[i] != NULL; i++){  //print out environment variables
                        printf("%s\n", environ[i]);
                    }
                }
                
                if (!strcmp(args[0],"echo")) {
                    echo(args);
                }

                if (!strcmp(args[0],"help")) { //help command
                    help();
                }

                if (!strcmp(args[0],"pause")) { //pause command
                    pause();
                }

                if (!strcmp(args[0],"quit"))   // "quit" command
                    break;                     // break out of 'while' loop
            
                /* else pass command onto OS (or in this instance, print them out) */
                else{
                    //check if last argument is & and need to run in background
                    int run_in_background = 0;
                    char **arg;
                    for(arg = args; *arg != NULL; arg++){}
                    char *last_arg = *(arg - 1);
                    if (!strcmp(last_arg,"&")) {
                        run_in_background = 1;
                        last_arg = NULL; //remove & from args
                    }

                    pid_t pid;
                    int status;
                    // Fork and execute other commands
                    pid = fork();
                    if (pid == 0) {
                        // Child process
                        setenv("PWD", "/myshell", 1);
                        if (execvp(args[0], args) == -1) {
                            perror("execvp");
                            exit(1);
                        }
                    } else if (pid < 0) {
                        // Forking error
                        perror("fork");
                    } else if(run_in_background){
                            printf("Running in background\n");
                    } else {
                        if (waitpid(pid, &status, WUNTRACED) == -1) {
                            perror("waitpid");
                            exit(1);
                        }
                    }
                    printf("|\n");
                }
            }
        }
    }
    return 0; 
}
