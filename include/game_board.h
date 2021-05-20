/**
 * \file : game_board.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * Module used to manipulate the board and its components
 *
 */

#ifndef __GAME_BOARD__H__
#define __GAME_BOARD__H__

#include "object.h"

#define MODE_ONE_PLAYER 0;
#define MODE_TWO_PLAYER 1;

/* Structure to store the datas of a player. */
typedef struct player{
    
    TypeObject typePlayer; /* Type of the player, it can be Player1 or Player2 */
    Coordinates coo_player; /* Actual coordinates of the player */
    Direction dir_player; /* Actual direction of the player */
    unsigned long moment_depl_player; /* Moment when the player is allow to move again */
    bool is_player_alive; /* Boolean to check if the player is alive or not */
    bool can_player_move; /* Boolean to check if the player can move or not */
    bool has_player_win; /* Boolean to check if the player won the game */
    unsigned long speed_player; /* allure of the deplacement of a player */

}Player;

/* Structure to store the datas to manipulate a game board */
typedef struct Level{
    
    Coordinates size; /*Size of the board*/
    Object** objects; /*2D array of Objects to manipulate the objects in the game*/
    bool is_game_over; /* boolean to check if the game is over or not */
    Coordinates coo_destination; /* Coordinates of the goal in the board, the player won if he reach this coordinates */
    bool mulptiplayer_mode; /* boolean to check if the board allow 1 or 2 players */
    Player p1; /* Player 1 in the game */
    Player p2;/* Player 2 */
    
} Level, *Board;



/**
 * \brief Function to print coordinates
 * \param coordinate : Coordinate
 */
void affiche_coordonnee(Coordinates coordonnee);


/**
 * \brief Function to perform allocations to obtain a level of the given size 
 *
 * \param size : Coordinates, size of the board
 * \return Board, a game board
 */
Board malloc_board (Coordinates size);


/**

 * \brief Function that frees the memory taken by a level
 * \param gameboard : Board, level of the board
 */
void free_board (Board board);


/**
 * \brief Initializes a player
 * \param init_coo : Coordinates, coordonates of the player
 * \param init_dir : Direction, direction of the player
 * \param speed_player_init : unsigned long, speed of the player
 * \param type : TypeObject
 * \return Player, a player
 */
Player init_player(Coordinates init_coo, Direction init_dir, unsigned long speed_player_init, TypeObject type);


/**
 * \brief Initializes a game level 
 * \param board : Board, a level of game
 * \param size : Coordinates, coordinates of the game board
 */
void init_board(Board board, Coordinates size);


/**
 * \brief Function that moves a player
 * \param board : Board, a game board 
 * \param player : Player*, a player
 * \return int 
*/
int move_players(Board board, Player* player);


/**
 * \brief Check if the game is over according to the state of the board
 * \param board : Board, a gameboard 
 * \return true if the game is lost, false if not.
*/
bool check_game_over(Board board);


/**
 * \brief Check if the player(s) won the game according to the state of the board
 * \param board : Board, a game board 
 * \return true if the game is win, false if not
*/
bool check_victory(Board board);

/**
 * \brief Check if the player can move or not, if he can, make its field "can_player_move" true
 * \param p : Player *, board for the player's movement
 */
void check_player_move(Player *p);

/**
 * \brief Check if the next case where the player is going in its next move
 * \param type : TypeObject to check the next case's type
 * \param player : Player to check its direction 
 * \param board : Board, a game board
 * \return true if the player goes to an object, false otherwise
*/
bool going_to_obj(Board board, Player player, TypeObject type);

/**
 * \param board : Board, to update after trigger the switch
 * \param player : Player, a player  
*/
void trigger_switch(Board board, Player player);

/**
 * \brief Function that verify if two coordinates are equals or not
 * \param first : Coordinates, the first coordinate to compare
 * \param second : Coordinates, the second coordinate to compare
 * \return bool, true if both of the coordinates are equals, false otherwise
 */
bool equals_coordinates(Coordinates first, Coordinates second);


/**
 * \brief Function to move a projectile 
 * \param board : Board, a game board
 * \param coordinates : Coordinates*, coordinates of the projectile
 */
void move_projectile(Board gameboard, Coordinates *Coordinates);

/**
 * \brief Function to check if an object is heading towards the wall 
 * \param x : unsigned int, coordinate x of the position of the object to analize
 * \param y : unsigned int, coordinate y of the position of the object to analize
 * \param direction : Direction, the direction of the object 
 * \param board : Board, a gameboard 
 * \return bool, true if the object is heading towards the well, false otherwise
 */
bool is_object_going_to_crash(unsigned int x, unsigned int y, Direction direction, Board Board);




/**
 * \brief Function to check if a level has been passed / reached
 * \param board : Board, a game board
 * \return bool, true if the level has been reached, false otherwise
 */
bool check_player_reached(Board gameboard);


/**
 * \brief Function that print in the stdout the level given in argument
 * \param board : Board, the game board
 */
void print_board (Board gameboard); /* Affiche dans le terminal le
                                       * Niveau donnee en argument */


#endif