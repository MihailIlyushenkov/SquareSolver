#include <stdio.h>
#include <math.h>
#include <assert.h>

#define NOROOTS 0
#define INFROOTS -1
#define ONEROOT 1
#define TWOROOTS 2
#define TWOCMPROOTS -3

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

void input(double *a_ip, double *b_ip, double *c_ip)
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

}

void solver(double a, double b, double c, int *outpflag_ip, double *val0_ip, double *val1_ip)
{

    assert(val0_ip != NULL);
    assert(val1_ip != NULL);
    assert(outpflag_ip != NULL);

    if (iszero(a))
    {
        if (iszero(b))
        {
            if (iszero(c))
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
            *val0_ip = (-c)/b;
            return void();
        }
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

void output(double *val0_ip, double *val1_ip, int *outpflag_ip)
{

    switch(*outpflag_ip)
    {
        case INFROOTS: printf("infitely many solutions"); break;
        case NOROOTS: printf("no solutions"); break;
        case ONEROOT:  printf("solution is %.4lf", *val0_ip); break;
        case TWOROOTS:  printf("solutions are %.4lf and %.4lf", *val0_ip + *val1_ip, *val0_ip - *val1_ip); break;
        case TWOCMPROOTS:  printf("solutions are %.4lf+%.4lfi and %.4lf-%.4lfi", *val0_ip, *val1_ip, *val0_ip, *val1_ip); break;
    }
}
