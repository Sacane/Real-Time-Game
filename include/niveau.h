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
    unsigned long speed_player;

}Player;

typedef struct Niveau{
    
    Coordonnees taille; 
    Objet** objets; 
    bool is_game_over;
    Coordonnees coo_destination;
    bool mulptiplayer_mode;
    Player p1;
    Player p2;
    
} Niveau, *Plateau;



void affiche_coordonnee(Coordonnees coordonnee);

Plateau malloc_Niveau (Coordonnees taille); /* Effectue les malloc's
                                             * pour obtenir un 
                                             * Niveau* de la taille 
                                             * donnee */
void free_Niveau (Plateau niveau); /* Libere la memoire prise par un
                                    * Niveau */


Player init_player(Coordonnees init_coo, Direction init_dir, unsigned long speed_player_init, TypeObjet type);

void init_niveaux(Plateau niveau, Coordonnees taille);

int move_players(Plateau board, Player* player);

bool check_game_over(Plateau board);

void check_player_move(Player *p);

/*return true si le player va vers un interrupteur, false sinon*/
bool from_position_to_switch(Plateau board, Player player);

bool est_coordonnee_equivalent(Coordonnees first, Coordonnees second);

void deplace_projectile(Plateau niveau, Coordonnees *coordonnees);

bool se_dirige_vers_mur(unsigned int x, unsigned int y, Direction direction, Plateau plateau);

bool check_player_reached(Plateau niveau);

void affiche_Niveau (Plateau niveau); /* Affiche dans le terminal le
                                       * Niveau donnee en argument */



#endif