#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "myfunctions.h"
#include <stdlib.h>

/// TODO: Лучше сделать более читабельное название для этого файла, например solveEquation.cpp, поскольку
/// название каждого файла должно отображать функции, которые в нём содержатся.
/// В связи с предыдущим коментарием, лучше будет разбить этот файл на несколько других, например: 

/// test.cpp, test.h - в этих файлах содержаться только функции, которые относятся к тестированию.
/// solveEquation.cpp, solveEquation.h - в этих файлах содержатся остальные функции.
/// errorHandler.h - в этом файле у тебя содержатся определения структур, enum и макросов связанных с ошибками
/// Ты ведь будешь обрабатывать ошибки не только в этом проекте? Так ты сможешь просто скопировать файл для обработки ошибок в следующий 

/// Помимо того, что разделение на файлы с говорящим именем лучше структурирует проект, это помогает 
/// условной компиляции проекта, т. е. в зависимости от некоторого условия компилировать не весь проект, а только некоторую егг часть
/// (это намёк на то, что ещё можно сделать в твоём проекте)

/*!
\file
\brief .cpp файл с телами функций

Данный файл содержит в себе основные функции, используемые в программе
*/

/// TODO: #define лучше будет заменить на static const char*
/// Если есть возможность выбора между макросом и константой - лучше выбирать константу. То же самое относится к выбору между макросом и функцией.
#define TO_RED     "\033[31m"
#define TO_DEFAULT "\033[0m"
#define TO_GREEN   "\033[32m"

/// TODO: Лучше будет выработать привычку оборчивать выражения внутри макроса в скобки
/// т. е 
/// #define EXCEPTION(ERR_CODE) (ErrorStruct{.Error = (ERR_CODE), .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__})
/// Лучше убрать точку с запятой в конце, так как это позволяет его использование без точки с запятой, что портит "стиль" кода, 
/// когда у тебя любая конструкция должна оканчиваться ';'. 
#define EXCEPTION(ERR_CODE) ErrorStruct{.Error = ERR_CODE, .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__};
/// Почему стоит выработать привычку оборачивать в скобки смотри пример:
/// #define SUM(a, b) a + b
/// ...
/// return SUM(x * y, 15) * z;
/// если не будет скобок это раскроется в
/// x * y + 15 * z, что не является тем, что мы ожидали увидеть, поскольку ожидали увидеть мы
/// ((x * y) + 15) * z

void ClearBuffer(void)
{
    int c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        c = getchar();
    }
}

/// TODO: Имена всех функций лучше иметь в едином кодстайле, т.е IsZero, так как в других местах у тебя имена функций в таком кодстайле написаны.
bool iszero(double x)
{
    const double EPS = 1e-4; ///точность сравнения с 0
    return (abs(x) < EPS);
}

ErrorStruct Input(TestData *ReturnData)
{
    /// TODO: Зачем создавать структуру для ошибки, пока у тебя её нет?
    ErrorStruct INPError;

    //------------------------------------------------------------------------// Данный участок коду у тебя повторяется много раз
    if (ReturnData == NULL)                                                   // в разных функциях. Это можно вынести в макрос
    {                                                                         // CHECK_ARGUMENT(PTR)
        /// TODO: return EXCEPTION(INVALID_ARGUMENT);                         //
        return INPError = EXCEPTION(INVALID_ARGUMENT); /* возврат ошибки */   //
    }                                                                         //
    //------------------------------------------------------------------------//

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

    /// TODO: если у тебя будет макрос для обработки ошибко, то переменной INPError, не будет
    /// return ErrorStruct {};
    return INPError; /* возврат ошибки */
}


ErrorStruct SolveEquation(TestData *EquationData)
{
    /// TODO: СHECK_ARGUMENT(EquationData);
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
    /// TODO: СHECK_ARGUMENT(EquationData);
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
    /// TODO: поправить табуляцию, else должен располагаться на том же уровне, что и if
        else
        {
            (EquationData -> outpflag) = ONE_ROOT; /* значение для вывода ответа "есть 1 корень" */
            (EquationData -> val1) = -(EquationData -> b)/(EquationData -> a);
            return LNsolvError; /* возврат ошибки */
        }
    /// TODO: Читабельнее, когда находится один return в конце функции
    /// return ErrorStruct {};
}

ErrorStruct SolveSquareEquation(TestData *EquationData)
{
    /// TODO: СHECK_ARGUMENT(EquationData);
    ErrorStruct ErrInSQS;

    if (EquationData == NULL)
    {
        ErrInSQS = EXCEPTION(INVALID_ARGUMENT);
        return ErrInSQS; /* возврат ошибки */
    }

    double a = EquationData -> a;
    double b = EquationData -> b;
    double c = EquationData -> c;

    /// TODO: пробелы b * b;
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

/// TODO: OutpData не изменяется, лучше передавать по константному указателю
void Output(TestData *OutpData, int prec)
{
    /// TODO: СHECK_ARGUMENT(EquationData);
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

/// TODO: Названия функций лучше сделать в едином кодстайле 
/// ConvertStringToEnum()
/// Лучше передавать по константному указалю, если данные не изменяюются
rootnum Convertstringtoenum(char Enumstring[])
{
    /// TODO: СHECK_ARGUMENT(Enumstring);
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

/// TODO: Дешевле по памяти будет передавать по указателю, так у тебя будет копирование 8 байт, вместо 44
/// ErrorStruct TestOneEq(const TestData* Tdat_ref)
ErrorStruct TestOneEq(TestData Tdat_ref)
{

    ErrorStruct ErrorInTester;

    TestData Tdat_out {.a = Tdat_ref.a, .b = Tdat_ref.b, .c = Tdat_ref.c, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};

    /// TODO: Нет проверки возвращаемого значение, вдруг там ошибка? 
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

/// TODO: TestFileName не изменяется, лучше передавать const char, вместо char 
ErrorStruct EquationTester(char TestFileName[])
{
    /// TODO: СHECK_ARGUMENT(TestFileName);
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
        /// TODO: return EXCEPTION(FILE_NOT_OPEN), чтобы не плодить переменные
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

    /// TODO: return ErrorStruct {};
    return TesterError; /* возврат ошибки */
}

ErrorStruct SolveStart()
{
    TestData EquationData {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};
    int prec = 1;


    Input(&EquationData);
    prec = PrecisionInput();


    /// TODO: Локальные переменные тоже должны быть все в едином кодстайле
    // struct
    ErrorStruct Solvstarterr = SolveEquation(&EquationData);

    /// TODO: Лучше вернуть сразу ошибку, чем запускать код с заведомо ошибочными данными. Обработку ошибки тоже можно обернуть
    /// в макрос CHECK_ERROR
    /*
    if (ErrorStruct.ERROR != NOERROR)
    {
        return Solvstarterr;
    }
    */

    /// TODO: Нет обработки возвращаемого значения
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
    /// TODO: СHECK_ARGUMENT(argv);

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
    /// TODO: СHECK_ARGUMENT(argv);

    progtarget inp = SOLVETAR;

    if (argc >= 2)
    {
        if (!(strcmp(argv[1], "--help")))
        {
            inp = HELPTAR;
        }
        /// TODO: Просто else if будет более читабельно 
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
