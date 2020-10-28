#include <stdio.h>
#include <stdlib.h>
#define DIM1 5
#define DIM2 6

void InitTab(char **tab) {
  int i, j;
  for (i = 0; i < DIM1; i++)
    for (j = 0; j < DIM2; j++)
      tab[i][j] = 0;
}
void InitTab_v2(char *tab) {
  int i;
  for (i = 0; i < DIM1 * DIM2; i++)
    tab[i] = 0;
}
void PrintTab(char **tab) {
  int i, j;
  for (i = 0; i < DIM1; i++) {
    for (j = 0; j < DIM2; j++)
      printf("\t%d", tab[i][j]);
    putchar('\n');
  }
}
void PrintTab_v2(char *tab) {
  int i, j;
  for (i = 0; i < DIM1; i++) {
    for (j = 0; j < DIM2; j++)
      printf("\t%d", tab[i * DIM2 + j]);
    putchar('\n');
  }
}
int main(void) {
  // char tab2D[DIM1][DIM2];
  // char *tab2Dyn = malloc(sizeof(char) * DIM1 * DIM2);
  char **tab2Dyn = malloc(sizeof(char *) * DIM1);
  int i;
  for (i = 0; i < DIM1; i++)
    tab2Dyn[i] = malloc(sizeof(char) * DIM2);
  InitTab(tab2Dyn);
  // InitTab_v2(tab2Dyn);
  PrintTab(tab2Dyn);
  // PrintTab_v2(tab2Dyn);
  return 0;
}