#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "myfunctions.h"
#include <stdlib.h>


/*!
\file
\brief .cpp файл с телами функций

Данный файл содержит в себе основные функции, используемые в программе
*/


#define TO_RED     "\033[31m"
#define TO_DEFAULT "\033[0m"
#define TO_GREEN   "\033[32m"

#define EXCEPTION(ERR_CODE) ErrorStruct{.Error = ERR_CODE, .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__};

void ClearBuffer(void)
{
    int c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
    }
}

bool iszero(double x)
{
    const double EPS = 1e-4; ///точность сравнения с 0
    return (abs(x) < EPS);
}

ErrorStruct Input(double *a_ptr, double *b_ptr, double *c_ptr)
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
        ClearBuffer();
        if (counter != 3)
        {
            printf("wrong Input format, try again\n");
        }
    }

    return INPError; /* возврат ошибки */
}


ErrorStruct SolveEquation(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{
    ErrorStruct ERR_in_SolveEquation;

    if (iszero(a))
    {
        ERR_in_SolveEquation = SolveLinearEquation(b, c, val0_ptr, outpflag_ptr);
    }
    else
    {
        ERR_in_SolveEquation = SolveSquareEquation(a, b, c, outpflag_ptr, val0_ptr, val1_ptr);
    }

    return ERR_in_SolveEquation; /* возврат ошибки */
}

ErrorStruct SolveLinearEquation(double a, double b, double *val0_ptr, rootnum *outpflag_ptr)
{
    ErrorStruct LNsolvError;

    if (val0_ptr == NULL || outpflag_ptr == NULL)
    {
                //  = EXCEPTION(INVALID_ARGUMENT);
        LNsolvError = EXCEPTION(INVALID_ARGUMENT);
        return LNsolvError; /* возврат ошибки */
    }

    if (iszero(a))
        {
            if (iszero(b))
            {
                *outpflag_ptr = INF_ROOTS; /* значение для вывода ответа "беск. кол-ва корней" */
                return LNsolvError; /* возврат ошибки */
            }
            else
            {
                *outpflag_ptr = NO_ROOTS; /* значение для вывода ответа "нет корней"  */
                return LNsolvError; /* возврат ошибки */
            }
        }
        else
        {
            *outpflag_ptr = ONE_ROOT; /* значение для вывода ответа "есть 1 корень" */
            *val0_ptr = (-b)/a;
            return LNsolvError; /* возврат ошибки */
        }
}

ErrorStruct SolveSquareEquation(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr)
{
    ErrorStruct ErrInSQS;
    if (val0_ptr == NULL || val1_ptr == NULL || outpflag_ptr == NULL)
    {
        ErrInSQS = EXCEPTION(INVALID_ARGUMENT);
        return ErrInSQS; /* возврат ошибки */
    }
                 //data->b * data->b
    double discr = b*b - 4 * a * c;
    // data->x1 = ...
    *val0_ptr = (-b) / (2.0 * a);
    *val1_ptr = sqrt(abs(discr)) / (2.0 * a);

    if (iszero(discr))
    {
        *outpflag_ptr = ONE_ROOT; /* значение для вывода ответа "есть 1 действ. корень" */
    }
    else if ( discr > 0 )
    {
        *outpflag_ptr = TWO_ROOTS; /* значение для вывода ответа "есть 2 действ. корня" */
    }
    else
    {
        *outpflag_ptr = TWO_COMPLEX_ROOTS; /* значение для вывода ответа "есть 2 комплексных корня" */
    }
    return ErrInSQS; /* возврат ошибки */

}

void Output(double *val0_ptr, double *val1_ptr, rootnum outpflag_ptr, int prec)
{
    switch(outpflag_ptr)
    {

        case INF_ROOTS:         printf("infitely many solutions"); break;
        case NO_ROOTS:          printf("no solutions"); break;
        case ONE_ROOT:          printf("solution is %.*lf", prec, *val0_ptr); break;
        case TWO_ROOTS:         printf("solutions are %.*lf and %.*lf", prec, *val0_ptr + *val1_ptr,
            prec, *val0_ptr - *val1_ptr); break;
        case TWO_COMPLEX_ROOTS: printf("solutions are %.*lf+%.*lfi and %.*lf-%.*lfi",
            prec, *val0_ptr, prec, *val1_ptr, prec, *val0_ptr, prec, *val1_ptr); break;
        default:                printf("Output error");
    }
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

rootnum Convertstringtoenum(char Enumstring[])
{
    if (!(strcmp(Enumstring, "INF_ROOTS")))
    {
        return INF_ROOTS;
    }
    else if (!(strcmp(Enumstring, "NO_ROOTS")))
    {
        return NO_ROOTS;
    }
    else if (!(strcmp(Enumstring, "ONE_ROOT")))
    {
        return ONE_ROOT;
    }
    else if (!(strcmp(Enumstring, "TWO_ROOTS")))
    {
        return TWO_ROOTS;
    }
    else if (!(strcmp(Enumstring, "TWO_COMPLEX_ROOTS")))
    {
        return TWO_COMPLEX_ROOTS;
    }
    return NO_ROOTS;
}

ErrorStruct TestOneEq(TestData *Tdat)
{

    double val1 = 0, val2 = 0;
    rootnum outpflag = NO_ROOTS;

    ErrorStruct ErrorInTester;

    if (Tdat == NULL)
    {
        ErrorInTester = EXCEPTION(INVALID_ARGUMENT);
        return ErrorInTester; /* возврат ошибки */
    }


    SolveEquation(Tdat -> a, Tdat -> b, Tdat -> c, &outpflag, &val1, &val2);


    if ( !iszero(val1 - (Tdat -> val1)) || !iszero(val2 - (Tdat -> val2)) || !iszero(outpflag != (Tdat -> outpflag)) )
    {
        printf(TO_RED "Test Failed!!!\n" TO_DEFAULT);
        printf("Expected: val1 = %lf, val2 = %lf. Exected: val1 = %lf, val2 = %lf \n", Tdat -> val1, Tdat -> val2, val1, val2);
        return ErrorInTester; /* возврат не ошибки */
    }
    else
    {
        printf(TO_GREEN "Test passed succesfully.\n" TO_DEFAULT);
        return ErrorInTester; /* возврат не ошибки */
    }
}

ErrorStruct EquasionTester(char TestFileName[])
{

    ErrorStruct TesterError;
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
        return TesterError = EXCEPTION(FILE_NOT_OPEN); /* возврат ошибки */

    char Enumstring[12] = {0};
    TestData Tdata = {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};
    int ScansCnt = fscanf(file, "%lf %lf %lf %lf %lf %s", &(Tdata.a), &(Tdata.b), &(Tdata.c), &(Tdata.val1), &(Tdata.val2), Enumstring);

    while (ScansCnt != EOF)
    {
        if (ScansCnt != 6)
        {
            return TesterError = EXCEPTION(BAD_TEST_DATA);
        }

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


    Input(&a, &b, &c);
    prec = PrecisionInput();

                                    // struct
    ErrorStruct Solvstarterr = SolveEquation(a, b, c, &outpflag, &val0, &val1);

    /*
    if (ErrorStruct.ERROR != NOERROR)
    {
        return Solvstarterr;
    }
    */

    Output(&val0, &val1, outpflag, prec);
    return Solvstarterr; /* возврат ошибки */
}

void ErrorProcessing(ErrorStruct Errorcode)
{
    switch(Errorcode.Error)
    {
        case NOERROR: break;
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
    ErrorStruct Errcode;

    progtarget inp = SOLVETAR;

    inp = Arg_Identifier(argc, argv);

    // вынести в отдельную ф-ию


    /*
    if (Errcode.Error != NOERROR)
    {
        return Errcode;
    }
    */

    switch(inp)
    {
        case SOLVETAR: Errcode = SolveStart(); break;
        case HELPTAR: printf("Square equasion solver by Mihail Ilyushenkov @2023 v1.0.idkn\nEnter --test to run tests or other to solve your equasion"); break;
        case TESTTAR: Errcode = EquasionTester(NULL); break;
        case USTESTTAR:Errcode = EquasionTester(argv[2]); break;
        default: printf("nu error i error (inp not found), che bubnit...."); break;
    }

    return Errcode; /* возврат ошибки */
}


progtarget Arg_Identifier(int argc, char *argv[])
{
    progtarget inp = SOLVETAR;

    if (argc >= 2)
    {
        if (!(strcmp(argv[1], "--help")))
        {
            inp = HELPTAR;
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

    return inp;
}
