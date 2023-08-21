#include <stdio.h>
#include <math.h>
#include "myfunctions.h"

int main(void)
{
    double a, b, c, val0, val1;
    int outpflag;

    input(&a, &b, &c);
    solver(a, b, c, &outpflag, &val0, &val1);
    output(&val0, &val1, &outpflag);
    return 0;
}
