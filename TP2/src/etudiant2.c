#include <stdio.h>
#include <string.h>

struct etudiant {
    char nom[32];
    char prenom[32];
    char adresse[80];
    float programmation;
    float systeme;
};

int main(void)
{
    const char *noms[] = {"Dupont", "Martin", "Bernard", "Robert", "Petit"};
    const char *prenoms[] = {"Marie", "Pierre", "Sophie", "Lucas", "Emma"};
    const char *adresses[] = {
        "20, boulevard Niels Bohr, Lyon",
        "22, boulevard Niels Bohr, Lyon",
        "4, rue de la Republique, Lyon",
        "8, avenue Jean Jaures, Villeurbanne",
        "15, rue Pasteur, Bron"
    };
    const float programmation[] = {16.5f, 14.0f, 12.5f, 15.0f, 17.0f};
    const float systeme[] = {12.1f, 14.1f, 13.5f, 11.5f, 16.0f};
    struct etudiant etudiants[5];

    for (size_t i = 0; i < 5; ++i) {
        strcpy(etudiants[i].nom, noms[i]);
        strcpy(etudiants[i].prenom, prenoms[i]);
        strcpy(etudiants[i].adresse, adresses[i]);
        etudiants[i].programmation = programmation[i];
        etudiants[i].systeme = systeme[i];
    }

    for (size_t i = 0; i < 5; ++i) {
        printf("Etudiant %zu :\n", i + 1);
        printf("  Nom : %s\n", etudiants[i].nom);
        printf("  Prenom : %s\n", etudiants[i].prenom);
        printf("  Adresse : %s\n", etudiants[i].adresse);
        printf("  Programmation en C : %.1f\n", etudiants[i].programmation);
        printf("  Systeme d'exploitation : %.1f\n\n", etudiants[i].systeme);
    }

    return 0;
}