#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

/*!
\file
\brief Заголовочный файл с описанием функций, структур и перечислений

Данный файл содержит в себе определения основных функций, структур и перечислений, используемых в программе
*/




/// Набор возможных параметров для функции Output()
enum rootnum
{
    INF_ROOTS = -1, ///< Указывает, что ответ нужно вывести в формате "корней бесконечно много"
    NO_ROOTS, ///< Указывает, что ответ нужно вывести в формате "корней нет"
    ONE_ROOT, ///< Указывает, что ответ нужно вывести в формате "только 1 корень"
    TWO_ROOTS, ///< Указывает, что ответ нужно вывести в формате "2 действительных корня"
    // TWO_COMPLEX_ROOTS
    TWO_COMPLEX_ROOTS ///< Указывает, что ответ нужно вывести в формате "2 копмлексных корня"
};

/*! Набор возможных кодов ошибок */
enum errortype
{
    NOERROR = 0, ///< Указывает, что ошибки не выявлено
    //INVALID_ARGUMENT
    INVALID_ARGUMENT, ///< Указывает, что один из аргументов-указателей для функции был нулем
    //FILE_NOT_OPEN
    FILE_NOT_OPEN, ///< Указывает, что файл для тестирования не был открыт
    // ???
    BAD_TEST_DATA ///< Указывает, что в файле для тестирования были некорректные данные для тестов
};

/// Набор возможных целей для программы, выявленных после обработки командной строки
enum progtarget
{
    // SOLVE_TARGET
    SOLVETAR = 0, ///<Указывает, что целью является решение уравнения, которое должен ввести пользователь
    TESTTAR, ///< Указывает, что целью является прогонка тестов из дефолтного файла (Testdata.txt)
    HELPTAR, ///< Указывает, что целью является вывод информации для помощи пользователю
    USTESTTAR ///< Указывает, что целью является прогонка тестов кастомного файла (создается пользователем, адрес вводится в качестве аргумента командной строки после --test
};

/*!
	\brief Струкрута, используемая функцией TestOneEQ для принятия параметров теста
*/

// EquationData
struct TestData
{
    double a; ///< Отвечает за коэффицент а в уравнении
    double b; ///< Отвечает за коэффицент b в уравнении
    double c; ///< Отвечает за коэффицент с в уравнении
    double val1; ///< Отвечает за значение -b/2a в решении уравнения
    double val2; ///< Отвечает за значение sqrt(discr)/2a, где discr = b**2 - 4ac, sqrt - квадратный корень
    rootnum outpflag; ///< Отвечает за вспомогательный параметр для корректного вывода итоговых решений
};

/*!
	\brief Структура, используемая всеми функциями типа ErrorStruct для возврата данных об ошибках (или их отстутствии)
*/

struct ErrorStruct
{
    errortype Error = NOERROR;
    const char *ErrorFileName = NULL;
    int ErrorLineNumber = 0;
    const char *ErrorFuncName = NULL;
};

/*!
Функция для очистки потока ввода. Без параметров.
*/
void ClearBuffer(void);

/*!
функция, сравнивающая число с заранее заданной константой EPS, близкой к 0.
\param[in] x сравниваемое число
\return возвращаемое булевое значение. True, если |x| < EPS, иначае False
*/
bool iszero(double x);

/*!
Вызывает SolveLinearEquation или SolveSquareEquation в зависимости от параметров a, b, c
\param[in] EquasionData - структура с данными для решения уравнения с
\param[out] outpflag указатель на служебный параметр для вывода в стрктуре
\param[out] val1 параметр val0 в структуре
\param[out] val2 параметр val1 в структуре
\return Структура с информацией об ошибках
*/
ErrorStruct SolveEquation(TestData *EquasionData);

/*!
Обрабатывает ввод из консоли. При неверных данных просит ввести их повторно. Также вызывает ClearBuffer()
\param[in] EquasionData - указатель на структуру с данными для решения уравнения
\param[out] EquasionData->a коэффицент a
\param[out] EquasionData->b коэффицент b
\param[out] EquasionData->c коэффицент c
\return Структура с информацией об ошибках
*/
ErrorStruct Input(TestData *ReturnData);

/*!
Решает линейное уравнение ax + b = 0
\param[in] EquasionData указатель на структуру с данными для решения уравнения

\param[out] EquasionData->val0 значение корня, если таковой имеется
\param[out] EquasionData->outpflag служебное значение для вывода в функции Output()
\return Структура с информацией об ошибках
*/
ErrorStruct SolveLinearEquation(TestData *EquasionData);


/*!
Решает квадратное  уравнение  ax^2 + bx + c = 0
\param[in] EquasionData указатель на структуру с данными для решения уравнения
\param[out] EquasionData->val1 записывает первую часть ответа, равную -b/2a
\param[out] EquasionData->val2 записывает вторую часть ответа, равную sqrt(discr)/2a, где discr = b**2 - 4ac, sqrt - квадратный корень
\param[out] EquasionData->outpflag записывает служебное значение для вывода в функции Output()
\return Структура с информацией об ошибках
*/
ErrorStruct SolveSquareEquation(TestData *EquasionData);


/*!
функция вывода данных в консоль из функции solver()
\param[in] OutpData структура с данными решенного уравнения
\param[in] prec количество знаков после запятой при выводе ответа
*/
void Output(TestData *OutpData, int prec);


/*!
возвращает 1 натуральное число, введенное с клавиатуры
\return натуральное число
*/
int PrecisionInput();


/*!
Вызыывает функцию TestOneEq количество TestCounter раз и передает ей данные, из файла, введенного пользователем.
Если таковой не указан, то будет открыт файл Testdata.txt
\param[in] Testfilename имя файла с тестами
\return Структура с информацией об ошибках
*/
ErrorStruct EquationTester(char Testfilename[]);


ErrorStruct TestOneEq(TestData Tdat);
/*!
Тестирует програму решения уравнения
\param[in] TestData Структура, содержащая коэффиценты уравнения и эталонные решения для них
\return Структура с информацией об ошибках
*/

/*!
конвертирует строку в заранее заданный enum (rootnum)
\param[in] строка для конвертации
\return enum rootnum, если строка идентична одному из enum rootnum, иначе возвращает дефолтное значение NO_ROOTS
*/
rootnum Convertstringtoenum(char Enumstring[]);


/*!
обрабатывает ошибку в main()
\param[in] Структура, содержащая данные об ошибках ранее вызванных функций
*/
void ErrorProcessing(ErrorStruct MainError);


/*!
обрабатывает аргументы командной строки при запуске main.exe
\param[in] argc кол-во аргументов командной строки
\param[in] массив аргументов командной строки
\return Структура с информацией об ошибках
*/
ErrorStruct CMDProcessing(int argc, char *argv[]);


/*!
инициализирует начало решения уравнения
\return Структура с информацией об ошибках
*/
ErrorStruct SolveStart();

/*!
определяет непосредственно аргументы ком. строки и переводит их в enum progtarget
\param[in] argc кол-во аргументов командной строки
\param[in] argv[] аргументы командной строки
\return progtarget для дальнейшей обработки в CMDProcessing()
*/
progtarget Arg_Identifier(int argc, char *argv[]);

#endif /*MYFUNCTIONS_H*/
