#include <stdio.h>
#include <math.h>
#include "myfunctions.h"

int main(void)
{
    double a = 0, b = 0, c = 0, val0 = 0, val1 = 0;
    int outpflag = 3, pres = 1;

    input(&a, &b, &c, &pres);
    extdef(a, b, c, &outpflag, &val0, &val1);
    output(&val0, &val1, &outpflag, pres);
    return 0;
}
