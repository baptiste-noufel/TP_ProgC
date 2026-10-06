#include "couleur.h"
#include <stdio.h>
#include <stdlib.h>

static int meme_couleur24(couleur24 a, couleur24 b)
{
  return a.rouge == b.rouge && a.vert == b.vert && a.bleu == b.bleu;
}

static int meme_couleur32(couleur32 a, couleur32 b)
{
  return a.rouge == b.rouge && a.vert == b.vert &&
         a.bleu == b.bleu && a.alpha == b.alpha;
}

couleur_compteur *compte_couleur(couleur *c, int csize)
{
  couleur_compteur *resultat = calloc(1, sizeof *resultat);
  int nombre = 0;

  if (resultat == NULL || c == NULL || csize < 0) {
    free(resultat);
    return NULL;
  }
  resultat->compte_bit = c->compte_bit;
  if (c->compte_bit == BITS24) {
    resultat->cc.cc24 = calloc((size_t)csize, sizeof *resultat->cc.cc24);
  } else {
    resultat->cc.cc32 = calloc((size_t)csize, sizeof *resultat->cc.cc32);
  }
  if ((c->compte_bit == BITS24 && resultat->cc.cc24 == NULL) ||
      (c->compte_bit == BITS32 && resultat->cc.cc32 == NULL)) {
    free(resultat);
    return NULL;
  }
  for (int i = 0; i < csize; ++i) {
    int index = -1;
    for (int j = 0; j < nombre; ++j) {
      if ((c->compte_bit == BITS24 &&
           meme_couleur24(c->c.c24[i], resultat->cc.cc24[j].c)) ||
          (c->compte_bit == BITS32 &&
           meme_couleur32(c->c.c32[i], resultat->cc.cc32[j].c))) {
        index = j;
        break;
      }
    }
    if (index >= 0) {
      if (c->compte_bit == BITS24) ++resultat->cc.cc24[index].compte;
      else ++resultat->cc.cc32[index].compte;
    } else if (c->compte_bit == BITS24) {
      resultat->cc.cc24[nombre].c = c->c.c24[i];
      resultat->cc.cc24[nombre].compte = 1;
      ++nombre;
    } else {
      resultat->cc.cc32[nombre].c = c->c.c32[i];
      resultat->cc.cc32[nombre].compte = 1;
      ++nombre;
    }
  }
  resultat->size = nombre;
  return resultat;
}

void print_couleur(couleur *c, int csize)
{
  for (int i = 0; i < csize; ++i) {
    if (c->compte_bit == BITS24)
      printf("%02x %02x %02x\n", c->c.c24[i].rouge, c->c.c24[i].vert, c->c.c24[i].bleu);
    else
      printf("%02x %02x %02x %02x\n", c->c.c32[i].rouge, c->c.c32[i].vert,
             c->c.c32[i].bleu, c->c.c32[i].alpha);
  }
}

void print_couleur_compteur(couleur_compteur *c)
{
  for (int i = 0; i < c->size; ++i) {
    if (c->compte_bit == BITS24)
      printf("#%02x%02x%02x: %d\n", c->cc.cc24[i].c.rouge, c->cc.cc24[i].c.vert,
             c->cc.cc24[i].c.bleu, c->cc.cc24[i].compte);
    else
      printf("#%02x%02x%02x: %d\n", c->cc.cc32[i].c.rouge, c->cc.cc32[i].c.vert,
             c->cc.cc32[i].c.bleu, c->cc.cc32[i].compte);
  }
}

void trier_couleur_compteur(couleur_compteur *c)
{
  for (int i = 0; i < c->size; ++i) {
    for (int j = i + 1; j < c->size; ++j) {
      int compte_i = c->compte_bit == BITS24 ? c->cc.cc24[i].compte : c->cc.cc32[i].compte;
      int compte_j = c->compte_bit == BITS24 ? c->cc.cc24[j].compte : c->cc.cc32[j].compte;
      if (compte_j > compte_i) {
        if (c->compte_bit == BITS24) {
          couleur24_compteur tmp = c->cc.cc24[i];
          c->cc.cc24[i] = c->cc.cc24[j]; c->cc.cc24[j] = tmp;
        } else {
          couleur32_compteur tmp = c->cc.cc32[i];
          c->cc.cc32[i] = c->cc.cc32[j]; c->cc.cc32[j] = tmp;
        }
      }
    }
  }
}
