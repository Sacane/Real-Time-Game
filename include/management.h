/**
 * \file : management.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * File containing the prototypes of the functions of the file management.c
 * 
 */

#ifndef __MANAGEMENT__H__
#define __MANAGEMENT__H__

#include "game_board.h"
#include "heap.h"
#include <string.h>
#include "config_stdin.h"


/**
 * Function to build a heap containing the initial Events of a game_board
 * Carefull : we suppose the heap not allocated yet, the function does it already.
 * \param game_board : Board, a game board
 * \return Heap, the Heap filled according to the initials event in the gameboard.
 */
Heap build_heap_by_board(Board game_board); 

/**
 * Function to activate a player's event
 * \param game_board : Board, a game board
 * \param heap : Heap, a pointer to a heap
 * \param pos_launcher : Coordinates, coordinates of laucher
 * \param previous_launcher : Event, the player event
 */
void trigger_launcher(Board game_board, Heap heap, Coordinates pos_launcher, Event ancien_launcher);


/**
 * Function to activate the event of a projectile
 * \param heap : Heap, a pointer to a heap
 * \param game_board : Board, a game board
 * \param pos_projectile : Coordinates, coordinates of a projectile
 * \param projectile : Event, the projectile event
 */
void trigger_projectile(Heap tas, Board game_board, Coordinates pos_projectile, Event projectile); 


/** 
 * Execute an event according to the coordinate of the object in the given gameboard,
 * this function also update the heap's state by adding the next event according to the event e given.
 * \param e : event to execute
 * \param heap : Heap, heap to add the next event
 * \param game_board : Board, gameboard to update according to the event
 */
void execute_event(Event e, Heap heap, Board game_board);


/**
 * Launch the game in the command line. 
 * \param board : Board, The gameboard containing all the object and players in the game.
 * \param is_reached : boolean to check if the game is reached or lost.
 */ 
void launch_command(Board board, bool *is_reached);

#endif