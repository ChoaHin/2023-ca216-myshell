// ********************************************************************
// date:    March 2023
// author:  Chee Hin Choa
// student number:  21100497
// A simple shell program with some built-in commands
// *******************************************************************/

//References
//https://stackoverflow.com/questions/23102627/creating-ls-command-in-c
//https://www.tutorialspoint.com/system-function-in-c-cplusplus

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

#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#define MAX_ARGS 64                            // max # args

void dir(char* args[MAX_ARGS]){
    char *ls_command = "ls -al";  //prefix for ls command
    if(args[1] == NULL){  //if no directory is specified
        system(ls_command);  //run ls command on current directory
    } else {
        char *target = (char*) malloc (strlen(ls_command) + strlen(args[1]));  //allocate memory for new ls command
        strcat(target, ls_command);  //new string
        strcat(target, args[1]);  //join prefix command and directory
        system(target);  //run ls command on target directory
    }
}

    /*SIMILAR PROTOTYPE*/
    // struct dirent *ent; //directory entry
    // DIR *dir; //directory

    // if(args[1]){ //if directory is present
    //     dir = opendir(args[1]); //open directory
    // } else {
    //     dir = opendir(cwd); //else open current directory
    // }
    // if(dir == NULL){ //if directory is not present
    //     printf("missing target directory\n");
    //     exit(0);
    // }   

    // while ((ent = readdir(dir)) != NULL) {
    //     struct stat info; //file info
    //     char file_path[512];  
    //     snprintf(file_path, 512, "%s/%s", cwd, ent->d_name);  //get file path

    //     if (stat(file_path, &info) == -1) {  
    //         printf("Failed to get file info for %s\n", ent->d_name);
    //         continue;
    //     }

    //     printf("%lld\t%s\t%s\n", (long long)info.st_size, ctime(&info.st_mtime), ent->d_name);
    // }
    // closedir(dir);