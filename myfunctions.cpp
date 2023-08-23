#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "myfunctions.h"

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

void input(double *a_ptr, double *b_ptr, double *c_ptr)
{

    assert(a_ptr != NULL);
    assert(b_ptr != NULL);
    assert(c_ptr != NULL);

    int counter = 0;
    printf("enter a, b, c in ax^2 + bx + c equation separated by a space\n");

    while (counter != 3)
    {
        counter = scanf("%lf%lf%lf", a_ptr, b_ptr, c_ptr);
        cleaner();
        if (counter != 3)
        {
            printf("wrong input format, try again\n");
        }
    }

}

void eqsdef(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{

    assert(outpflag_ptr != NULL);
    assert(val0_ptr != NULL);
    assert(val1_ptr != NULL);

    if (iszero(a))
    {
        linearsolver(b, c, val0_ptr, outpflag_ptr);
    }
    else
    {
        squaresolver(a, b, c, outpflag_ptr, val0_ptr, val1_ptr);
    }
}

void linearsolver(double a, double b, double *val0_ptr, rootnum *outpflag_ptr)
{
    assert(val0_ptr != NULL);
    assert(outpflag_ptr != NULL);

    if (iszero(a))
        {
            if (iszero(b))
            {
                *outpflag_ptr = INFROOTS; /* значение для вывода ответа "беск. кол-ва корней" */
                return;
            }
            else
            {
                *outpflag_ptr = NOROOTS; /* значение для вывода ответа "нет корней"  */
                return;
            }
        }
        else
        {
            *outpflag_ptr = ONEROOT; /* значение для вывода ответа "есть 1 корень" */
            *val0_ptr = (-b)/a;
            return;
        }
}

void squaresolver(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{

    assert(val0_ptr != NULL);
    assert(val1_ptr != NULL);
    assert(outpflag_ptr != NULL);
    assert( !(iszero(a)) );

    if (iszero(a))
    {
        linearsolver(b, c, val0_ptr, outpflag_ptr);
        return;
    }

    // Лучшк b * b - сделал
    double discr = b*b - 4 * a * c;
    *val0_ptr = (-b) / (2.0 * a);
    *val1_ptr = sqrt(abs(discr)) / (2.0 * a);

    if (iszero(discr))
    {
        *outpflag_ptr = ONEROOT; /* значение для вывода ответа "есть 1 действ. корень" */
    }
    else
    {
        if ( discr > 0 )
        {
            *outpflag_ptr = TWOROOTS; /* значение для вывода ответа "есть 2 действ. корня" */
        }
        else
        {
            *outpflag_ptr = TWOCMPROOTS; /* значение для вывода ответа "есть 2 комплексных корня" */
        }
    }

}

void output(double *val0_ptr, double *val1_ptr, rootnum outpflag_ptr, int prec)
{
    switch(outpflag_ptr)
    {

        case INFROOTS: printf("infitely many solutions"); break;
        case NOROOTS: printf("no solutions"); break;
        case ONEROOT:  printf("solution is %.*lf", prec, *val0_ptr); break;
        case TWOROOTS:  printf("solutions are %.*lf and %.*lf", prec, *val0_ptr + *val1_ptr,
            prec, *val0_ptr - *val1_ptr); break;
        case TWOCMPROOTS:  printf("solutions are %.*lf+%.*lfi and %.*lf-%.*lfi",
            prec, *val0_ptr, prec, *val1_ptr, prec, *val0_ptr, prec, *val1_ptr); break;
        default: printf("output error");
    }
}

int precision_input()
{
    int prec = 0;
    int counter = 0;
    printf("enter precision for answers\n");
    while (counter != 1)
    {
        counter = scanf("%d", &prec);
        cleaner();
        if ( (counter != 1) || ( prec < 0) )
        {
            printf("wrong input format, try again\n");
        }
    }
    return prec;
}

rootnum Convertstringtoenum(char Enumstring[])
{
    if (!(strcmp(Enumstring, "INFROOTS")))
    {
        return INFROOTS;
    }
    else if (!(strcmp(Enumstring, "NOROOTS")))
    {
        return NOROOTS;
    }
    else if (!(strcmp(Enumstring, "ONEROOT")))
    {
        return ONEROOT;
    }
    else if (!(strcmp(Enumstring, "TWOROOTS")))
    {
        return TWOROOTS;
    }
    else if (!(strcmp(Enumstring, "TWOCMPROOTS")))
    {
        return TWOCMPROOTS;
    }
    return NOROOTS;
}

void TestOneEq(double dat[], rootnum outpflag_ref)
{
    double a = dat[0];
    double b = dat[1];
    double c = dat[2];
    double val1_ref = dat[3];
    double val2_ref = dat[4];
    double val1 = 0, val2 = 0;
    rootnum outpflag = NOROOTS;

    squaresolver(a, b, c, &outpflag, &val1, &val2);

    if ( iszero(val1 - val1_ref) || iszero(val2 - val2_ref) || iszero(outpflag != outpflag_ref) )
    {
        printf("Test Failed!!! Expected: val1 = %lf, val2 = %lf.n Exected: val1 = %lf, val2 = %lf \n", val1_ref, val2_ref, val1, val2);
    }
    else
        printf("Test passed succesfully.\n");
}

int EquasionTester()
{

    const int TestCount = 3; /* Количество строк в файле с тестами */

    FILE *file = fopen("C:\\Users\\Mi\\Documents\\GitHub\\SquareSolver\\Testdat.txt", "r");

    for (int i = 0; i < TestCount; i += 1)
    {
        char Enumstring[12] = {0};
        double dat1[6] = {0};
        rootnum outpflag;

        fscanf(file, "%lf %lf %lf %lf %lf %s",
        &dat1[0], &dat1[1], &dat1[2], &dat1[3], &dat1[4], Enumstring);

        outpflag = Convertstringtoenum(Enumstring);

        TestOneEq(dat1[], outpflag);
    }
    return 0;
}
