#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

/*!
\file
\brief Заголовочный файл с описанием функций, структур и перечислений

Данный файл содержит в себе определения основных функций, структур и перечислений, используемых в файле SolveFunctions.cpp
*/

#define TO_RED "\033[31m"
#define TO_DEFAULT "\033[0m"
#define TO_GREEN "\033[32m"


#define EXCEPTION(ERR_CODE) (ErrorStruct{.Error = ERR_CODE, .ErrorFileName = __FILE__, .ErrorLineNumber = __LINE__, .ErrorFuncName = __PRETTY_FUNCTION__})

#define CHECK_ARGUMENT(PTR) if (PTR == NULL) { return EXCEPTION(INVALID_ARGUMENT); }

#define CHECK_ERROR(ErrorStruct) if (ErrorStruct.Error != NO_ERROR) { return ErrorStruct; }

/// Набор возможных параметров для функции Output()
enum rootnum
{
    INF_ROOTS = -1, ///< Указывает, что ответ нужно вывести в формате "корней бесконечно много"
    NO_ROOTS, ///< Указывает, что ответ нужно вывести в формате "корней нет"
    ONE_ROOT, ///< Указывает, что ответ нужно вывести в формате "только 1 корень"
    TWO_ROOTS, ///< Указывает, что ответ нужно вывести в формате "2 действительных корня"
    TWO_COMPLEX_ROOTS ///< Указывает, что ответ нужно вывести в формате "2 копмлексных корня"
};

/*! Набор возможных кодов ошибок */
enum errortype
{
    NO_ERROR = 0, ///< Указывает, что ошибки не выявлено
    INVALID_ARGUMENT, ///< Указывает, что один из аргументов-указателей для функции был нулем
    FILE_NOT_OPEN, ///< Указывает, что файл для тестирования не был открыт
    BAD_TEST_DATA ///< Указывает, что в файле для тестирования были некорректные данные для тестов
};

/// Набор возможных целей для программы, выявленных после обработки командной строки
enum progtarget
{
    /// TODO: Исправить правки, которые я тут оставил
    SOLVE_TARGET = 0, ///<Указывает, что целью является решение уравнения, которое должен ввести пользователь
    TEST_TARGET, ///< Указывает, что целью является прогонка тестов из дефолтного файла (EquationData.txt)
    HELP_TARGET, ///< Указывает, что целью является вывод информации для помощи пользователю
    USER_TEST_TARGET ///< Указывает, что целью является прогонка тестов кастомного файла (создается пользователем, адрес вводится в качестве аргумента командной строки после --test
};

/*!
	\brief Струкрута, используемая функциями для принятия данных по уравнению
*/

struct EquationData
{
    double a = 0; ///< Отвечает за коэффицент а в уравнении
    double b = 0; ///< Отвечает за коэффицент b в уравнении
    double c = 0; ///< Отвечает за коэффицент с в уравнении
    double val1 = 0; ///< Отвечает за значение -b/2a в решении уравнения
    double val2 = 0; ///< Отвечает за значение sqrt(discr)/2a, где discr = b**2 - 4ac, sqrt - квадратный корень
    rootnum outpflag = NO_ROOTS; ///< Отвечает за вспомогательный параметр для корректного вывода итоговых решений
};

/*!
	\brief Структура, используемая всеми функциями типа ErrorStruct для возврата данных об ошибках (или их отстутствии)
*/

struct ErrorStruct
{
    errortype Error = NO_ERROR;
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
bool IsZero(double x);

/*!
Вызывает SolveLinearEquation или SolveSquareEquation в зависимости от параметров a, b, c
\param[in] EquasionData - структура с данными для решения уравнения с
\param[out] outpflag указатель на служебный параметр для вывода в стрктуре
\param[out] val1 параметр val0 в структуре
\param[out] val2 параметр val1 в структуре
\return Структура с информацией об ошибках
*/
ErrorStruct SolveEquation(EquationData *EquasionData);

/*!
Обрабатывает ввод из консоли. При неверных данных просит ввести их повторно. Также вызывает ClearBuffer()
\param[in] EquasionData - указатель на структуру с данными для решения уравнения
\param[out] EquasionData->a коэффицент a
\param[out] EquasionData->b коэффицент b
\param[out] EquasionData->c коэффицент c
\return Структура с информацией об ошибках
*/
ErrorStruct Input(EquationData *ReturnData);

/*!
Решает линейное уравнение ax + b = 0
\param[in] EquasionData указатель на структуру с данными для решения уравнения

\param[out] EquasionData->val0 значение корня, если таковой имеется
\param[out] EquasionData->outpflag служебное значение для вывода в функции Output()
\return Структура с информацией об ошибках
*/
ErrorStruct SolveLinearEquation(EquationData *EquasionData);


/*!
Решает квадратное  уравнение  ax^2 + bx + c = 0
\param[in] EquasionData указатель на структуру с данными для решения уравнения
\param[out] EquasionData->val1 записывает первую часть ответа, равную -b/2a
\param[out] EquasionData->val2 записывает вторую часть ответа, равную sqrt(discr)/2a, где discr = b**2 - 4ac, sqrt - квадратный корень
\param[out] EquasionData->outpflag записывает служебное значение для вывода в функции Output()
\return Структура с информацией об ошибках
*/
ErrorStruct SolveSquareEquation(EquationData *EquasionData);


/*!
функция вывода данных в консоль из функции solver()
\param[in] OutpData структура с данными решенного уравнения
\param[in] prec количество знаков после запятой при выводе ответа
*/
ErrorStruct Output(const EquationData *OutpData, int prec);


/*!
возвращает 1 натуральное число, введенное с клавиатуры
\return натуральное число
*/
int PrecisionInput();





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
progtarget ArgIdentifier(int argc, char *argv[]);

#endif /*MYFUNCTIONS_H*/
