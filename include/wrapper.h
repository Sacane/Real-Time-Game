#ifndef __WRAPPER__H__
#define __WRAPPER__H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "temps.h"


typedef enum{
  COMMAND,
  GRAPHIC,
  DEBUG,
  ERROR
}Mode;

typedef struct{

  unsigned x;
  unsigned y;
  
} Coordonnees;


void verif_malloc(void *objet);



#endif