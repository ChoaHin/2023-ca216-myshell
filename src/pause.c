#include <stdio.h>

void pause(){
    printf("Press Enter to continue..."); 
    fflush(stdout); // flush the output buffer
    while(getchar() != '\n'); // wait for Enter to be pressed
}