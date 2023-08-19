#include <stdio.h>
#include <math.h>

void cleaner(void);


int main(void)
{
    float a, b, c, discr;
    int counter = 0;
    printf("enter a, b, c in ax^2 + bx + c equation separated by a space\n");

    while (counter != 3)
    {
        counter = scanf("%f%f%f", &a, &b, &c);
        cleaner();
        if (counter != 3)
        {
            printf("wrong input format, try again\n");
        }
    }

    /* printf("%f %f %f", a, b, c); */

    discr = pow(b, 2) - 4.0*(a*c);
    if (fabs(a) < 000000.1)
        printf("this is not square equation (a can't be 0)");
    else if (discr > 0)
        printf("solutions are %.3f and %.3f", ((-b)+sqrt(discr))/(2*a), ((-b)-sqrt(discr))/(2*a));
    else if (discr == 0)
        printf("solution is %.3f", (-b)/(2*a));
    else
        printf("solutions are %.3f+%.3fi and %.3f-%.3fi", (-b)/(2.0*a), sqrt(fabs(discr))/(2.0*a), (-b)/(2.0*a),  sqrt(fabs(discr))/(2.0*a));

    return 0;
}


void cleaner(void)
{
    int c;
    c = getchar();
    while ((c != '\n') && (c != EOF))
        {
            c = getchar();
        }
}
