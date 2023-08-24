#include <stdio.h>
#include <math.h>
#include "myfunctions.h"
#include <string.h>

// Почитать про doxygen
// Make почитать


int main(int argc, char *argv[])
{


    ErrorStruct MainError;

    MainError = CMDProcessing(argc, argv);

    ErrorProcessing(MainError);

    getchar();

    return 0;
}
