#include <arpa/inet.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "serveur.h"

int socketfd = -1;

static void gestionnaire_ctrl_c(int signal_recu)
{
  (void)signal_recu;
  if (socketfd >= 0) close(socketfd);
  _Exit(EXIT_SUCCESS);
}

static int plot(const char *data)
{
  char copie[4096];
  char *saveptr;
  char *token;
  int nombre;
  FILE *svg;

  if (sscanf(data, "couleurs: %d", &nombre) != 1 || nombre < 1 || nombre > 30)
    return 1;
  if (strlen(data) >= sizeof copie) return 1;
  strcpy(copie, data);
  token = strtok_r(copie, ",", &saveptr);
  if (token == NULL) return 1;
  svg = fopen(svg_file_path, "w");
  if (svg == NULL) return 1;
  fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"400\" height=\"400\">\n");
  fprintf(svg, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");
  for (int i = 0; i < nombre; ++i) {
    token = strtok_r(NULL, ",", &saveptr);
    if (token == NULL) { fclose(svg); return 1; }
    double debut = -90.0 + 360.0 * i / nombre;
    double fin = -90.0 + 360.0 * (i + 1) / nombre;
    double x1 = 200 + 150 * cos(debut * M_PI / 180);
    double y1 = 200 + 150 * sin(debut * M_PI / 180);
    double x2 = 200 + 150 * cos(fin * M_PI / 180);
    double y2 = 200 + 150 * sin(fin * M_PI / 180);
    fprintf(svg, "<path d=\"M200,200 L%.2f,%.2f A150,150 0 0,1 %.2f,%.2f Z\" fill=\"%s\"/>\n",
            x1, y1, x2, y2, token);
  }
  fputs("</svg>\n", svg);
  fclose(svg);
  return 0;
}

int recois_envoie_message(int client_fd, char data[1024])
{
  if (strncmp(data, "couleurs:", 9) != 0 || plot(data) != 0)
    return renvoie_message(client_fd, "Erreur: message couleurs invalide\n");
  return renvoie_message(client_fd, "SVG genere: pie_chart.svg\n");
}

int renvoie_message(int client_fd, char *data)
{
  size_t reste = strlen(data);
  while (reste > 0) {
    ssize_t n = send(client_fd, data, reste, 0);
    if (n <= 0) return EXIT_FAILURE;
    data += n; reste -= (size_t)n;
  }
  return EXIT_SUCCESS;
}

int main(void)
{
  struct sockaddr_in adresse = {0};
  signal(SIGINT, gestionnaire_ctrl_c);
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0) { perror("socket"); return EXIT_FAILURE; }
  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);
  adresse.sin_family = AF_INET; adresse.sin_port = htons(PORT);
  adresse.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(socketfd, (struct sockaddr *)&adresse, sizeof adresse) < 0 ||
      listen(socketfd, 10) < 0) { perror("bind/listen"); return EXIT_FAILURE; }
  puts("Serveur en attente de connexions...");
  for (;;) {
    int client = accept(socketfd, NULL, NULL);
    char data[1024] = {0};
    ssize_t taille;
    if (client < 0) continue;
    taille = recv(client, data, sizeof data - 1, 0);
    if (taille > 0) { data[taille] = '\0'; recois_envoie_message(client, data); }
    close(client);
  }
}
