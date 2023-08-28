/*!
\file
\brief Заголовочный файл с описанием функций, структур и перечислений

Данный файл содержит в себе определения основных функций, структур и перечислений, используемых в файле TestFunctions.cpp
*/

/*!
Вызыывает функцию TestOneEq до тех пор, пока данные из файла, введенного пользователем, не будут считаны (если они неверного формата, возвращает ошибку).
Если таковой не указан, то будет открыт файл EquationData.txt
\param[in] Testfilename имя файла с тестами
\return Структура с информацией об ошибках
*/
ErrorStruct EquationTester(const char Testfilename[]);

/*!
Тестирует програму решения уравнения
\param[in] EquationData Структура, содержащая коэффиценты уравнения и эталонные решения для них
\return Структура с информацией об ошибках
*/
ErrorStruct TestOneEq(const EquationData* Tdat);


/*!
конвертирует строку в заранее заданный enum (rootnum)
\param[in] строка для конвертации
\return enum rootnum, если строка идентична одному из enum rootnum, иначе возвращает дефолтное значение NO_ROOTS
*/
rootnum ConvertStringToEnum(const char Enumstring[]);
