/**
 * \file : parser.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * The module is used to manipulate the file and folders to read it and build a gameboard or 
 * launch the game
 *
 */

#ifndef __PARSER__H__
#define __PARSER__H__

#include <string.h>
#include "game_board.h"
#include "temps.h"
#include "management.h"
#define MAX_LEVEL 6 /* Simple macro represents the maximum level made as file */

/**
 * \brief Function to read a given file
 * \param name_file : char*, a string of characters
 * \return : Board, a game board
 */
Board read_file(char* name_file);


/**
 * \brief Parse the folder and launch all the level inthere (command line only)
 * \param name_folder : name of the folder to parse
 * \param level_start start of the parsing
 * 
 */ 
void read_folder(char* name_folder, int level_start);

#endif