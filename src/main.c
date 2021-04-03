#include <stdio.h>
#include "../include/niveau.h"


int main(void) {

  Coordonnees taille;
  taille.x = 10;
  taille.y = 5;
  Plateau niveau;
  printf("%d\n", taille.x);
  niveau = malloc_Niveau(taille);



  free_Niveau(niveau);

  return 0;
}
