#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

void cleaner(void);
void input(double *a, double *b, double *c);
void solver(double a, double b, double c, int *outpflag, double *val0_ip, double *val1_ip);
void output(double *val0_ip, double *val1_ip, int *outpflag_ip);

#endif /*MYFUNCTIONS_H*/
