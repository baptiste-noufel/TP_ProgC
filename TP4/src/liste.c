#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

void init_liste(struct liste_couleurs *liste)
{
    liste->tete = NULL;
}

int insertion(const struct couleur *couleur, struct liste_couleurs *liste)
{
    struct noeud_couleur *noeud = malloc(sizeof *noeud);
    if (noeud == NULL) return 1;
    noeud->valeur = *couleur;
    noeud->suivant = liste->tete;
    liste->tete = noeud;
    return 0;
}

void parcours(const struct liste_couleurs *liste)
{
    for (const struct noeud_couleur *noeud = liste->tete;
         noeud != NULL; noeud = noeud->suivant) {
        printf("#%02x%02x%02x\n", noeud->valeur.rouge,
               noeud->valeur.vert, noeud->valeur.bleu);
    }
}

void liberer_liste(struct liste_couleurs *liste)
{
    struct noeud_couleur *noeud = liste->tete;
    while (noeud != NULL) {
        struct noeud_couleur *suivant = noeud->suivant;
        free(noeud);
        noeud = suivant;
    }
    liste->tete = NULL;
}