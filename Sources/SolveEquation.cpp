#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "SolveFunctions.h"

#ifdef TEST
    #include "TestFunctions.h"
#endif

#include <stdlib.h>

/*!
\file
\brief .cpp файл с телами функций

Данный файл содержит в себе основные функции, используемые в основной программе
*/

void ClearBuffer(void)
{
    int c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
    }
}

bool IsZero(double x)
{
    const double EPS = 1e-4; ///точность сравнения с 0
    return (abs(x) < EPS);
}

ErrorStruct Input(EquationData *ReturnData)
{
    CHECK_ARGUMENT(ReturnData);

    int counter = 0;
    printf("enter a, b, c in ax^2 + bx + c equation separated by a space\n");
    double a, b, c = 0;

    while (counter != 3)
    {
        counter = scanf("%lf%lf%lf", &a, &b, &c);
        ClearBuffer();
        if (counter != 3)
        {
            printf("wrong Input format, try again\n");
        }
    }
    ReturnData -> a = a;
    ReturnData -> b = b;
    ReturnData -> c = c;

    return ErrorStruct {}; /* возврат ошибки */
}


ErrorStruct SolveEquation(EquationData *EquationData)
{
    CHECK_ARGUMENT(EquationData);

    if (IsZero(EquationData -> a))
    {
        return SolveLinearEquation(EquationData);
    }
    else
    {
        return SolveSquareEquation(EquationData);
    }
}

ErrorStruct SolveLinearEquation(EquationData *EquationData)
{
    CHECK_ARGUMENT(EquationData);

    if (IsZero(EquationData -> b))
        {
            if (IsZero(EquationData -> c))
            {
                (EquationData -> outpflag) = INF_ROOTS; /* значение для вывода ответа "беск. кол-ва корней" */
            }
            else
            {
                (EquationData -> outpflag) = NO_ROOTS; /* значение для вывода ответа "нет корней"  */
            }
        }
    else
    {
        (EquationData -> outpflag) = ONE_ROOT; /* значение для вывода ответа "есть 1 корень" */
        (EquationData -> val1) = -(EquationData -> b)/(EquationData -> a);
    }

    return ErrorStruct {};  /* возврат ошибки */
}

ErrorStruct SolveSquareEquation(EquationData *EquationData)
{
    CHECK_ARGUMENT(EquationData);

    double a = EquationData -> a;
    double b = EquationData -> b;
    double c = EquationData -> c;


    double discr = b * b - 4 * a * c;

    EquationData -> val1 = (-b) / (2.0 * a);
    EquationData -> val2 = sqrt(abs(discr)) / (2.0 * a);

    if (IsZero(discr))
    {
        EquationData -> outpflag = ONE_ROOT; /* значение для вывода ответа "есть 1 действ. корень" */
    }
    else if ( discr > 0 )
    {
        EquationData -> outpflag = TWO_ROOTS; /* значение для вывода ответа "есть 2 действ. корня" */
    }
    else
    {
        EquationData -> outpflag = TWO_COMPLEX_ROOTS; /* значение для вывода ответа "есть 2 комплексных корня" */
    }
    return ErrorStruct {};  /* возврат ошибки */
}


ErrorStruct Output(const EquationData *OutpData, int prec)
{
    CHECK_ARGUMENT(OutpData)
    double val1 = OutpData -> val1;
    double val2 = OutpData -> val2;

    switch(OutpData -> outpflag)
    {

        case INF_ROOTS:         printf("infitely many solutions"); break;
        case NO_ROOTS:          printf("no solutions"); break;
        case ONE_ROOT:          printf("solution is %.*lf", prec, val1); break;
        case TWO_ROOTS:         printf("solutions are %.*lf and %.*lf", prec, val1 + val2,
            prec, val1 - val2); break;
        case TWO_COMPLEX_ROOTS: printf("solutions are %.*lf+%.*lfi and %.*lf-%.*lfi",
            prec, val1, prec, val2, prec, val1, prec, val2); break;
        default:                printf("Output error");
    }

    return ErrorStruct {};
}

int PrecisionInput()
{
    int prec = 0;
    int counter = 0;
    printf("enter precision for answers\n");
    while (counter != 1)
    {
        counter = scanf("%d", &prec);
        ClearBuffer();
        if ( (counter != 1) || ( prec < 0) )
        {
            printf("wrong Input format, try again\n");
        }
    }
    return prec;
}



ErrorStruct SolveStart()
{
    EquationData EquationData {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};
    int prec = 1;


    ErrorStruct SolveStartErr = Input(&EquationData);
    CHECK_ERROR(SolveStartErr);

    prec = PrecisionInput();
    SolveStartErr = SolveEquation(&EquationData);
    CHECK_ERROR(SolveStartErr);

    SolveStartErr = Output(&EquationData, prec);
    CHECK_ERROR(SolveStartErr);

    return SolveStartErr; /* возврат ошибки */
}

void ErrorProcessing(ErrorStruct Errorcode)
{
    switch(Errorcode.Error)
    {
        case NO_ERROR: break;
        case INVALID_ARGUMENT: printf("Invalid argument (NULL pointer). In file %s, in function %s, in line %d\n",
            Errorcode.ErrorFileName, Errorcode.ErrorFuncName, Errorcode.ErrorLineNumber); break;
        case FILE_NOT_OPEN: printf("Invalid argument (Missing test file). In file %s, in function %s, in line %d\n",
            Errorcode.ErrorFileName, Errorcode.ErrorFuncName, Errorcode.ErrorLineNumber); break;
        case BAD_TEST_DATA: printf("Invalid argument (Invalid test parameter) In file %s, in function %s, in line %d\n",
            Errorcode.ErrorFileName, Errorcode.ErrorFuncName, Errorcode.ErrorLineNumber); break;
        default: printf("Unexpected Error code: %d\n", Errorcode.Error); break;
    }
}

ErrorStruct CMDProcessing(int argc, char *argv[])
{
    CHECK_ARGUMENT(argv)

    ErrorStruct Errcode;

    progtarget inp = SOLVE_TARGET;

    inp = ArgIdentifier(argc, argv);

    switch(inp)
    {
        case SOLVE_TARGET: Errcode = SolveStart(); break;
        case HELP_TARGET: printf("Square Equation solver by Mihail Ilyushenkov @2023 v1.0.idkn\nEnter --test to run tests or other to solve your Equation"); break;
#ifdef TEST
        case TEST_TARGET: Errcode = EquationTester(NULL); break;
        case USER_TEST_TARGET: Errcode = EquationTester(argv[2]); break;
#else
        case TEST_TARGET:
        case USER_TEST_TARGET:
#endif
        default: printf("nu error i error (inp not found), che bubnit...."); break;
    }

    return Errcode; /* возврат ошибки */
}


progtarget ArgIdentifier(int argc, char *argv[])
{
    progtarget inp = SOLVE_TARGET;

    if (argc >= 2)
    {
        if (!(strcmp(argv[1], "--help")))
        {
            inp = HELP_TARGET;
        }
#ifdef TEST
        else if (!(strcmp(argv[1], "--test")))
        {
            inp = TEST_TARGET;

            if (argc == 3)
            {
                inp = USER_TEST_TARGET;
            }

        }
#endif
    }
    return inp;
}
