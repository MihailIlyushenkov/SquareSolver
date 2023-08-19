#include <stdio.h>
#include <math.h>

void cleaner(void);
void input(void);
void output(void);

double a, b, c;

int main(void)
{
    input();
    output();
    return 0;
}

void input(void)
{
    int counter = 0;

    printf("enter a, b, c in ax^2 + bx + c equation separated by a space\n");

    while (counter != 3)
    {
        counter = scanf("%lf%lf%lf", &a, &b, &c);
        cleaner();
        if (counter != 3)
        {
            printf("wrong input format, try again\n");
        }
    }
}


void cleaner(void)
{
    int c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
    }
}

void output(void)
{
    const double EPS = 1e-15;
    double discr, value1_1, value1_2, value2_1, value2_2;

    discr = pow(b, 2) - 4.0*(a*c);

    if (fabs(a) < EPS)
    {
        if (fabs(b) < EPS)
        {
            if (fabs(c) < EPS)
            {
                printf("infitely many solutions");
            }
            else
            {
                printf("no solutions");
            }
        }
        else
        {
            printf("%.4lf", (-c)/b);
        }
    }
    else
    {
        if (discr >= EPS)
        {
            value1_1 = ((-b)+sqrt(discr))/(2.0*a);
            value1_2 = ((-b)-sqrt(discr))/(2.0*a);
            printf("solutions are %.4lf and %.4lf", value1_1, value1_2);
        }
        else
        {
            if (fabs(discr) < EPS)
            printf("solution is %.4lf", (-b)/(2*a));

            else
            {
                value2_1 = (-b)/(2.0*a);
                value2_2 = sqrt(fabs(discr))/(2.0*a);
                printf("solutions are %.4lf+%.4lfi and %.4lf-%.4lfi", value2_1, value2_2, value2_1, value2_2);
            }
        }
    }
}
