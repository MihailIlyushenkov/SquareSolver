#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "SolveFunctions.h"
#include "TestFunctions.h"
#include <stdlib.h>

/*!
\file
\brief .cpp файл с телами функций

Данный файл содержит в себе побочные функции, используемые в программе тестирования
*/

ErrorStruct EquationTester(const char TestFileName[])
{

    ErrorStruct TesterError;

    FILE *file;

    if (TestFileName == NULL)
    {
        file = fopen("TestData.txt", "r");
    }
    else
    {
        file = fopen(TestFileName, "r");
    }

    if (file == NULL)
        return EXCEPTION(FILE_NOT_OPEN); /* возврат ошибки */

    char Enumstring[12] = {0};
    EquationData Tdata = {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};
    int ScansCnt = fscanf(file, "%lf %lf %lf %lf %lf %s", &(Tdata.a), &(Tdata.b), &(Tdata.c), &(Tdata.val1), &(Tdata.val2), Enumstring);

    while (ScansCnt != EOF)
    {
        if (ScansCnt != 6)
        {
            return EXCEPTION(BAD_TEST_DATA);
        }

        Tdata.outpflag = ConvertStringToEnum(Enumstring);

        TesterError = TestOneEq(&Tdata);
        Tdata = {.a = 0, .b = 0, .c = 0, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};
        ScansCnt = fscanf(file, "%lf %lf %lf %lf %lf %s", &(Tdata.a), &(Tdata.b), &(Tdata.c), &(Tdata.val1), &(Tdata.val2), Enumstring);
    }

    return ErrorStruct {}; /* возврат ошибки */
}


ErrorStruct TestOneEq(const EquationData* Tdat_ref)
{
    CHECK_ARGUMENT(Tdat_ref);

    EquationData Tdat_out {.a = Tdat_ref ->a, .b = Tdat_ref ->b, .c = Tdat_ref ->c, .val1 = 0, .val2 = 0, .outpflag = NO_ROOTS};

    ErrorStruct ErrorInTester = SolveEquation(&Tdat_out);
    CHECK_ERROR(ErrorInTester);

    if ( !IsZero(Tdat_ref ->val1 - Tdat_out.val1) || !IsZero(Tdat_ref ->val2 - Tdat_out.val2) || !IsZero(Tdat_ref ->outpflag - Tdat_out.outpflag) )
    {
        printf(TO_RED "Test Failed!!!\n" TO_DEFAULT);
        printf("Expected: val1 = %lf, val2 = %lf. Exected: val2 = %lf, val2 = %lf \n", Tdat_ref ->val1, Tdat_ref ->val2, Tdat_out.val1, Tdat_out.val2);
    }
    else
    {
        printf(TO_GREEN "Test passed succesfully.\n" TO_DEFAULT);
    }

    return ErrorStruct {};
}

rootnum ConvertStringToEnum(const char Enumstring[])
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
