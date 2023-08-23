#include <stdio.h>
#include <math.h>
#include "myfunctions.h"


// Сделать проверки на входе в каждую функцию
// Почитать про doxygen
// Фикс кодстайла ip => ptr, ... сделал
// Make почитать

int main(void)
{
    errortype TestEr = NOERROR;
    /* double a = 0, b = 0, c = 0, val0 = 0, val1 = 0;
    rootnum outpflag;
    int prec = 1;

    input(&a, &b, &c);
    prec = precision_input();
    eqsdef(a, b, c, &outpflag, &val0, &val1);
    output(&val0, &val1, outpflag, prec); */

    TestEr = EquasionTester();

    if (TestEr != NOERROR)
    {
        printf("UNEXPECTED ERROR: code %d\n", TestEr);
        printf("Error codes:\n");
        printf("code 0 - no errors\ncode 1 - error of reading file with test data");
    }
    getchar();

    return 0;
}
