#include "repertoire.h"
#include <dirent.h>
#include <stdio.h>

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