#ifndef __BOARD__H__
#define __BOARD__H__

#include "array_obj.h"
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
    Array **box;
    Player player1;
    Player player2;
    Coordonnees coo_destination;
    bool est_niveau_termine;

}Game, *Board;


Player init_player(Coordonnees coordonnee, Direction dir_player);

Board malloc_board(Coordonnees size);

void free_board(Board board);

void move_projectile(Board gameboard, Coordonnees *coo_proj,unsigned int index);
bool is_object_moveable(Coordonnees coo_obj, Direction direction, Board board);

#endif