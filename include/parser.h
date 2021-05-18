/**
 * \file : parser.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \creation date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions in the parser.c file
 *
 */

#ifndef __PARSER__H__
#define __PARSER__H__

#include <string.h>
#include "niveau.h"
#include "temps.h"

/**
 * Function to read a given file
 * @param name_file : char*, a string of characters
 * @return : Board, a game board  
 */
Plateau read_file(char* name_file);


#endif