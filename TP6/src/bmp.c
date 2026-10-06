#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bmp.h"

couleur_compteur *analyse_bmp_image(char *nom_de_fichier)
{
  int fd = open(nom_de_fichier, O_RDONLY);
  bmp_header header;
  bmp_info_header info;
  couleur pixels = {0};
  couleur_compteur *resultat;

  if (fd < 0) { perror(nom_de_fichier); return NULL; }
  if (read(fd, &header, sizeof header) != (ssize_t)sizeof header ||
      header.type != 0x4d42 ||
      read(fd, &info, sizeof info) != (ssize_t)sizeof info ||
      (info.compte_bit != 24 && info.compte_bit != 32) ||
      info.taille_image == 0 ||
      lseek(fd, header.offset, SEEK_SET) < 0) {
    fprintf(stderr, "Fichier BMP invalide: %s\n", nom_de_fichier);
    close(fd);
    return NULL;
  }
  if (info.compte_bit == 24) {
    int n = (int)(info.taille_image / 3);
    pixels.compte_bit = BITS24;
    pixels.c.c24 = malloc((size_t)n * sizeof *pixels.c.c24);
    if (pixels.c.c24 == NULL || read(fd, pixels.c.c24, info.taille_image) != (ssize_t)info.taille_image) {
      free(pixels.c.c24); close(fd); return NULL;
    }
    resultat = compte_couleur(&pixels, n);
    free(pixels.c.c24);
  } else {
    int n = (int)(info.taille_image / 4);
    pixels.compte_bit = BITS32;
    pixels.c.c32 = malloc((size_t)n * sizeof *pixels.c.c32);
    if (pixels.c.c32 == NULL || read(fd, pixels.c.c32, info.taille_image) != (ssize_t)info.taille_image) {
      free(pixels.c.c32); close(fd); return NULL;
    }
    resultat = compte_couleur(&pixels, n);
    free(pixels.c.c32);
  }
  close(fd);
  if (resultat != NULL) trier_couleur_compteur(resultat);
  return resultat;
}
