#include <stdio.h>
#include <string.h>

static unsigned int occurrences(const char *ligne, const char *phrase)
{
    unsigned int total = 0;
    size_t longueur = strlen(phrase);

    if (longueur == 0) return 0;
    for (const char *p = ligne; (p = strstr(p, phrase)) != NULL; ++p) {
        ++total;
    }
    return total;
}

int main(int argc, char **argv)
{
    char nom[256];
    char phrase[256];
    FILE *fichier;
    char ligne[2048];
    unsigned long numero = 0;
    int trouve = 0;

    if (argc > 2) {
        fprintf(stderr, "Usage : %s [fichier]\n", argv[0]);
        return 1;
    }
    if (argc == 2) {
        snprintf(nom, sizeof nom, "%s", argv[1]);
    } else {
        printf("Nom du fichier : ");
        if (scanf(" %255[^\n]", nom) != 1) return 1;
    }
    printf("Phrase a rechercher : ");
    if (scanf(" %255[^\n]", phrase) != 1) return 1;
    fichier = fopen(nom, "r");
    if (fichier == NULL) {
        perror(nom);
        return 1;
    }
    while (fgets(ligne, sizeof ligne, fichier) != NULL) {
        unsigned int total;
        ++numero;
        total = occurrences(ligne, phrase);
        if (total > 0) {
            printf("Ligne %lu, %u fois\n", numero, total);
            trouve = 1;
        }
    }
    fclose(fichier);
    if (!trouve) puts("Phrase non trouvee.");
    return 0;
}