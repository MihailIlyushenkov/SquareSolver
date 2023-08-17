#include <stdio.h>
#include <math.h>
#include <TXLib.h>

int main(void)
{
    float a, b, c, discr;
    scanf("%f%f%f", &a, &b, &c);

    discr = pow(b, 2) - 4.0*(a*c);
    if (discr > 0)
        printf("решения это %f and %f", ((-b)+sqrt(discr))/(2*a), ((-b)-sqrt(discr))/(2*a));
    else if (discr == 0)
        printf("решение это %f", (-b)/(2*a));
    else
        printf("нет действительных решений");

    return 0;
}
