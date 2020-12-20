#include <stdio.h>
#include <stdlib.h>

#include "arbre_lexicographique.h"

int main(int argc, char** argv) {
  int nbr;
  int res;
  int i;
  char* mot;
  PNoeud dico = lire_dico("french_za");

  if (argc != 3) {
    fprintf(stderr, "Usage : %s <mot> <nb_recherches>\n", argv[0]);
    exit(1);
  }

  mot = argv[1];
  nbr = atoi(argv[2]);

  for (i = 0; i < nbr; i++) {
    res = rechercher_mot(dico, mot);
  }
  if (res)
    printf("Le mot %s est trouve.\n", mot);
  else
    printf("Le mot %s n'a pas ete trouve.\n", mot);

  detruire_dico(dico);
  return 0;
}
