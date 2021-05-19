/**
 * \file wrapper.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * This module contains all the include necessary to all the modules
 * It also manage the game_mode required to launch the game and control the errors.
 *
 */

#include "../include/wrapper.h"


/**
 * \fn void verif_malloc(void *object)
 * \brief Function to check if the allocation has been successful
 * @param object : void *, object to check
 */
void verif_malloc(void *object){
    if(NULL == object){
        fprintf(stderr, "Allocation échoué\n");
        exit(1);
    }
}

