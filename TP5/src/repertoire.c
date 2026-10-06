#include "repertoire.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static int chemin_entree(char *destination, size_t taille,
                         const char *dossier, const char *nom)
{
    int longueur = snprintf(destination, taille, "%s/%s", dossier, nom);
    return longueur < 0 || (size_t)longueur >= taille;
}

static int lire_dossier_recursif_interne(const char *nom_repertoire)
{
    DIR *dossier = opendir(nom_repertoire);
    struct dirent *entree;

    if (dossier == NULL) {
        perror(nom_repertoire);
        return 1;
    }
    while ((entree = readdir(dossier)) != NULL) {
        char chemin[4096];
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
            lire_dossier_recursif_interne(chemin) != 0) {
            closedir(dossier);
            return 1;
        }
    }
    return closedir(dossier) == 0 ? 0 : 1;
}

int lire_dossier(const char *nom_repertoire)
{
    DIR *dossier = opendir(nom_repertoire);
    struct dirent *entree;

    if (dossier == NULL) {
        perror(nom_repertoire);
        return 1;
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

int lire_dossier_recursif(const char *nom_repertoire)
{
    return lire_dossier_recursif_interne(nom_repertoire);
}

int lire_dossier_iteratif(const char *nom_repertoire)
{
    char dossiers[256][4096];
    size_t debut = 0;
    size_t fin = 1;

    if (snprintf(dossiers[0], sizeof dossiers[0], "%s", nom_repertoire) < 0) {
        return 1;
    }
    while (debut < fin) {
        DIR *dossier = opendir(dossiers[debut]);
        struct dirent *entree;

        if (dossier == NULL) {
            perror(dossiers[debut]);
            return 1;
        }
        while ((entree = readdir(dossier)) != NULL) {
            char chemin[4096];
            struct stat informations;

            if (strcmp(entree->d_name, ".") == 0 ||
                strcmp(entree->d_name, "..") == 0) {
                continue;
            }
            if (chemin_entree(chemin, sizeof chemin, dossiers[debut],
                              entree->d_name) ||
                stat(chemin, &informations) != 0) {
                perror(entree->d_name);
                closedir(dossier);
                return 1;
            }
            puts(chemin);
            if (S_ISDIR(informations.st_mode)) {
                if (fin == sizeof dossiers / sizeof dossiers[0]) {
                    fprintf(stderr, "Trop de sous-repertoires.\n");
                    closedir(dossier);
                    return 1;
                }
                (void)snprintf(dossiers[fin], sizeof dossiers[fin], "%s", chemin);
                ++fin;
            }
        }
        if (closedir(dossier) != 0) {
            perror("closedir");
            return 1;
        }
        ++debut;
    }
    return 0;
}