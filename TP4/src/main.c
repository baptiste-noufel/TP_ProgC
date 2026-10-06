#include <stdio.h>
#include "operator.h"

int main(void)
{
    int num1;
    int num2;
    int resultat;
    char operateur;

    printf("Entrez num1, num2 et l'operateur : ");
    if (scanf("%d %d %c", &num1, &num2, &operateur) != 3 ||
        calculer(num1, num2, operateur, &resultat) != 0) {
        fprintf(stderr, "Operation invalide ou division par zero.\n");
        return 1;
    }
    printf("Resultat : %d\n", resultat);
    return 0;
}
