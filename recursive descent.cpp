#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//!Functions Get;
double GetG0  ();
double GetT   ();
double GetE   ();
double GetP   ();
double GetN   ();

//!Function get expression
int    get_exp();


char *s;

int main()
{
    get_str();
    char *str = s;
    double res = GetG0();

    printf("%.3f\n", res);

    free(str);

    system("pause");

    return 0;
}

int get_str()
{
    s = (char *)calloc(100, sizeof(char));

    fgets(s, 100, stdin);
    s[strlen(s) - 1] = '\0';

    return 0;
}

double GetG0()
{

    double res = GetE();
    assert (*s == '\0');

    return res;
}

double GetE()
{
    double res = GetT();

    while (*s == '+' || *s == '-')
    {
        char op = *s;
        s++;

        double res2 = GetT();
        if (op == '+')
            res += res2;
        if (op == '-')
            res -= res2;
    }

    return res;
}

double GetT()
{
    double res = GetP();

    while (*s == '*' || *s == '/')
    {
        char op = *s;
        s++;

        double res2 = GetP();
        if (op == '*')
            res *= res2;
        if (op == '/')
            res /= res2;
    }

    return res;
}

double GetP()
{
    if (*s == '(')
    {
        s++;

        double res = GetE();
        assert(*s == ')');
        s++;

        return res;
    }
    else
        return GetN();
}

double GetN()
{
    double res = 0;

    while ('0' <= *s && *s <= '9')
        res = res*10 + *s++ - '0';

    return res;
}
