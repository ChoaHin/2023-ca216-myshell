// ********************************************************************
// date:    March 2023
// author:  Chee Hin Choa
// student number:  21100497
// A simple shell program with some built-in commands
// *******************************************************************/

//References
// https://man7.org/linux/man-pages/man3/getcwd.3.html

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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PATH_MAX 2048

void cd(char **args){
        // if directory is present, and only one
        if (args[1] != NULL) {
            if(chdir(args[1]) == 0){
                //change working directory and change environment elements aswell
                printf("changed directory to %s\n", getcwd(NULL, 0));
                char cwd[PATH_MAX];
                getcwd(cwd, sizeof(cwd));
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