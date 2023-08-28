#include <stdio.h>
#include <math.h>
#include "SolveFunctions.h"
#include <string.h>


///\file
///\brief Основной файл программы, решающей квадратное уравнение.

/*! \mainpage
* Реализована возможность решать квадратные уравнения, введенные в консоль
*
* Реализована возможность тестирования через кастомный файл

*/

int main(int argc, char *argv[])
{
    ErrorStruct MainError;

    MainError = CMDProcessing(argc, argv);

    ErrorProcessing(MainError);

    getchar();

    return 0;
}
