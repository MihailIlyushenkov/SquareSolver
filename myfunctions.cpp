#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "myfunctions.h"
#include <stdlib.h>

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
    const double EPS = 1e-4; /* точность сравнения с 0 */
    return (abs(x) < EPS);
}

ErrorStruct input(double *a_ptr, double *b_ptr, double *c_ptr)
{
    ErrorStruct INPError;

    if (a_ptr == NULL || b_ptr == NULL || c_ptr == NULL)
    {
        return INPError; /* возврат ошибки */
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

    return INPError; /* возврат ошибки */
}

ErrorStruct eqsdef(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{
    ErrorStruct ERR_in_eqsdef;

    if (iszero(a))
    {
        ERR_in_eqsdef = linearsolver(b, c, val0_ptr, outpflag_ptr);
    }
    else
    {
        ERR_in_eqsdef = squaresolver(a, b, c, outpflag_ptr, val0_ptr, val1_ptr);
    }

    return ERR_in_eqsdef; /* возврат ошибки */
}

ErrorStruct linearsolver(double a, double b, double *val0_ptr, rootnum *outpflag_ptr)
{
    ErrorStruct LNsolvError;

    if (val0_ptr == NULL || outpflag_ptr == NULL)
    {
        LNsolvError = ErrorStruct{.Error = BAD_NULL_PTR, .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__};
        return LNsolvError; /* возврат ошибки */
    }

    if (iszero(a))
        {
            if (iszero(b))
            {
                *outpflag_ptr = INFROOTS; /* значение для вывода ответа "беск. кол-ва корней" */
                return LNsolvError; /* возврат ошибки */
            }
            else
            {
                *outpflag_ptr = NOROOTS; /* значение для вывода ответа "нет корней"  */
                return LNsolvError; /* возврат ошибки */
            }
        }
        else
        {
            *outpflag_ptr = ONEROOT; /* значение для вывода ответа "есть 1 корень" */
            *val0_ptr = (-b)/a;
            return LNsolvError; /* возврат ошибки */
        }
}

ErrorStruct squaresolver(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{
    ErrorStruct ErrInSQS;
    if (val0_ptr == NULL || val1_ptr == NULL || outpflag_ptr == NULL)
    {
        ErrInSQS = ErrorStruct{.Error = BAD_NULL_PTR, .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__};
        return ErrInSQS; /* возврат ошибки */
    }

    if (iszero(a))
    {
        linearsolver(b, c, val0_ptr, outpflag_ptr);
        return ErrInSQS; /* возврат не ошибки */
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
    return ErrInSQS; /* возврат ошибки */

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

ErrorStruct TestOneEq(TestData *Tdat)
{

    double val1 = 0, val2 = 0;
    rootnum outpflag = NOROOTS;

    ErrorStruct ErrorInTester;

    if (Tdat == NULL)
    {
        ErrorInTester = ErrorStruct{.Error = BAD_NULL_PTR, .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__};
        return ErrorInTester; /* возврат ошибки */
    }


    eqsdef(Tdat -> a, Tdat -> b, Tdat -> c, &outpflag, &val1, &val2);


    if ( !iszero(val1 - (Tdat -> val1)) || !iszero(val2 - (Tdat -> val2)) || !iszero(outpflag != (Tdat -> outpflag)) )
    {
        printf("\033[31mTest Failed!!!\033[0m\n");
        printf("Expected: val1 = %lf, val2 = %lf. Exected: val1 = %lf, val2 = %lf \n", Tdat -> val1, Tdat -> val2, val1, val2);
        return ErrorInTester; /* возврат не ошибки */
    }
    else
    {
        printf("\033[92mTest passed succesfully.\033[0m\n");
        return ErrorInTester; /* возврат не ошибки */
    }
}

ErrorStruct EquasionTester(char TestFileName[])
{

    ErrorStruct TesterError;
    // const int TestCount = 4; /* Количество строк в файле с тестами */
    FILE *file;

    if (TestFileName == NULL)
    {
        file = fopen("Testdata.txt", "r");
    }
    else
    {
        file = fopen(TestFileName, "r");
    }

    if (file == NULL)
        return TesterError = ErrorStruct{.Error = FILENOTOPEN, .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__}; /* возврат ошибки */

    char Enumstring[12] = {0};
    TestData Tdata = {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NOROOTS};
    int ScansCnt = fscanf(file, "%lf %lf %lf %lf %lf %s", &(Tdata.a), &(Tdata.b), &(Tdata.c), &(Tdata.val1), &(Tdata.val2), Enumstring);

    while (ScansCnt == 6)
    {
        Tdata.outpflag = Convertstringtoenum(Enumstring);

        TesterError = TestOneEq(&Tdata);
        ScansCnt = fscanf(file, "%lf %lf %lf %lf %lf %s", &(Tdata.a), &(Tdata.b), &(Tdata.c), &(Tdata.val1), &(Tdata.val2), Enumstring);
    }

    return TesterError; /* возврат ошибки */
}

ErrorStruct SolveStart()
{
    double a = 0, b = 0, c = 0, val0 = 0, val1 = 0;
    rootnum outpflag;
    int prec = 1;


    input(&a, &b, &c);
    prec = precision_input();
    ErrorStruct Solvstarterr = eqsdef(a, b, c, &outpflag, &val0, &val1);
    output(&val0, &val1, outpflag, prec);
    return Solvstarterr; /* возврат ошибки */
}

void ErrorProcessing(ErrorStruct Errorcode)
{
    switch(Errorcode.Error)
    {
        case NOERROR: break;
        case BAD_NULL_PTR: printf("Invalid argument (NULL pointer). In file %s, in function %s, in line %d\n",
            Errorcode.ErrorFileName, Errorcode.ErrorFuncName, Errorcode.ErrorLineNumber); break;
        case FILENOTOPEN: printf("Invalid argument (Missing test file). In file %s, in function %s, in line %d\n",
            Errorcode.ErrorFileName, Errorcode.ErrorFuncName, Errorcode.ErrorLineNumber); break;
        default: printf("Unexpected Error code: %d\n", Errorcode.Error); break;
    }
}

ErrorStruct CMDProcessing(int argc, char *argv[])
{
    ErrorStruct Errcode;

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

                if (argc == 3)
                {
                    inp = USTESTTAR;
                }

            }
        }
    }

    if (Errcode.Error != NOERROR)
    {
        return Errcode;
    }

    switch(inp)
    {
        case SOLVETAR: Errcode = SolveStart(); break;
        case HELPTAR: printf("Square equasion solver by Mihail Ilyushenkov @2023 v1.0.idkn\nEnter test to run --tests or --solve to enter your equasion"); break;
        case TESTTAR: Errcode = EquasionTester(NULL); break;
        case USTESTTAR:Errcode = EquasionTester(argv[2]); break;
        default: printf("nu error i error (inp not found), che bubnit...."); break;
    }

    return Errcode; /* возврат ошибки */
}
