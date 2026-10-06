#include "operator.h"

int calculer(int num1, int num2, char operateur, int *resultat)
{
    switch (operateur) {
    case '+':
        *resultat = num1 + num2;
        return 0;
    case '-':
        *resultat = num1 - num2;
        return 0;
    case '*':
        *resultat = num1 * num2;
        return 0;
    case '/':
        if (num2 == 0) return 1;
        *resultat = num1 / num2;
        return 0;
    case '%':
        if (num2 == 0) return 1;
        *resultat = num1 % num2;
        return 0;
    case '&':
        *resultat = num1 & num2;
        return 0;
    case '|':
        *resultat = num1 | num2;
        return 0;
    case '~':
        *resultat = ~num1;
        return 0;
    default:
        return 1;
    }
}