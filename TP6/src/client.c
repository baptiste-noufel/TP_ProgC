#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "client.h"
#include "bmp.h"

static int envoyer_tout(int fd, const char *message)
{
  size_t reste = strlen(message);
  while (reste > 0) {
    ssize_t n = send(fd, message, reste, 0);
    if (n <= 0) return -1;
    message += n; reste -= (size_t)n;
  }
  return 0;
}

static int envoyer_couleurs(int fd, const char *chemin, int nombre)
{
  couleur_compteur *cc = analyse_bmp_image((char *)chemin);
  char message[2048];
  size_t position = 0;
  int limite;

  if (cc == NULL) return -1;
  limite = cc->size < nombre ? cc->size : nombre;
  position += (size_t)snprintf(message + position, sizeof message - position,
                                "couleurs: %d", limite);
  for (int i = 0; i < limite; ++i) {
    if (cc->compte_bit == BITS24) {
      position += (size_t)snprintf(message + position, sizeof message - position,
                                   ",#%02x%02x%02x", cc->cc.cc24[i].c.rouge,
                                   cc->cc.cc24[i].c.vert, cc->cc.cc24[i].c.bleu);
    } else {
      position += (size_t)snprintf(message + position, sizeof message - position,
                                   ",#%02x%02x%02x", cc->cc.cc32[i].c.rouge,
                                   cc->cc.cc32[i].c.vert, cc->cc.cc32[i].c.bleu);
    }
  }
  free(cc->compte_bit == BITS24 ? (void *)cc->cc.cc24 : (void *)cc->cc.cc32);
  free(cc);
  if (position + 2 >= sizeof message) return -1;
  message[position++] = '\n'; message[position] = '\0';
  return envoyer_tout(fd, message);
}

int envoie_recois_message(int socketfd)
{
  char message[1024];
  printf("Votre message: ");
  if (fgets(message, sizeof message, stdin) == NULL) return -1;
  return envoyer_tout(socketfd, message);
}

int main(int argc, char **argv)
{
  int nombre = 10;
  int fd;
  struct sockaddr_in adresse = {0};

  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: %s IMAGE.BMP [nombre_de_couleurs]\n", argv[0]);
    return EXIT_FAILURE;
  }
  if (argc == 3 && (sscanf(argv[2], "%d", &nombre) != 1 || nombre < 1 || nombre > 30)) {
    fprintf(stderr, "Le nombre de couleurs doit être compris entre 1 et 30.\n");
    return EXIT_FAILURE;
  }
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) { perror("socket"); return EXIT_FAILURE; }
  adresse.sin_family = AF_INET; adresse.sin_port = htons(PORT);
  adresse.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  if (connect(fd, (struct sockaddr *)&adresse, sizeof adresse) < 0) {
    perror("connect"); close(fd); return EXIT_FAILURE;
  }
  if (envoyer_couleurs(fd, argv[1], nombre) != 0) {
    fprintf(stderr, "Echec d'envoi des couleurs.\n"); close(fd); return EXIT_FAILURE;
  }
  close(fd);
  return EXIT_SUCCESS;
}
