/**
 * \file : opt.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \creation date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions in the opt.c file
 *
 */

#ifndef __OPT__H__
#define __OPT__H__


#include <getopt.h>
#include "parser.h"
#include "level_maker.h"


/**
 * Function to manage the different usage options 
 * @param argc : int, the number of the argument (of the chosen option)
 * @param argv[] : char*, string of characters
 * @param mode : int*, a pointer to an int (the chosen mode)
 * @param name_file : char*, string of characters of the name of the given file 
 * @param game : Board, a game board
 */
void opt_management(int argc, char* argv[], int *mode, char *name_file, Plateau *niveau);



#endif