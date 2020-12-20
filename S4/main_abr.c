#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "liste.h"

int main(int argc, char** argv) {
  Lm_mot* liste = lire_dico_Lmot("french_za");
  Nd_mot* abr;
  Nd_mot* pn;
  int i;
  int nbr;
  if (argc != 3) {
    fprintf(stderr, "Usage : %s <mot> <nb_recherches>\n", argv[0]);
    exit(1);
  }

  nbr = atoi(argv[2]);
  abr = Lm2abr(liste);
  char* mot = argv[1];

  for (i = 0; i < nbr; i++) {
    pn = chercher_Nd_mot(abr, mot);
  }

  if (pn == NULL) {
    printf("Le mot %s n'a pas ete trouve.\n", mot);
  } else {
    printf("Le mot %s est trouve.\n", mot);
  }

  detruire_abr_mot(abr);

  return 0;
}
