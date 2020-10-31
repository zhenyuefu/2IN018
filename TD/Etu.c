#include "Etu.h"

#include <stdio.h>

ty_etu *lecture_ascii_etu(char *nom_fichier, int *nb_etu) {
  FILE *pf;
  ty_etu *tab_etu;
  int i;

  pf = fopen(nom_fichier, "r");
  if (pf == NULL) {
    fprintf(stderr, "Impossible ouvrir %s\n", nom_fichier);
    return NULL;
  }
  if (fscanf(pf, " %d", &nb_etu) != 1) {
    fprintf(stderr, "Error");
    fclose(pf);
    return NULL;
  }
  tab_etu = malloc(*nb_etu * sizeof(ty_etu));
  for (i = 0; i < *nb_etu; i++) {
    fscanf(pf, " %d %s %s %d", &(tab_etu[i].id_etu), &(tab_etu[i].nom),
           &(tab_etu[i].prenom), &(tab_etu[i].nb_ue));
  }
}
