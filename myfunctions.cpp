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

ErrorStruct Input(TestData *ReturnData)
{
    ErrorStruct INPError;

    if (ReturnData == NULL)
    {
        return INPError = EXCEPTION(INVALID_ARGUMENT); /* возврат ошибки */
    }


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

    return INPError; /* возврат ошибки */
}


ErrorStruct SolveEquation(TestData *EquationData)
{
    ErrorStruct ERR_in_SolveEquation;

    if (iszero(EquationData -> a))
    {
        ERR_in_SolveEquation = SolveLinearEquation(EquationData);
    }
    else
    {
        ERR_in_SolveEquation = SolveSquareEquation(EquationData);
    }

    return ERR_in_SolveEquation; /* возврат ошибки */
}

ErrorStruct SolveLinearEquation(TestData *EquationData)
{
    ErrorStruct LNsolvError;

    if (EquationData == NULL)
    {
        LNsolvError = EXCEPTION(INVALID_ARGUMENT);
        return LNsolvError; /* возврат ошибки */
    }

    if (iszero(EquationData -> b))
        {
            if (iszero(EquationData -> c))
            {
                (EquationData -> outpflag) = INF_ROOTS; /* значение для вывода ответа "беск. кол-ва корней" */
                return LNsolvError; /* возврат ошибки */
            }
            else
            {
                (EquationData -> outpflag) = NO_ROOTS; /* значение для вывода ответа "нет корней"  */
                return LNsolvError; /* возврат ошибки */
            }
        }
        else
        {
            (EquationData -> outpflag) = ONE_ROOT; /* значение для вывода ответа "есть 1 корень" */
            (EquationData -> val1) = -(EquationData -> b)/(EquationData -> a);
            return LNsolvError; /* возврат ошибки */
        }
}

ErrorStruct SolveSquareEquation(TestData *EquationData)
{
    ErrorStruct ErrInSQS;

    if (EquationData == NULL)
    {
        ErrInSQS = EXCEPTION(INVALID_ARGUMENT);
        return ErrInSQS; /* возврат ошибки */
    }

    double a = EquationData -> a;
    double b = EquationData -> b;
    double c = EquationData -> c;

    double discr = b*b - 4 * a * c;

    EquationData -> val1 = (-b) / (2.0 * a);
    EquationData -> val2 = sqrt(abs(discr)) / (2.0 * a);

    if (iszero(discr))
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
    return ErrInSQS; /* возврат ошибки */

}

void Output(TestData *OutpData, int prec)
{
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

ErrorStruct TestOneEq(TestData Tdat_ref)
{

    ErrorStruct ErrorInTester;

    TestData Tdat_out {.a = Tdat_ref.a, .b = Tdat_ref.b, .c = Tdat_ref.c, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};


    SolveEquation(&Tdat_out);

    if ( !iszero(Tdat_ref.val1 - Tdat_out.val1) || !iszero(Tdat_ref.val2 - Tdat_out.val2) || !iszero(Tdat_ref.outpflag - Tdat_out.outpflag) )
    {
        printf(TO_RED "Test Failed!!!\n" TO_DEFAULT);
        printf("Expected: val1 = %lf, val2 = %lf. Exected: val2 = %lf, val2 = %lf \n", Tdat_ref.val1, Tdat_ref.val2, Tdat_out.val1, Tdat_out.val2);
        return ErrorInTester; /* возврат не ошибки */
    }
    else
    {
        printf(TO_GREEN "Test passed succesfully.\n" TO_DEFAULT);
        return ErrorInTester; /* возврат не ошибки */
    }
}

ErrorStruct EquationTester(char TestFileName[])
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

        TesterError = TestOneEq(Tdata);
        Tdata = {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};
        ScansCnt = fscanf(file, "%lf %lf %lf %lf %lf %s", &(Tdata.a), &(Tdata.b), &(Tdata.c), &(Tdata.val1), &(Tdata.val2), Enumstring);
    }

    return TesterError; /* возврат ошибки */
}

ErrorStruct SolveStart()
{
    TestData EquationData {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};
    int prec = 1;


    Input(&EquationData);
    prec = PrecisionInput();


    // struct
    ErrorStruct Solvstarterr = SolveEquation(&EquationData);

    /*
    if (ErrorStruct.ERROR != NOERROR)
    {
        return Solvstarterr;
    }
    */

    Output(&EquationData, prec);
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

    switch(inp)
    {
        case SOLVETAR: Errcode = SolveStart(); break;
        case HELPTAR: printf("Square Equation solver by Mihail Ilyushenkov @2023 v1.0.idkn\nEnter --test to run tests or other to solve your Equation"); break;
        case TESTTAR: Errcode = EquationTester(NULL); break;
        case USTESTTAR:Errcode = EquationTester(argv[2]); break;
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
