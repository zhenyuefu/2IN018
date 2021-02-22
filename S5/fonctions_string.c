#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "devel.h"

void *dupliquer_str(const void *src) {
  char **isrc = (char **)src;
  char *idest = strdup(*isrc);
  if (idest == NULL) {
    affiche_message("Erreur de strdup().");
    return NULL;
  }
  *idest = **isrc;
  return (void *)idest;
}

void copier_str(const void *src, void *dst) {
  /* a completer. Exercice 5, question 1 */
}

void detruire_str(void *data) { /* a completer. Exercice 5, question 1 */ }

void afficher_str(const void *data) {
  /* a completer. Exercice 5, question 1 */
}

int comparer_str(const void *a, const void *b) {
  /* a completer. Exercice 5, question 1 */
  return 0;  // pour que cela compile
}

int ecrire_str(const void *data, FILE *f) {
  /* a completer. Exercice 5, question 1 */
  return 0;  // pour que cela compile
}

void *lire_str(FILE *f) {
  /* a completer. Exercice 5, question 1 */
  return NULL;  // pour que cela compile
}
