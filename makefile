CC = g++
CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: EQSolver

test: main.o SolveEquationWithTest.o TestProgramm.o
	$(CC) Objects\main.o Objects\SolveEquation.o Objects\TestProgramm.o -o main.exe

EQSolver: main.o SolveEquation.o
	$(CC) Objects\main.o Objects\SolveEquation.o -o main.exe

main.o: Sources\main.cpp
	$(CC) $(CFLAGS) -c Sources\main.cpp -o Objects\main.o

SolveEquation.o: Sources\SolveEquation.cpp
	$(CC) $(CFLAGS) -c Sources\SolveEquation.cpp -o Objects\SolveEquation.o

SolveEquationWithTest.o: Sources\SolveEquation.cpp
	$(CC) $(CFLAGS) -DTEST -c Sources\SolveEquation.cpp -o Objects\SolveEquation.o

TestProgramm.o: Sources\TestProgramm.cpp
	$(CC) $(CFLAGS) -c Sources\TestProgramm.cpp -o Objects\TestProgramm.o

clean:
	del Objects\*.o *.exe
