#ifndef __BOARD__H__
#define __BOARD__H__

#include "objet.h"

#include "niveau.h"

typedef struct Player{

    Coordonnees coo_player;
    bool est_vivant;
    Direction dir_player;
    bool depl_player_autorise;
    unsigned long moment_depl_perso;
    unsigned long allure_perso;

}Player;

typedef struct game{

    Coordonnees size;
    List_obj **box;
    Player player1;
    Player player2;
    Coordonnees coo_destination;
    bool est_niveau_termine;

}Game, *Board;


Player init_player(Coordonnees coordonnee, Direction dir_player);

Board malloc_board(Coordonnees size);

void free_board(Board board);

void init_board(Board board, Coordonnees size);


void deplace_projectile_b(Board board, Coordonnees *coordonnees, Objet projectile);

int deplace_joueur_b(Board board, Objet player_obj, Player *player);

#endif