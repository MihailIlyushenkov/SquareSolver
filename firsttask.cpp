#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, b, c, discr;
    printf("enter a, b, c is ax^2 + bx + c equasion\n");
    scanf("%f%f%f", &a, &b, &c);

    discr = pow(b, 2) - 4.0*(a*c);
    if (fabs(a) < 000000.1)
        printf("this is not square equasion");
    else if (discr > 0)
        printf("solutions are %f and %f", ((-b)+sqrt(discr))/(2*a), ((-b)-sqrt(discr))/(2*a));
    else if (discr == 0)
        printf("solution is %f", (-b)/(2*a));
    else
        printf("solutions are %f+%f and %f-%f", (-b)/(2.0*a), sqrt(fabs(discr))/(2.0*a), (-b)/(2.0*a),  sqrt(fabs(discr))/(2.0*a));

    return 0;
}
