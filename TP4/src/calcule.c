#include <stdio.h>
#include <stdlib.h>
#include "operator.h"

int main(int argc, char **argv)
{
    int num1;
    int num2;
    int resultat;
    char *fin;

    if (argc != 4 || argv[1][0] == '\0' || argv[1][1] != '\0') {
        fprintf(stderr, "Usage : %s OPERATEUR NOMBRE1 NOMBRE2\n", argv[0]);
        return 1;
    }
    num1 = (int)strtol(argv[2], &fin, 10);
    if (*fin != '\0') return fprintf(stderr, "Nombre invalide.\n"), 1;
    num2 = (int)strtol(argv[3], &fin, 10);
    if (*fin != '\0') return fprintf(stderr, "Nombre invalide.\n"), 1;
    if (calculer(num1, num2, argv[1][0], &resultat) != 0) {
        fprintf(stderr, "Operation invalide ou division par zero.\n");
        return 1;
    }
    printf("Resultat : %d\n", resultat);
    return 0;
}