/**
 * \file : wrapper.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * This module contains all the include necessary to all the modules
 * It also manage the game_mode required to launch the game and control the allocation's errors.
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
  ERROR,
  FOLDER,
}Game_mode;

typedef struct{

  unsigned x; /* x coordinate of the object in the board */
  unsigned y; /* y coordinate of the object in the board */
  
} Coordinates;

/**
 * Function to check if the allocation has been successful
 * \param data : data to check
 */
void verif_malloc(void *object);



#endif