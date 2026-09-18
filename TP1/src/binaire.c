#include <stdio.h>

int main(void) {
    int nombres[] = {0, 4096, 65536, 65535, 1024};
    int taille = sizeof(nombres) / sizeof(nombres[0]);
    int nb_bits = sizeof(int) * 8;

    for (int k = 0; k < taille; k++) {
        int n = nombres[k];
        printf("%6d en binaire : ", n);

        /* Parcours du bit 31 au bit 0 */
        for (int i = nb_bits - 1; i >= 0; i--) {
            int bit = (n >> i) & 1;
            printf("%d", bit);

            /* Séparateur tous les 4 bits pour la lisibilité */
            if (i % 4 == 0 && i != 0) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}