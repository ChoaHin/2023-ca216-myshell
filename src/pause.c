// author:  Chee Hin Choa
// student number:  21100497
//***************************************************************************/
#include <stdio.h>

void pause(){
    printf("Press Enter to continue..."); 
    fflush(stdout); // flush the output buffer
    while(getchar() != '\n'); // wait for Enter to be pressed
}