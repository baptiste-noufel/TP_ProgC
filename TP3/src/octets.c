#include <stdio.h>

static void afficher_octets(const void *adresse, size_t taille)
{
    const unsigned char *octets = adresse;

    for (size_t i = 0; i < taille; ++i) {
        printf("%02x%s", octets[i], i + 1 == taille ? "\n" : " ");
    }
}

int main(void)
{
    short valeur_short = 0x0203;
    int valeur_int = 0x01020304;
    long valeur_long = 0x0102030405060708L;
    float valeur_float = 1.0f;
    double valeur_double = 1.0;
    long double valeur_long_double = 1.0L;

    printf("Octets de short :\n");
    afficher_octets(&valeur_short, sizeof valeur_short);
    printf("Octets de int :\n");
    afficher_octets(&valeur_int, sizeof valeur_int);
    printf("Octets de long int :\n");
    afficher_octets(&valeur_long, sizeof valeur_long);
    printf("Octets de float :\n");
    afficher_octets(&valeur_float, sizeof valeur_float);
    printf("Octets de double :\n");
    afficher_octets(&valeur_double, sizeof valeur_double);
    printf("Octets de long double :\n");
    afficher_octets(&valeur_long_double, sizeof valeur_long_double);
    return 0;
}