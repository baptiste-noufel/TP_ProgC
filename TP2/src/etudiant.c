#include <stdio.h>

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
    const size_t nombre_etudiants = sizeof noms / sizeof noms[0];

    for (size_t i = 0; i < nombre_etudiants; ++i) {
        printf("Etudiant %zu :\n", i + 1);
        printf("  Nom : %s\n", noms[i]);
        printf("  Prenom : %s\n", prenoms[i]);
        printf("  Adresse : %s\n", adresses[i]);
        printf("  Programmation en C : %.1f\n", programmation[i]);
        printf("  Systeme d'exploitation : %.1f\n\n", systeme[i]);
    }

    return 0;
}