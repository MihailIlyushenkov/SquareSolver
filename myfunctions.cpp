#include <stdio.h>
#include <math.h>

void input(double *a_ip, double *b_ip, double *c_ip)
{
    int counter = 0;
    printf("enter a, b, c in ax^2 + bx + c equation separated by a space\n");

    while (counter != 3)
    {
        counter = scanf("%lf%lf%lf", a_ip, b_ip, c_ip);
        /* cleaner(); */
        if (counter != 3)
        {
            printf("wrong input format, try again\n");
        }
    }

}

void solver(double a, double b, double c, int *outpflag_ip, double *val0_ip, double *val1_ip)
{
    const double EPS = 1e-15;
    double discr;

    if (fabs(a) < EPS)
    {
        if (fabs(b) < EPS)
        {
            if (fabs(c) < EPS)
            {
                *outpflag_ip = -3;
                return;
            }
            else
            {
                *outpflag_ip = -2;
                return;
            }
        }
        else
        {
            *outpflag_ip = -1;
            *val0_ip = (-c)/b;
            return void();
        }
    }

    discr = pow(b, 2) - 4.0*(a*c);
    *val0_ip = (-b)/(2.0*a);
    *val1_ip = sqrt(fabs(discr))/(2.0*a);

    if (discr > EPS)
    {
        *outpflag_ip = 0;
    }
    else
    {
        if (fabs(discr) < EPS)
        {
            *outpflag_ip = 1;
        }
        else
        {
            *outpflag_ip = 2;
        }
    }

}
