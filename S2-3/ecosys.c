#include "ecosys.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

float p_ch_dir = 0.01;
int gain_energie_proie = 6;
int gain_energie_predateur = 20;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;
float p_manger = 0.6;
/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
  assert(x < SIZE_X && x >= 0);
  assert(y < SIZE_Y && y >= 0);
  Animal *new = creer_animal(x, y, energie);
  new->suivant = *liste_animal;
  *liste_animal = new;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  Animal *current;
  if (*liste == NULL || animal == NULL) return;
  while ((current = *liste) != NULL && current != animal && *liste != animal) {
    liste = &current->suivant;
  }
  *liste = current->suivant;
  free(current);
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal *liberer_liste_animaux(Animal *liste) {
  Animal *current;
  Animal *suivantp = liste;
  while ((current = suivantp) != NULL) {
    suivantp = current->suivant;
    free(current);
  }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt = 0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred = 0, nbproie = 0;
  Animal *pa = NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j] = ' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ++nbproie;
    // printf("%d,%d,%f\n", pa->x, pa->y, pa->energie);
    assert(pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y < SIZE_Y);
    ecosys[pa->x][pa->y] = '*';
    pa = pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
    ++nbpred;
    assert(pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y < SIZE_Y);
    if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /*
    proies aussi present */
      ecosys[pa->x][pa->y] = '@';
    } else {
      ecosys[pa->x][pa->y] = 'O';
    }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H"); /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 5, question 1 */
void bouger_animaux(Animal *la) { /*A Completer*/
  while (la) {
    if (rand() * 1. / RAND_MAX < p_ch_dir) {
      int a = la->dir[0];
      int b = la->dir[1];
      while (a == la->dir[0] && b == la->dir[1]) {
        la->dir[0] = rand() % 3 - 1;
        la->dir[1] = rand() % 3 - 1;
      }
    }
    la->x += la->dir[0];
    if (la->x >= SIZE_X) {
      la->x -= SIZE_X;
    } else if (la->x < 0) {
      la->x += SIZE_X;
    }
    la->y += la->dir[1];
    if (la->y >= SIZE_Y) {
      la->y -= SIZE_Y;
    } else if (la->y < 0) {
      la->y += SIZE_Y;
    }
    // printf("%d %d %f\n", la->x, la->y, la->energie);
    assert(la->x >= 0 && la->y >= 0 && la->x < SIZE_X && la->y < SIZE_Y);
    la = la->suivant;
  }
}

/* Part 2. Exercice 5, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) { /*A Completer*/
  if (liste_animal) {
    Animal *ani = *liste_animal;
    while (ani != NULL) {
      if (rand() * 1. / RAND_MAX < p_reproduce) {
        Animal *enfant = creer_animal(ani->x, ani->y, ani->energie / 2);
        ani->energie /= 2;
        *liste_animal = ajouter_en_tete_animal(*liste_animal, enfant);
      }
      ani = ani->suivant;
    }
  }
}

/* Part 2. Exercice 7, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  /*A Completer*/
  if (*liste_proie == NULL) return;
  Animal *current;
  Animal **proie = liste_proie;
  bouger_animaux(*liste_proie);
  while ((current = *liste_proie) != NULL) {
    current->energie -= 1;
    if (monde[current->x][current->y] >= 0) {
      current->energie += gain_energie_proie;
      monde[current->x][current->y] = temps_repousse_herbe;
    }
    if (current->energie < 0) {
      enlever_animal(proie, current);
      liste_proie = &current->suivant;
    } else {
      liste_proie = &current->suivant;
    }
  }
}

/* Part 2. Exercice 8, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  /*A Completer*/
  while (l != NULL) {
    if (l->x == x && l->y == y) {
      return l;
    }
    l = l->suivant;
  }
  return NULL;
}

/* Part 2. Exercice 8, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  /*A Completer*/
  if (*liste_proie == NULL || *liste_predateur == NULL) return;
  Animal *current, *proie;
  Animal **predateur = liste_predateur;
  bouger_animaux(*liste_predateur);
  while ((current = *liste_predateur) != NULL) {
    current->energie -= 1;
    proie = animal_en_XY(*liste_proie, current->x, current->y);

    if ((proie != NULL) && rand() * 1. / RAND_MAX < p_manger) {
      current->energie += gain_energie_predateur;
      enlever_animal(liste_proie, proie);
    }

    if (current->energie < 0) {
      liste_predateur = &current->suivant;
      enlever_animal(predateur, current);
    } else {
      liste_predateur = &current->suivant;
    }
  }
}

/* Part 2. Exercice 6, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) { /*A Completer*/
  int i, j;
  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      monde[i][j]++;
    }
  }
}