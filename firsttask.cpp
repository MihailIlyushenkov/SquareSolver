#include <stdio.h>
#include <math.h>
#include "myfunctions.h"
#include <string.h>

// Почитать про doxygen
// Make почитать


int main(int argc, char *argv[])
{
    errortype Errcode = NOERROR;


    Errcode = CMDProcessing(argc, argv);

    ErrorProcessing(Errcode);

    getchar();

    return 0;
}
