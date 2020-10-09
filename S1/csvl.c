#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compte_mots_chaine(char *chaine) {
  int i = 0, num = 1;
  for (i = 0; chaine[i] != '\0'; i++) {
    if (chaine[i] == ' ') num++;
  }
  return num;
}

char **decompose_chaine(char *chaine) {
  /* Fonction vue en TD, exercice 2, question 7 */

  char *pc = chaine;
  int nb_mots = 0;
  char **ptab;
  char *psrc_mot;
  int ind_mot = 0;

  // comptages des mots
  nb_mots = compte_mots_chaine(chaine);

  if (nb_mots == 0) return NULL;
  // allocation du tableau

  ptab = malloc((nb_mots + 1) * sizeof(char *));
  ptab[nb_mots] = NULL;

  // copie des mots

  pc = chaine;
  while (*pc) {
    if (*pc == ' ') {
      pc++;
      continue;
    }

    psrc_mot = pc;

    while ((*pc != ' ') && (*pc)) pc++;

    // allocation du mot
    ptab[ind_mot] = malloc((pc - psrc_mot + 1) * sizeof(char));
    // copie du mot
    memcpy(ptab[ind_mot], psrc_mot, pc - psrc_mot);
    // insertion du marqueur de fin de chaine
    *(ptab[ind_mot] + (pc - psrc_mot)) = '\0';

    ind_mot++;
  }

  return ptab;
}

char *compose_chaine(char **ptab_mots) {
  /* a completer exercice 3, question 4 */
  int i = 0;
  char *chaine = malloc(sizeof(char));
  *chaine = '\0';
  char *espace = " ";
  while (ptab_mots[i] != NULL) {
    strcat(chaine, ptab_mots[i]);
    strcat(chaine, espace);
    i++;
  }
  return chaine;
}

void detruit_tab_mots(char **ptab_mots) {
  /* Fonction vue en TD, exercice 2, question 5 */

  int i = 0;

  if (ptab_mots)
    while (ptab_mots[i]) free(ptab_mots[i++]);

  free(ptab_mots);
}

int compte_mots(char **ptab_mots) { /* a completer exercice 3, question 2 */
}

void affiche_tab_mots(char **ptab_mots) {
  /* a completer exercice 3, question 3 */
  char *s = ptab_mots[0];
  for (int i = 0; s != NULL; i++) {
    s = ptab_mots[i];
    printf("%s ", s);
  }
}

char **reduit_tab_mots(char **ptab_mots) {
  /* a completer exercice 4, question 1 */
}

int main() {
  /* a completer:
   * exercice 3, question 3, 5
   * exercice 4, question 1
   */
  char **tab;
  char *chaine = "mot1 et mot2";
  char *chaine_c;
  tab = decompose_chaine(chaine);
  affiche_tab_mots(tab);
  printf("\n");
  chaine_c = compose_chaine(tab);
  printf("%s", chaine_c);
  free(chaine_c);
  return 1;
}
