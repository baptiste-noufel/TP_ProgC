#include <stdio.h>

static unsigned long longueur(const char *chaine)
{
    const char *fin = chaine;

    while (*fin != '\0') {
        ++fin;
    }
    return (unsigned long)(fin - chaine);
}

static void copier(char *destination, const char *source)
{
    while ((*destination++ = *source++) != '\0') {
    }
}

static void concatener(char *destination, const char *source)
{
    while (*destination != '\0') {
        ++destination;
    }
    copier(destination, source);
}

int main(void)
{
    const char premiere[] = "Hello";
    const char seconde[] = " World!";
    char copie[sizeof premiere];
    char concatenee[sizeof premiere + sizeof seconde - 1];

    copier(copie, premiere);
    copier(concatenee, premiere);
    concatener(concatenee, seconde);

    printf("Longueur de \"%s\" : %lu\n", concatenee, longueur(concatenee));
    printf("Copie : %s\n", copie);
    printf("Concaténation : %s\n", concatenee);
    return 0;
}