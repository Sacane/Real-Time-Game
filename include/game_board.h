/**
 * \file : game_board.h
 * \authors : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __GAME_BOARD__H__
#define __GAME_BOARD__H__

#include "object.h"

#define MODE_ONE_PLAYER 0;
#define MODE_TWO_PLAYER 1;

/* Structure to store the datas of a player. */
typedef struct player{
    
    TypeObjet typePlayer;
    Coordinates coo_player;
    Direction dir_player;
    unsigned long moment_depl_player;
    bool is_player_alive;
    bool can_player_move;
    bool has_player_win;
    unsigned long speed_player;

}Player;

typedef struct Level{
    
    Coordinates taille; 
    Objet** objets; 
    bool is_game_over;
    Coordinates coo_destination;
    bool mulptiplayer_mode;
    Player p1;
    Player p2;
    
} Level, *Board;



/**
 * Function to print coordinates
 * @param coordinate : Coordinate
 */
void affiche_coordonnee(Coordinates coordonnee);


/**
 * Function to perform allocations to obtain a level of the given size
 * @param size : Coordinates, size of the board
 * @return : Board, a game board  
 */
Board malloc_board (Coordinates taille); /* Effectue les malloc's
                                             * pour obtenir un 
                                             * Niveau* de la taille 
                                             * donnee */

/**
 * Function that frees the memory taken by a level
 * @param level : Board, level of the board
 */
void free_board (Board board); /* Libere la memoire prise par un
                                    * Niveau */


Player init_player(Coordinates init_coo, Direction init_dir, unsigned long speed_player_init, TypeObjet type);

/**
 * Function that initializes a game level 
 * @param level : Board, a level of game
 * @param size : Coordinates, coordinates of the game board
 */
void init_board(Board board, Coordinates taille);

int move_players(Board board, Player* player);


/**
 * check if the game is over according to the state of the board
 * \param board of the game
 * \return true if the game is lost, false if not.
*/
bool check_game_over(Board board);


/**
 * check if the player(s) won the game according to the state of the board
 * \param board of the game
 * \return true if the game is win, false if not
*/
bool check_victory(Board board);

/**
 * Function that verify the player's movement
 * @param level : Board, board for the player's movement
 */
void check_player_move(Player *p);

/**
 * check if the next case where the player is going in its next move
 * \param type to check the next case's type
 * \param player to check its direction 
 * \param board
 * \return true si le player va vers un interrupteur, false sinon
*/
bool going_to_obj(Board board, Player player, TypeObjet type);


/**
 * \param board to update after trigger the switch
 * \param player 
*/
void trigger_switch(Board board, Player player);

/**
 * Function that verify if two coordinates are equals or not
 * @param first : Coordinates, the first coordinate to compare
 * @param second : Coordinates, the second coordinate to compare
 * @return bool, true if both of the coordinates are equals, false otherwise
 */
bool equals_coordinates(Coordinates first, Coordinates second);


/**
 * Function to move a projectile 
 * @param level : Board, a game board
 * @param coordinates : Coordinates*, coordinates of the projectile
 */
void move_projectile(Board gameboard, Coordinates *Coordinates);

/**
 * Function to check if an object is heading towards the wall 
 * @param x : unsigned int, coordinate x of the position of the object to analize
 * @param y : unsigned int, coordinate y of the position of the object to analize
 * @param direction : Direction, the direction of the object 
 * @return bool, true if the object is heading towards the well, false otherwise
 */
bool se_dirige_vers_mur(unsigned int x, unsigned int y, Direction direction, Board Board);

/**
 * Function to check if a level has been passed / reached
 * @param level : Board, the game board
 * @return bool, true if the level has been reached, false otherwise
 */
bool check_player_reached(Board gameboard);


/**
 * Fonction that print in the terminal the level given in argument
 * @param level : Board, the game board
 */
void print_board (Board gameboard); /* Affiche dans le terminal le
                                       * Niveau donnee en argument */


#endif