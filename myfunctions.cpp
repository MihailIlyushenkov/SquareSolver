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
    const double EPS = 1e-6; /* точность сравнения с 0 */
    return (abs(x) < EPS);
}

errortype input(double *a_ptr, double *b_ptr, double *c_ptr)
{

    if (a_ptr == NULL || b_ptr == NULL || c_ptr == NULL)
    {
        return PTRERRORINP;
    }


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

    return NOERROR;
}

errortype eqsdef(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{
    errortype ERR_in_eqsdef = NOERROR;

    if (iszero(a))
    {
        ERR_in_eqsdef = linearsolver(b, c, val0_ptr, outpflag_ptr);
    }
    else
    {
        ERR_in_eqsdef = squaresolver(a, b, c, outpflag_ptr, val0_ptr, val1_ptr);
    }

    return ERR_in_eqsdef;
}

errortype linearsolver(double a, double b, double *val0_ptr, rootnum *outpflag_ptr)
{
    if (val0_ptr == NULL || outpflag_ptr == NULL)
    {
        return PTRERRORLN;
    }

    if (iszero(a))
        {
            if (iszero(b))
            {
                *outpflag_ptr = INFROOTS; /* значение для вывода ответа "беск. кол-ва корней" */
                return NOERROR;
            }
            else
            {
                *outpflag_ptr = NOROOTS; /* значение для вывода ответа "нет корней"  */
                return NOERROR;
            }
        }
        else
        {
            *outpflag_ptr = ONEROOT; /* значение для вывода ответа "есть 1 корень" */
            *val0_ptr = (-b)/a;
            return NOERROR;
        }
}

errortype squaresolver(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{
    if (val0_ptr == NULL || val1_ptr == NULL || outpflag_ptr == NULL)
    {
        return PTRERRORSQ;
    }

    if (iszero(a))
    {
        linearsolver(b, c, val0_ptr, outpflag_ptr);
        return NOERROR;
    }

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
    return NOERROR;

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

errortype TestOneEq(TestData *Tdat)
{

    double val1 = 0, val2 = 0;
    rootnum outpflag = NOROOTS;

    if (Tdat == NULL)
    {
        return PTRERRTESTF;
    }


    eqsdef(Tdat -> a, Tdat -> b, Tdat -> c, &outpflag, &val1, &val2);





    if ( !iszero(val1 - (Tdat -> val1)) || !iszero(val2 - (Tdat -> val2)) || !iszero(outpflag != (Tdat -> outpflag)) )
    {
        printf("\033[31mTest Failed!!!\033[0m\n");
        printf("Expected: val1 = %lf, val2 = %lf. Exected: val1 = %lf, val2 = %lf \n", Tdat -> val1, Tdat -> val2, val1, val2);
        return NOERROR;
    }
    else
    {
        printf("\033[92mTest passed succesfully.\033[0m\n");
        return NOERROR;
    }
}

errortype EquasionTester()
{

    errortype TesterError = NOERROR;
    const int TestCount = 4; /* Количество строк в файле с тестами */

    FILE *file = fopen("Testsdata.txt", "r");

    if (file == NULL)
        return FILENOPEN;

    for (int i = 0; i < TestCount; i += 1)
    {
        char Enumstring[12] = {0};

        TestData Tdata = {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NOROOTS};

        fscanf(file, "%lf %lf %lf %lf %lf %s", &(Tdata.a), &(Tdata.b), &(Tdata.c), &(Tdata.val1), &(Tdata.val2), Enumstring);

        /* printf("%lf %lf %lf %lf %lf %s", dat1[0], dat1[1], dat1[2], dat1[3], dat1[4], Enumstring); */

        Tdata.outpflag = Convertstringtoenum(Enumstring);


        TesterError = TestOneEq(&Tdata);
    }
    return TesterError;
}

errortype SolveStart()
{
    double a = 0, b = 0, c = 0, val0 = 0, val1 = 0;
    rootnum outpflag;
    int prec = 1;


    input(&a, &b, &c);
    prec = precision_input();
    errortype Solvstarterr = eqsdef(a, b, c, &outpflag, &val0, &val1);
    output(&val0, &val1, outpflag, prec);
    return Solvstarterr;
}


void ErrorProcessing(errortype Errorcode)
{
    if (Errorcode != NOERROR)
    {
        printf("\nUNEXPECTED ERROR: code %d\n", Errorcode);
        printf("Error codes:\n");
        printf("code 0 - no errors\n");
        printf("code 1 - error of reading file with test data\n");
        printf("code 2 - pointer error (null pointer) in Squareslover()\n");
        printf("code 3 - pointer error (null pointer) in linearsolver()\n");
        printf("code 4 - pointer error (null pointer) in TestOneEq()\n");

    }
}

errortype CMDProcessing(int argc, char *argv[])
{
    errortype Errcode = NOERROR;

    progtarget inp = HELPTAR;

    if (argc >= 2)
    {
        if (!(strcmp(argv[1], "--solve")))
        {
            inp = SOLVETAR;
        }
        else
        {
            if ( !(strcmp(argv[1], "--test")) )
            {
            inp = TESTTAR;
            }
        }
    }


    switch(inp)
    {
        case SOLVETAR: Errcode = SolveStart(); break;
        case HELPTAR: printf("Square equasion solver by Mihail Ilyushenkov @2023 v1.0.idkn\nEnter test to run --tests or --solve to enter your equasion"); break;
        case TESTTAR: Errcode = EquasionTester(); break;
        default: printf("nu error i error (inp not found), che bubnit...."); break;
    }

    /*
    if (inp == 1)
    {
        Errcode = SolveStart();
    }

    else
    {
        if (inp == -1)
        {
            Errcode = EquasionTester();
        }
        else
        {
            if (inp == 0)
            {
                printf("Square equasion solver by Mihail Ilyushenkov @2023 v1.0.idkn\nEnter test to run --tests or --solve to enter your equasion");
            }
        }
    }
    */
    return Errcode;
}
