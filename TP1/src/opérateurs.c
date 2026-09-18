#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int a = 16;
    int b = 3;

    /* 1. Addition */
    printf("Addition (a + b) : %d\n", a + b);

    /* 2. Soustraction */
    printf("Soustraction (a - b) : %d\n", a - b);

    /* 3. Multiplication */
    printf("Multiplication (a * b) : %d\n", a * b);

    /* 4. Division (entière et réelle pour précision) */
    printf("Division entière (a / b) : %d\n", a / b);

    /* 5. Modulo (reste de la division entière) */
    printf("Modulo (a %% b) : %d\n", a % b);

    /* 6. Égalité (a == b) */
    bool est_egal = (a == b);
    printf("Egalite (a == b) : %d (%s)\n", est_egal, est_egal ? "true" : "false");

    /* 7. Comparaison supérieur (a > b) */
    bool est_superieur = (a > b);
    printf("Superieur (a > b) : %d (%s)\n", est_superieur, est_superieur ? "true" : "false");

    return 0;
}