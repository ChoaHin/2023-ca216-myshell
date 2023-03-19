#ifndef cd
#define cd

void cd(){
    char *cwd = getcwd(NULL, 0);               // current working directory
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
        printf("missing cd argument\n");
    }
}


#endif