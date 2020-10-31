#define ETU_
#ifdef ETU_

typedef struct _ty_etu {
  int id_etu;
  char nom[200];
  char prenom[200];
  int nb_ue;
  char codes_ue[9][20];
  int notes[20];
} ty_etu;

ty_etu *lecture_ascii_etu(char *nom_fichier, int *nb_etu);

#endif