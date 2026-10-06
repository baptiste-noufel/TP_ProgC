#include "fichier.h"
#include <stdio.h>

int lire_fichier(const char *nom_de_fichier)
{
    FILE *fichier = fopen(nom_de_fichier, "r");
    int caractere;

    if (fichier == NULL) {
        perror(nom_de_fichier);
        return 1;
    }
    while ((caractere = fgetc(fichier)) != EOF) {
        putchar(caractere);
    }
    if (ferror(fichier)) {
        perror("Lecture");
        fclose(fichier);
        return 1;
    }
    fclose(fichier);
    return 0;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
    FILE *fichier = fopen(nom_de_fichier, "w");

    if (fichier == NULL) {
        perror(nom_de_fichier);
        return 1;
    }
    if (fputs(message, fichier) == EOF || fputc('\n', fichier) == EOF) {
        perror("Ecriture");
        fclose(fichier);
        return 1;
    }
    fclose(fichier);
    return 0;
}