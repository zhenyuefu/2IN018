#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000

int main(void) {
  srand(time(NULL));
  int monde[SIZE_X][SIZE_Y] = {0};
  int i, x, y;
  float energie;
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  for (i = 0; i < NB_PROIES; i++) {
    x = rand() % SIZE_X;
    y = rand() % SIZE_Y;
    energie = 20;
    ajouter_animal(x, y, energie, &liste_proie);
  }
  for (i = 0; i < NB_PREDATEURS; i++) {
    x = rand() % SIZE_X;
    y = rand() % SIZE_Y;
    energie = 20;
    ajouter_animal(x, y, energie, &liste_predateur);
  }

  FILE *f = fopen("Evol_Pop.txt", "w");
  for (i = 0; i <= 500; i++) {
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    reproduce(&liste_predateur, p_reproduce_predateur);
    reproduce(&liste_proie, p_reproduce_proie);
    rafraichir_monde(monde);
    afficher_ecosys(liste_proie, liste_predateur);
    fprintf(f, "%d %d %d\n", i, compte_animal_it(liste_proie),
            compte_animal_it(liste_predateur));
    // usleep(T_WAIT);
  }

  fclose(f);

  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);

  return 0;
}
