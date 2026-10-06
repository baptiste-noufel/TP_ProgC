/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"

/**
 * Fonction pour envoyer et recevoir un message depuis un client connecté à la socket.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
static int envoie_et_affiche_reponse(int socketfd, const char *data)
{
  char reponse[1024];
  ssize_t taille = write(socketfd, data, strlen(data));

  if (taille < 0) {
    perror("Erreur d'ecriture");
    return -1;
  }
  taille = read(socketfd, reponse, sizeof reponse - 1);
  if (taille <= 0) {
    perror("Erreur de lecture");
    return -1;
  }
  reponse[taille] = '\0';
  printf("Message recu: %s\n", reponse);
  return 0;
}

static int envoie_calcul_lit(int socketfd, char operateur, int premier,
                             int second, int *resultat)
{
  char data[128];
  char reponse[128];
  int taille = snprintf(data, sizeof data, "calcule : %c %d %d\n",
                        operateur, premier, second);
  ssize_t recu;

  if (taille < 0 || (size_t)taille >= sizeof data ||
      write(socketfd, data, (size_t)taille) < 0) {
    return -1;
  }
  recu = read(socketfd, reponse, sizeof reponse - 1);
  if (recu <= 0) return -1;
  reponse[recu] = '\0';
  if (sscanf(reponse, "calcule : %d", resultat) != 1) return -1;
  printf("Message recu: %s", reponse);
  return 0;
}

static int envoyer_notes(int socketfd)
{
  int somme_classe = 0;

  for (int etudiant = 1; etudiant <= 5; ++etudiant) {
    int notes[5];
    int somme;
    for (int note = 0; note < 5; ++note) {
      char chemin[128];
      FILE *fichier;
      (void)snprintf(chemin, sizeof chemin, "../etudiant/%d/note%d.txt",
                     etudiant, note + 1);
      fichier = fopen(chemin, "r");
      if (fichier == NULL || fscanf(fichier, "%d", &notes[note]) != 1) {
        perror(chemin);
        if (fichier != NULL) fclose(fichier);
        return -1;
      }
      fclose(fichier);
    }
    if (envoie_calcul_lit(socketfd, '+', notes[0], notes[1], &somme) != 0 ||
        envoie_calcul_lit(socketfd, '+', somme, notes[2], &somme) != 0 ||
        envoie_calcul_lit(socketfd, '+', somme, notes[3], &somme) != 0 ||
        envoie_calcul_lit(socketfd, '+', somme, notes[4], &somme) != 0) {
      return -1;
    }
    printf("Somme etudiant %d : %d\n", etudiant, somme);
    somme_classe += somme;
  }
  {
    int moyenne;
    if (envoie_calcul_lit(socketfd, '/', somme_classe, 5, &moyenne) != 0) {
      return -1;
    }
    printf("Moyenne de la classe : %d\n", moyenne);
  }
  return 0;
}

int envoie_operateur_numeros(int socketfd, char operateur, int premier,
                             int second, int nombre_numeros)
{
  char data[1024];
  int taille = nombre_numeros == 1
      ? snprintf(data, sizeof data, "calcule : %c %d\n", operateur, premier)
      : snprintf(data, sizeof data, "calcule : %c %d %d\n",
                 operateur, premier, second);

  if (taille < 0 || (size_t)taille >= sizeof data) return -1;
  return envoie_et_affiche_reponse(socketfd, data);
}

int envoie_recois_message(int socketfd)
{
  char message[1024];
  char operateur;
  int premier;
  int second;

  printf("Votre message (max 1000 caracteres): ");
  if (fgets(message, sizeof message, stdin) == NULL) return -1;
  if (strncmp(message, "notes", 5) == 0) {
    return envoyer_notes(socketfd);
  }
  if (sscanf(message, "calcule : %c %d %d", &operateur, &premier, &second) == 3) {
    return envoie_operateur_numeros(socketfd, operateur, premier, second, 2);
  }
  if (sscanf(message, "calcule : %c %d", &operateur, &premier) == 2) {
    return envoie_operateur_numeros(socketfd, operateur, premier, 0, 1);
  }
  {
    char data[1024];
    int taille = snprintf(data, sizeof data, "message: %s", message);
    if (taille < 0 || (size_t)taille >= sizeof data) return -1;
    return envoie_et_affiche_reponse(socketfd, data);
  }
}

int main()
{
  int socketfd;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  while (1)
  {
    // appeler la fonction pour envoyer un message au serveur
    if (envoie_recois_message(socketfd) != 0) {
      break;
    }
  }

  close(socketfd);
}
