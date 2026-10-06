#include <stdio.h>

static int comparer(const char *premiere, const char *seconde)
{
    while (*premiere != '\0' && *premiere == *seconde) {
        ++premiere;
        ++seconde;
    }
    return *premiere == '\0' && *seconde == '\0';
}

int main(void)
{
    const char *phrases[] = {
        "Bonjour, comment ca va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };
    char recherche[256];
    int trouve = 0;

    printf("Entrez la phrase a rechercher : ");
    if (scanf(" %255[^\n]", recherche) != 1) {
        fprintf(stderr, "Entree invalide.\n");
        return 1;
    }

    for (size_t i = 0; i < sizeof phrases / sizeof phrases[0]; ++i) {
        if (comparer(phrases[i], recherche)) {
            trouve = 1;
            break;
        }
    }

    printf("%s\n", trouve ? "Phrase trouvee" : "Phrase non trouvee");
    return 0;
}
