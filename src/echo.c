// author:  Chee Hin Choa
// student number:  21100497
//***************************************************************************/
#include <stdio.h>

void echo(char** args){
    int i;
    for (i = 1; args[i] != NULL; i++) {
        //print every argument, simply separated by a space
        printf("%s ", args[i]);
    }
    printf("\n");
}