#include <stdio.h>

int main(void) {
    int compteur = 5;

    /* Vérification de la contrainte : compteur strictement inférieur à 10 */
    if (compteur <= 0 || compteur >= 10) {
        printf("Erreur : la variable compteur doit être strictement inférieure à 10 et positive.\n");
        return 1;
    }

    printf("--- Version avec boucles for (compteur = %d) ---\n", compteur);
    for (int i = 0; i < compteur; i++) {
        for (int j = 0; j <= i; j++) {
            /* Condition pour les bords : 1re colonne, diagonale ou dernière ligne */
            if (j == 0 || j == i || i == compteur - 1) {
                printf("* ");
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }

    printf("\n--- Version alternative avec boucles while (compteur = %d) ---\n", compteur);
    int row = 0;
    while (row < compteur) {
        int col = 0;
        while (col <= row) {
            if (col == 0 || col == row || row == compteur - 1) {
                printf("* ");
            } else {
                printf("# ");
            }
            col++;
        }
        printf("\n");
        row++;
    }

    return 0;
}