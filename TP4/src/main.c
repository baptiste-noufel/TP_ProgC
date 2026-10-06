#include <stdio.h>
#include "operator.h"
#include "fichier.h"
#include "liste.h"

static int exercice_operateurs(void)
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

static int exercice_fichiers(void)
{
    int choix;
    char nom[256];
    char message[1024];

    printf("1. Lire un fichier\n2. Ecrire dans un fichier\nVotre choix : ");
    if (scanf("%d", &choix) != 1) {
        fprintf(stderr, "Choix invalide.\n");
        return 1;
    }
    printf("Nom du fichier : ");
    if (scanf(" %255[^\n]", nom) != 1) {
        fprintf(stderr, "Nom invalide.\n");
        return 1;
    }
    if (choix == 1) return lire_fichier(nom);
    if (choix == 2) {
        printf("Message : ");
        if (scanf(" %1023[^\n]", message) != 1) {
            fprintf(stderr, "Message invalide.\n");
            return 1;
        }
        return ecrire_dans_fichier(nom, message);
    }
    fprintf(stderr, "Choix invalide.\n");
    return 1;
}

static int exercice_liste(void)
{
    const struct couleur couleurs[] = {
        {0xff, 0x00, 0x00}, {0x00, 0xff, 0x00}, {0x00, 0x00, 0xff},
        {0xff, 0xff, 0x00}, {0xff, 0x00, 0xff}, {0x00, 0xff, 0xff},
        {0xff, 0xff, 0xff}, {0x00, 0x00, 0x00}, {0x80, 0x80, 0x80},
        {0xff, 0x80, 0x00}
    };
    struct liste_couleurs liste;

    init_liste(&liste);
    for (size_t i = 0; i < sizeof couleurs / sizeof couleurs[0]; ++i) {
        if (insertion(&couleurs[i], &liste) != 0) {
            fprintf(stderr, "Allocation impossible.\n");
            liberer_liste(&liste);
            return 1;
        }
    }
    parcours(&liste);
    liberer_liste(&liste);
    return 0;
}

int main(void)
{
    int exercice;

    printf("Choisissez l'exercice (1, 2 ou 7) : ");
    if (scanf("%d", &exercice) != 1) {
        fprintf(stderr, "Choix invalide.\n");
        return 1;
    }
    if (exercice == 1) return exercice_operateurs();
    if (exercice == 2) return exercice_fichiers();
    if (exercice == 7) return exercice_liste();
    fprintf(stderr, "L'exercice choisi n'est pas disponible.\n");
    return 1;
}
