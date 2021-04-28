#ifndef __WRAPPER__H__
#define __WRAPPER__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define COMMAND 0
#define GRAPHIC 1
#define DEBUG 2
#define TEST_FILE 3

typedef struct{

  unsigned x;
  unsigned y;
  
} Coordonnees;


void verif_malloc(void *objet);





#endif