#include "arbre_lexicographique_tab.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PNoeudTab creer_noeud(char lettre) {
  PNoeudTab pn = (PNoeudTab)malloc(sizeof(NoeudTab));
  if (pn == NULL) {
    printf("Impossible d'allouer un noeud\n");
    return NULL;
  }
  pn->lettre = lettre;
  pn->fin_de_mot = non_fin;
  for (int i = 0; i < 26; i++) {
    pn->fils[i] = NULL;
  }
  return pn;
}

PNoeudTab ajouter_mot(PNoeudTab racine, char *mot) {
  if (strlen(mot) == 0) {
    racine->fin_de_mot = fin;
    return NULL;
  }
  int i = mot[0] - 'a';
  if (racine->fils[i] == NULL) racine->fils[i] = creer_noeud(mot[0]);
  ajouter_mot(racine->fils[i], mot + 1);
  return racine;
}

void afficher_mots(PNoeudTab n, char mot_en_cours[LONGUEUR_MAX_MOT],
                   int index) {
  if (n == NULL) {
    return;
  }
  mot_en_cours[index] = n->lettre;
  if (n->fin_de_mot == fin) {
    mot_en_cours[index + 1] = '\0';
    printf("%s\n", mot_en_cours);
  }
  for (int i = 0; i < 26; i++) {
    afficher_mots(n->fils[i], mot_en_cours, index + 1);
  }
}

void afficher_dico(PNoeudTab racine) {
  char mot_en_cours[LONGUEUR_MAX_MOT];
  for (int i = 0; i < 26; i++) {
    afficher_mots(racine->fils[i], mot_en_cours, 0);
  }
}

void detruire_dico(PNoeudTab dico) {
  if (dico != NULL) {
    for (int i = 0; i < 26; i++) detruire_dico(dico->fils[i]);
    free(dico);
  }
}

int rechercher_mot(PNoeudTab dico, char *mot) {
  if (strlen(mot) == 0) {
    return dico->fin_de_mot == fin;
  }
  int i = mot[0] - 'a';
  if (dico->fils[i] == NULL) return 0;
  return rechercher_mot(dico->fils[i], mot + 1);
}

PNoeudTab lire_dico(const char *nom_fichier) {
  FILE *f = fopen(nom_fichier, "r");
  if (f == NULL) {
    fprintf(stderr, "Impossible d'ouvrir le fichiner %s\n", nom_fichier);
    return NULL;
  }

  PNoeudTab dico = malloc(sizeof(NoeudTab));
  dico->fin_de_mot = non_fin;
  char mot[LONGUEUR_MAX_MOT];
  while (fgets(mot, LONGUEUR_MAX_MOT, f)) {
    mot[strlen(mot) - 1] = '\0';
    ajouter_mot(dico, mot);
  }
  fclose(f);
  return dico;
}
