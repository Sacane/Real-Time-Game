/**
 * \fichier : niveau.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __NIVEAU__H__
#define __NIVEAU__H__

#include "objet.h"

#define MODE_ONE_PLAYER 0;
#define MODE_TWO_PLAYER 1;


typedef struct player{
    
    TypeObjet typePlayer;
    Coordonnees coo_player;
    Direction dir_player;
    unsigned long moment_depl_player;
    bool is_player_alive;
    bool can_player_move;
    bool has_player_win;
    unsigned long speed_player;

}Player;

typedef struct Level{
    
    Coordonnees taille; 
    Objet** objets; 
    bool is_game_over;
    Coordonnees coo_destination;
    bool mulptiplayer_mode;
    Player p1;
    Player p2;
    
} Level, *Board;



/**
 * Function to print coordinates
 * @param coordinate : Coordinate
 */
void affiche_coordonnee(Coordonnees coordonnee);


/**
 * Function to perform allocations to obtain a level of the given size
 * @param size : Coordinates, size of the board
 * @return : Board, a game board  
 */
Board malloc_board (Coordonnees taille); /* Effectue les malloc's
                                             * pour obtenir un 
                                             * Niveau* de la taille 
                                             * donnee */

/**
 * Function that frees the memory taken by a level
 * @param level : Board, level of the board
 */
void free_board (Board board); /* Libere la memoire prise par un
                                    * Niveau */


Player init_player(Coordonnees init_coo, Direction init_dir, unsigned long speed_player_init, TypeObjet type);

/**
 * Function that initializes a game level 
 * @param level : Board, a level of game
 * @param size : Coordinates, coordinates of the game board
 */
void init_board(Board board, Coordonnees taille);

int move_players(Board board, Player* player);

bool check_game_over(Board board);

bool check_victory(Board board);

/**
 * Function that verify the player's movement
 * @param level : Board, board for the player's movement
 */
void check_player_move(Player *p);

/*return true si le player va vers un interrupteur, false sinon*/
bool going_to_obj(Board board, Player player, TypeObjet type);

void trigger_switch(Board board, Player player);

/**
 * Function that verify if two coordinates are equals or not
 * @param first : Coordinates, the first coordinate to compare
 * @param second : Coordinates, the second coordinate to compare
 * @return bool, true if both of the coordinates are equals, false otherwise
 */
bool est_coordonnee_equivalent(Coordonnees first, Coordonnees second);


/**
 * Function to move a projectile 
 * @param level : Board, a game board
 * @param coordinates : Coordinates*, coordinates of the projectile
 */
void deplace_projectile(Board niveau, Coordonnees *coordonnees);

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
bool check_player_reached(Board niveau);


/**
 * Fonction that print in the terminal the level given in argument
 * @param level : Board, the game board
 */
void print_board (Board niveau); /* Affiche dans le terminal le
                                       * Niveau donnee en argument */


#endif