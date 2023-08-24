#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

enum rootnum
{
    INFROOTS = -1, NOROOTS, ONEROOT, TWOROOTS, TWOCMPROOTS
};

enum errortype
{
    NOERROR = 0, BAD_NULL_PTR, FILENOTOPEN
};

enum progtarget
{
    SOLVETAR = 0, TESTTAR, HELPTAR, USTESTTAR
};

struct TestData
{
    double a;
    double b;
    double c;
    double val1;
    double val2;
    rootnum outpflag;
};

struct ErrorStruct
{
    errortype Error = NOERROR;
    const char *ErrorFileName = NULL;
    int ErrorLineNumber = 0;
    const char *ErrorFuncName = NULL;
};

void cleaner(void);
/* ощищает поток ввода */

bool iszero(double x);
/* сравнивает double x с заранее заданной констатной EPS, близкой к 0. Выдает 1 если x < EPS, иначе 0) */

ErrorStruct eqsdef(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr);
/* вызывает linearsolver или squaresolver в зависимости от параметров a, b, c*/

ErrorStruct input(double *a_ptr, double *b_ptr, double *c_ptr);
/* обрабатывает ввод. При неверных данных просит ввести их повторно. Также вызывает cleaner() */

ErrorStruct linearsolver(double a, double b, double *val0_ptr, rootnum *outpflag_ptr);
/* решает квадратное уравнение ax + b = 0.
    Записывает корень, если таковой имеется в val0_ptr и служебную переменную для вывода в *outpflag_ptr */

ErrorStruct squaresolver(double a, double b, double c, rootnum *outpflag_ptr, double *val0_ptr, double *val1_ptr);
/* Выполняет вычисления для решения уравнения. Получает на ввод данные коэффиценты a, b, c,
    а также указатели outpflag_ptr - служебную переменную для функции output() и
    val0_ptr (= -b/2a) и val1_ptr (= sqrt(b^2 - 4ac)/2a ) -
    данные для вывода в функции  output(), которые записывает в процессе работы */

void output(double *val0_ptr, double *val1_ptr, rootnum outpflag_ptr, int prec);
/* функция вывода данных в консоль из функции solver().
    Получает на ввод указатели на служебную переменную и 2 значения для вывода. */

int precision_input();
/* возвращает 1 натуральное число, введенное с клавиатуры */

ErrorStruct EquasionTester(char Testfilename[]);
/*Вызыывает функцию TestOneEq количество TestCounter раз и передает ей данные
    из Testdata.txt*/

ErrorStruct TestOneEq(TestData *Tdat);
#endif /*MYFUNCTIONS_H*/

rootnum Convertstringtoenum(char Enumstring[]);
/* конвертирует строку в заранее заданный ENUM rootnum */


void ErrorProcessing(ErrorStruct MainError);
/* обрабатывает ошибку в main() */

ErrorStruct CMDProcessing(int argc, char *argv[]);
/* обрабатывает аргументы командной строки при запуске main.exe */

ErrorStruct SolveStart();
/* инициализирует начало решения уравнения */
