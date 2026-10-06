#include "repertoire.h"
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static int chemin_entree(char *destination, size_t taille,
                         const char *dossier, const char *nom)
{
    int longueur = snprintf(destination, taille, "%s/%s", dossier, nom);
    return longueur < 0 || (size_t)longueur >= taille;
}

int lire_dossier(const char *nom_repertoire)
{
    DIR *dossier = opendir(nom_repertoire);
    struct dirent *entree;

    if (dossier == NULL) {
        perror(nom_repertoire);
        return 1;
    }

    int lire_dossier_recursif(const char *nom_repertoire)
    {
        DIR *dossier = opendir(nom_repertoire);
        struct dirent *entree;

        if (dossier == NULL) {
            perror(nom_repertoire);
            return 1;
        }
        while ((entree = readdir(dossier)) != NULL) {
            char chemin[PATH_MAX];
            struct stat informations;

            if (strcmp(entree->d_name, ".") == 0 ||
                strcmp(entree->d_name, "..") == 0) {
                continue;
            }
            if (chemin_entree(chemin, sizeof chemin, nom_repertoire, entree->d_name) ||
                stat(chemin, &informations) != 0) {
                perror(entree->d_name);
                closedir(dossier);
                return 1;
            }
            puts(chemin);
            if (S_ISDIR(informations.st_mode) &&
                lire_dossier_recursif(chemin) != 0) {
                closedir(dossier);
                return 1;
            }
        }
        return closedir(dossier) == 0 ? 0 : 1;
    }
    while ((entree = readdir(dossier)) != NULL) {
        if (entree->d_name[0] != '.') {
            puts(entree->d_name);
        }
    }
    if (closedir(dossier) != 0) {
        perror("closedir");
        return 1;
    }
    return 0;
}