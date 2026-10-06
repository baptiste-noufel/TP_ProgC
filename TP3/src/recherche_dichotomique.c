#include <stdio.h>

#define TAILLE 100

static int rechercher(const int *tableau, int valeur)
{
    int debut = 0;
    int fin = TAILLE - 1;

    while (debut <= fin) {
        int milieu = debut + (fin - debut) / 2;
        if (tableau[milieu] == valeur) {
            return 1;
        }
        if (tableau[milieu] < valeur) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }
    return 0;
}

int main(void)
{
    int tableau[TAILLE];
    int recherche;

    for (int i = 0; i < TAILLE; ++i) {
        tableau[i] = i - 50;
    }

    printf("Tableau trie :\n");
    for (int i = 0; i < TAILLE; ++i) {
        printf("%d%s", tableau[i], i == TAILLE - 1 ? "\n" : " ");
    }
    printf("Entrez l'entier que vous souhaitez chercher : ");
    if (scanf("%d", &recherche) != 1) {
        fprintf(stderr, "Entree invalide.\n");
        return 1;
    }

    printf("Resultat : entier %s\n",
           rechercher(tableau, recherche) ? "present" : "absent");
    return 0;
}