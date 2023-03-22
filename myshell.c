// ********************************************************************
// date:    March 2023
// author:  Chee Hin Choa
// student number:  21100497
// A simple shell program with some built-in commands
// *******************************************************************/

//References
//code template from https://loop.dcu.ie/mod/book/view.php?id=2054177&chapterid=433267
/*
I understand that the University regards breaches of academic integrity and plagiarism as
grave and serious.

I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the
penalties that may be imposed should I engage in practice or practices that breach this
policy.

I have identified and included the source of all facts, ideas, opinions and viewpoints of others
in the assignment references. Direct quotations, paraphrasing, discussion of ideas from
books, journal articles, internet sources, module text, or any other source whatsoever are
acknowledged and the sources cited are identified in the assignment references.
I declare that this material, which I now submit for assessment, is entirely my own work and
has not been taken from the work of others save and to the extent that such work has been
cited and acknowledged within the text of my work.

I have used the DCU library referencing guidelines (available at
https://www4.dcu.ie/library/classes_and_tutorials/citingreferencing.shtml and/or the
appropriate referencing system recommended in the assignment guidelines and/or
programme documentation.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h> // for external commands

//function prototypes
#include "myshell.h"

/*function prototype*/
void shell_logo();
void runCommand(char *args[MAX_ARGS]);

/*main*/
int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args

    if(argc == 1){  //only file name present
        shell_logo();  //display logo
        while(!feof(stdin)){  //while not end of file
            char cwd[MAX_BUFFER];  //current working directory
            getcwd(cwd, sizeof(cwd));  //get current working directory
            setenv("PWD", cwd, 1);  //set PWD environment variable to current working directory
            char * prompt = strcat(getenv("PWD"),"\033[32m|> ");                    // green shell prompt
            fputs(prompt, stdout);  //display prompt

            if(fgets(buf, MAX_BUFFER, stdin)){  //read input
                arg = args;  //set an alternative pointer arg to args
                *arg++ = strtok(buf, SEPARATORS);  //tokenize input

                while((*arg++ = strtok(NULL,SEPARATORS)));  //while there are more tokens
                *arg++ = NULL;  //set last token to NULL
                runCommand(args);   //run command
            }
        }
    }

    if(argc == 2){  //batch file present
        FILE *batch = NULL;  //batch file
        batch = fopen(argv[1], "r");  //open batch file
        if(!batch){  //if batch file not found
            printf("error opening batch file\n");  //display error message
            return 1;
        }
        /*notice here we using batch file instead of standard input*/
        while(fgets(buf, MAX_BUFFER, batch)){  //while not end of file
            arg = args;  //set an alternative pointer arg to args
            *arg++ = strtok(buf,SEPARATORS);  //tokenize input
            while ((*arg++ = strtok(NULL,SEPARATORS)));  //while there are more tokens
            *arg++ = NULL;  //set last token to NULL
            runCommand(args);  //run command
        }
        fclose(batch);  //close batch file
    }
    
    if (argc > 2) {  //too many arguments
        printf("Too many arguments supplied.\n");
        return 1;
    }
    printf("Back to terminal\n");  //end shell message
    return 0;
}

/*clear screen and display shell logo*/
void shell_logo(){
    system("clear"); //clear screen
    //print ascii art logo
    printf("  ___  ___  _   _  ____  __    __   \n");
    printf(" / __)/ __\\( )_( )( ___)(  )  (  )  \n");
    printf("( (__ \\__ \\\\ ) _ (  )__)  )(__  )(__ \n");
    printf(" \\___)(___/(_) (_)(____)(____)(____)\n");
}

/* run internal command and external command */
void runCommand(char *args[MAX_ARGS]){
    printf("\033[31m");  //set output in red
    if (args[0]) {                     // if there's anything there
        /* check for internal */
        if (!strcmp(args[0],"clr")) { // "clr" command
            clr();
            //continue;
        }

        else if (!strcmp(args[0],"cd")) { // "cd" command
            cd(args);
        }

        else if (!strcmp(args[0],"cat")) { // "cat" command
            cat(args);
        }

        else if (!strcmp(args[0], "dir")) { // "dir" command
            dir(args);
        }

        else if (!strcmp(args[0],"ls_environ")) { // "environ" command
            ls_environ();
        }
        
        else if (!strcmp(args[0],"echo")) {  // "echo" command
            echo(args);
        }

        else if (!strcmp(args[0],"help")) { //help command
            help();
        }

        else if (!strcmp(args[0],"pause")) { //pause command
            pause();
        }

        else if (!strcmp(args[0],"quit")) {  // "quit" command
            exit(0);                    //exit whole program
        }

        /* else pass command onto OS for external command*/
        else{
            //check if last argument is & and need to run in background
            int run_in_background = 0;  //flag to check if command needs to run in background
            int index = 0;
            for(; args[index] != NULL; index++){ continue; }  //get index of last argument
            if (!strcmp(args[index - 1], "&")) {  //if last argument is &
                run_in_background = 1;  //set flag to true
                args[index - 1] = NULL; //remove & from args
            }

            pid_t pid;  //process id
            int status;  //status of process
            // Fork and execute other commands
            pid = fork();
            if (pid == 0) { // Child process
                setenv("PWD", "/myshell", 1);  //set PWD environment variable to current working directory
                if (execvp(args[0], args) == -1) {  //execute command
                    perror("execvp");  //error message
                    exit(1);
                }
            } else if (pid < 0) {  
                // Forking error
                perror("fork");
            } else if(run_in_background){  //if command needs to run in background
                    //not waiting for child process to finish
                    printf("Running in background\n");
                    system("ps");  //display running processes
            } else {
                if (waitpid(pid, &status, WUNTRACED) == -1) {  //wait for child process to finish
                    perror("waitpid");
                    exit(1);
                }
            }
            printf("|\n");  //end of command
            }
        }
}