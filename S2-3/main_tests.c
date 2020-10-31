#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20

int main(void) {
  int i;
  int x, y;
  float energie;
  time_t t;
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  Animal *delete_proie = NULL;
  Animal *delete_predateur = NULL;

  srand((unsigned)time(&t));

  for (i = 0; i < NB_PROIES; i++) {
    x = rand() % SIZE_X;
    y = rand() % SIZE_Y;
    energie = rand() % 10;
    ajouter_animal(x, y, energie, &liste_proie);
  }

  for (i = 0; i < NB_PREDATEURS; i++) {
    x = rand() % SIZE_X;
    y = rand() % SIZE_Y;
    energie = rand() % 10;
    ajouter_animal(x, y, energie, &liste_predateur);
  }

  afficher_ecosys(liste_predateur, liste_proie);
  /*
  ** Test function enlever_animal()
  */
  /* 测试删除第一个 */
  delete_predateur = liste_predateur;
  delete_proie = liste_proie;
  /* 测试删除最后一个 */
  // for (i = 0; i < 19; i++) {
  //   delete_proie = delete_proie->suivant;
  //   delete_predateur = delete_predateur->suivant;
  // }
  enlever_animal(&liste_predateur, delete_predateur);
  enlever_animal(&liste_proie, delete_proie);
  afficher_ecosys(liste_predateur, liste_proie);
  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);
  return 0;
}
