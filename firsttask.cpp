#include <stdio.h>
#include <math.h>
#include "myfunctions.h"
#include <string.h>

/// TODO: Обычно файл с функцией main называют main.cpp, так смотря на стркутуру файлов сразу понятно с какого файла начинать смотреть проект
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
