#include <stdio.h>

void echo(char** args){
    int i;
    for (i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}