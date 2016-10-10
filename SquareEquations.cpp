#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int INF_ROOTS = -1;
const double EPS = 1E-6;

int IsZero(float );
int LinearEquation(double , double , double* );
int SqEquation(double , double , double , double* , double* );
void OutputText();

// TODO:  Подбери название получше. Название функции должно чётко отражать
// содержимое. PrintRoots подходит куда лучше).
void Switcher(int , double, double );


int main()
{
    OutputText();

    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;

    scanf("%lg %lg %lg", &a, &b, &c);

    int nRoots = SqEquation(a, b, c, &x1, &x2);

    Switcher(nRoots, x1, x2);

    return 0;
}

int IsZero(float a)
{
    return fabs(a) < EPS;
}

int LinearEquation(double b, double c, double* x1)
{
    if (IsZero(b) && IsZero(c))
        return INF_ROOTS;
    else if (IsZero(b) && !IsZero(c))
        return 0;
    else if (!IsZero(b) && IsZero(c))
    {
        *x1=0;
        return 1;
    }
    else
    {
        *x1 = -c/b;
        return 1;
    }
}

int SqEquation(double a, double b, double c, double* x1, double* x2)
{
    if (IsZero(a))
        return LinearEquation(b,c,x1);

    double D = b*b-4*a*c;

    if (D < 0)
        return 0;
    else if (D == 0)
    {
        *x1 = -b/(2*a);
        return 1;
    }
    else
    {
        *x1 = (-b+sqrt(D))/(2*a);
        *x2 = (-b-sqrt(D))/(2*a);
        return 2;
    }
}

void OutputText()
{
    printf("SqEquation v1.0, 2016\n");
    printf("Enter a, b, c:\n");
}

void Switcher(int nRoots, double x1, double x2)
{
    switch(nRoots)
    {
    case 2:
        printf("x1 = %lg\n", x1);
        printf("x2 = %lg\n", x2);
        break;

    case 1:
        printf("x = %lg\n" , x1);
        break;

    case 0:
        printf("No roots\n");
        break;

    case INF_ROOTS:
        printf("Infinity roots\n");
        break;

    default:
        printf("Wrong number nRoots:%d\n", nRoots);
    }
}
