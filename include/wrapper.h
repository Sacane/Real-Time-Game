/**
 * \file : wrapper.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \creation date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions in the wrapper.c file
 *
 */


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

/**
 * Function to check if the allocation has been successful
 * @param objet : void*, the game board
 */
void verif_malloc(void *objet);



#endif