#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "myfunctions.h"

#define NOROOTS 0
#define INFROOTS -1
#define ONEROOT 1
#define TWOROOTS 2
#define TWOCMPROOTS -2

void cleaner(void)
{
    int c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
    }
}

bool iszero(double x)
{
    const double EPS = 1e-15; /* точность сравнения с 0 */
    return (abs(x) < EPS);
}

void input(double *a_ip, double *b_ip, double *c_ip, int *pres_ip)
{
    int counter = 0;
    printf("enter a, b, c in ax^2 + bx + c equation separated by a space\n");

    while (counter != 3)
    {
        counter = scanf("%lf%lf%lf", a_ip, b_ip, c_ip);
        cleaner();
        if (counter != 3)
        {
            printf("wrong input format, try again\n");
        }
    }

    printf("enter precision for answers\n");
    while (counter != 1)
    {
        counter = scanf("%d", pres_ip);
        cleaner();
        if (counter != 1)
        {
            printf("wrong input format, try again\n");
        }
    }

}

void extdef(double a, double b, double c, int *outpflag_ip, double *val0_ip, double *val1_ip)
{
    if (iszero(a))
    {
        linearsolver(b, c, val0_ip, outpflag_ip);
    }
    else
    {
        squaresolver(a, b, c, outpflag_ip, val0_ip, val1_ip);
    }
}

void linearsolver(double a, double b, double *val0_ip, int *outpflag_ip)
{
    if (iszero(a))
        {
            if (iszero(b))
            {
                *outpflag_ip = INFROOTS; /* значение для вывода ответа "беск. кол-ва корней" */
                return;
            }
            else
            {
                *outpflag_ip = NOROOTS; /* значение для вывода ответа "нет корней"  */
                return;
            }
        }
        else
        {
            *outpflag_ip = ONEROOT; /* значение для вывода ответа "есть 1 корень" */
            *val0_ip = (-b)/a;
            return;
        }
}

void squaresolver(double a, double b, double c, int *outpflag_ip, double *val0_ip, double *val1_ip)
{

    assert(val0_ip != NULL);
    assert(val1_ip != NULL);
    assert(outpflag_ip != NULL);
    assert( !(iszero(a)) );

    if (iszero(a))
    {
        linearsolver(b, c, val0_ip, outpflag_ip);
        return;
    }

    double discr = pow(b, 2) - 4.0*(a*c);
    *val0_ip = (-b)/(2.0*a);
    *val1_ip = sqrt(abs(discr))/(2.0*a);

    if (iszero(discr))
    {
        *outpflag_ip = ONEROOT; /* значение для вывода ответа "есть 1 действ. корень" */
    }
    else
    {
        if ( discr > 0 )
        {
            *outpflag_ip = TWOROOTS; /* значение для вывода ответа "есть 2 действ. корня" */
        }
        else
        {
            *outpflag_ip = TWOCMPROOTS; /* значение для вывода ответа "есть 2 комплексных корня" */
        }
    }

}

void output(double *val0_ip, double *val1_ip, int *outpflag_ip, int pres)
{
    switch(*outpflag_ip)
    {
        case INFROOTS: printf("infitely many solutions"); break;
        case NOROOTS: printf("no solutions"); break;
        case ONEROOT:  printf("solution is %.*lf", pres, *val0_ip); break;
        case TWOROOTS:  printf("solutions are %.*lf and %.*lf", pres, *val0_ip + *val1_ip,
            pres, *val0_ip - *val1_ip); break;
        case TWOCMPROOTS:  printf("solutions are %.*lf+%.*lfi and %.*lf-%.*lfi",
            pres, *val0_ip, pres, *val1_ip, pres, *val0_ip, pres, *val1_ip); break;
    }
}


