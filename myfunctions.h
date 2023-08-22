#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

void cleaner(void);
/* ощищает поток ввода */

bool iszero(double x);
/* сравнивает double x с заранее заданной констатной EPS, близкой к 0. Выдает 1 если x < EPS, иначе 0) */

void extdef(double a, double b, double c, int *outpflag_ip, double *val0_ip, double *val1_ip);
/* вызывает linearsolver или squaresolver в зависимости от параметров a, b, c*/

void input(double *a_ip, double *b_ip, double *c_ip, int *pres_ip);
/* обрабатывает ввод. При неверных данных просит ввести их повторно. Также вызывает cleaner() */

void linearsolver(double a, double b, double *val0_ip, int *outpflag_ip);
/* решает квадратное уравнение ax + b = 0.
Записывает корень, если таковой имеется в val0_ip и служебную переменную для вывода в *outpflag_ip */

void squaresolver(double a, double b, double c, int *outpflag_ip, double *val0_ip, double *val1_ip);
/* Выполняет вычисления для решения уравнения. Получает на ввод данные коэффиценты a, b, c,
а также указатели outpflag_ip - служебную переменную для функции output() и
val0_ip (= -b/2a) и val1_ip (= sqrt(b^2 - 4ac)/2a ) -
    данные для вывода в функции  output(), которые записывает в процессе работы */

void output(double *val0_ip, double *val1_ip, int *outpflag_ip, int pres);
/* функция вывода данных в консоль из функции solver().
Получает на ввод указатели на служебную переменную и 2 значения для вывода. */


#endif /*MYFUNCTIONS_H*/
