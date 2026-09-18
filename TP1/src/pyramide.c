#include <stdio.h>

int main(void) {
    int n = 5;
    int i, j;

    for (i = 1; i <= n; i++) {
        /* Espaces pour centrer la pyramide */
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        /* Nombres croissants de 1 à i */
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        /* Nombres décroissants de i - 1 à 1 */
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        printf("\n");
    }

    printf("Génération de la pyramide terminée.\n");

    return 0;
}