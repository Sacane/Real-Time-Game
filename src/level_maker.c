/**
 * \file level_maker.c
 * \authors Ramaroson Rakotomihamina Johan && Li Christine
 * \date : 01-04-21
 * \last modification : 21-05-21
 * 
 * Module containing the functions of the game levels
 *
 */

#include "../include/level_maker.h"


/**
 * \fn Board level0()
 * \brief Function to initialize a game board (level 0)
 * \return Board, a game board
 */
Board level0() {

    Board board;
    Coordinates size_board, coo_destination;
    size_board.x = 5;
    size_board.y = 10;
    board = malloc_board(size_board);
    init_board(board, size_board);
    
    Generation* gen;
    Generation* gen2;
    gen2 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen2);


    gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);


    gen2->allure_proj = une_milliseconde*300;
    gen2->intervalle = une_seconde;
    gen->allure_proj = une_milliseconde*300;
    gen->intervalle = une_seconde;

    board->objects[0][0].type = LAUNCHER;
    board->objects[0][0].data = gen;
    board->objects[3][5].type = LAUNCHER;
    board->objects[3][5].data = gen2;
    board->objects[4][9].type = DESTINATION;
	coo_destination.x = 4;
    coo_destination.y = 9;
    board->coo_destination = coo_destination;

    board->objects[1][0].type = WALL;
    board->objects[1][1].type = WALL;
    board->objects[1][2].type = WALL;
    board->objects[1][3].type = WALL;
    board->objects[1][4].type = WALL;
    board->objects[1][5].type = WALL;
    board->objects[1][6].type = WALL;
    board->objects[1][8].type = WALL;
    board->objects[2][8].type = WALL;
    board->objects[3][8].type = WALL;
    board->objects[4][8].type = WALL;

    Coordinates coo_p1;
    coo_p1.x = 4;
    coo_p1.y = 0;

    board->p1 = init_player(coo_p1, SOUTH, une_milliseconde * 10, PLAYER1);
    board->objects[coo_p1.x][coo_p1.y].type = PLAYER1;
    board->mulptiplayer_mode = false;
    
    return board;
}


/**
 * \fn Board level1test()
 * \brief Function to initialize a game board (level 1 test)
 * \return Board, a game board
 */
Board level1test(){

    Board board;
    Generation* gen;
    Coordinates size_board, coo_door, coo_door2;
    size_board.x = 5;
    size_board.y = 10;
    coo_door.x = 3;
    coo_door.y = 2;
    board = malloc_board(size_board);
    init_board(board, size_board);
    coo_door2.x = 1;
    coo_door2.y = 8;
    Trigger *trigg, *trigg2;
    trigg = (Trigger*)malloc(sizeof(Trigger));
    verif_malloc(trigg);
    trigg2 = (Trigger*)malloc(sizeof(Trigger));
    verif_malloc(trigg2);
    trigg->coo_door = coo_door; 
    trigg2->coo_door = coo_door2;
    
    gen = (Generation*)malloc(sizeof(Generation));
    gen->allure_proj = une_milliseconde*300;
    gen->intervalle = une_seconde;
    board->objects[4][2].type = LAUNCHER;
    board->objects[4][2].data = gen;
    board->objects[3][2].type = DOOR;
    board->objects[1][8].type = DOOR;
    board->objects[3][9].type = SWITCH;
    board->objects[2][8].type = SWITCH;
    board->objects[3][9].data = trigg;
    board->objects[2][8].data = trigg2;
    Coordinates coo_p1, coo_p2;
    coo_p1.x = 0;
    coo_p1.y = 0;
    coo_p2.x = 2;
    coo_p2.y = 4;

    board->p2 = init_player(coo_p2, SOUTH, une_milliseconde * 10, PLAYER2);
    board->p1 = init_player(coo_p1, SOUTH, une_milliseconde * 10, PLAYER1);
    board->objects[coo_p1.x][coo_p1.y].type = PLAYER1;
    board->objects[coo_p2.x][coo_p2.y].type = PLAYER2;
    board->mulptiplayer_mode = true;

    return board;

}


/**
 * \fn Board level1()
 * \brief Function to initialize a game board (level 1)
 * \return Board, a game board
 */
Board level1(){

    Board board;
    Coordinates size_board, coo_destination;
    size_board.x = 5;
    size_board.y = 10;
    board = malloc_board(size_board);
    init_board(board, size_board);

    Generation* gen;
    Generation* gen2;
    Generation* gen3;
    gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
    gen2 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen2);
    gen3 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen3);
    
    gen->allure_proj = une_milliseconde*300;
    gen->intervalle = une_seconde;
	gen2->allure_proj = une_milliseconde*300;
    gen2->intervalle = une_seconde;
	gen3->allure_proj = une_milliseconde*300;
    gen3->intervalle = une_seconde;


	board->objects[4][0].type = LAUNCHER;
    board->objects[4][0].data = gen;
    board->objects[1][6].type = LAUNCHER;
    board->objects[1][6].data = gen2;
	board->objects[3][9].type = LAUNCHER;
    board->objects[3][9].data = gen3;
    board->objects[0][3].type = DESTINATION;
    coo_destination.x = 0; 
    coo_destination.y = 3;
    board->coo_destination = coo_destination;
    /* init WALL */
    board->objects[0][2].type = WALL;
    board->objects[1][2].type = WALL;
    board->objects[1][3].type = WALL;
    board->objects[1][4].type = WALL;
    board->objects[1][5].type = WALL;
    board->objects[2][3].type = WALL;
    board->objects[4][5].type = WALL;
    board->objects[4][6].type = WALL;

    Coordinates coo_p1;
	coo_p1.x = 0;
    coo_p1.y = 0;
    board->p1 = init_player(coo_p1, SOUTH, une_milliseconde * 10, PLAYER1);
    board->objects[coo_p1.x][coo_p1.y].type = board->p1.typePlayer;
    

	return board;
}


/**
 * \fn Board level2()
 * \brief Function to initialize a game board (level 2)
 * \return Board, a game board
 */
Board level2(){

	Board board;
    Coordinates size_board, coo_destination;
    size_board.x = 8;
    size_board.y = 12;
    board = malloc_board(size_board);
    init_board(board, size_board);
    
    Generation* gen;
    Generation* gen2;
    Generation* gen3;
    Generation* gen4;
    gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
    gen2 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen2);
    gen3 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen3);
    gen4 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen4);

	gen->allure_proj = une_milliseconde * 300;
    gen->intervalle = une_seconde;
	gen2->allure_proj = une_milliseconde * 300;
    gen2->intervalle = une_seconde;
	gen3->allure_proj = une_milliseconde * 300;
    gen3->intervalle = une_seconde;
	gen4->allure_proj = une_milliseconde * 300;
    gen4->intervalle = une_seconde;

	board->objects[1][2].type = LAUNCHER;
    board->objects[1][2].data = gen;
    board->objects[2][10].type = LAUNCHER;
    board->objects[2][10].data = gen2;
	board->objects[6][4].type = LAUNCHER;
    board->objects[6][4].data = gen3;
	board->objects[6][9].type = LAUNCHER;
    board->objects[6][9].data = gen4;
    board->objects[0][0].type = DESTINATION;
    coo_destination.x = 0;
    coo_destination.y = 0;
    board->coo_destination = coo_destination;
	/* init WALL */
    board->objects[1][5].type = WALL;

    board->objects[2][0].type = WALL;
    board->objects[2][1].type = WALL;
    board->objects[2][2].type = WALL;
    board->objects[2][3].type = WALL;
    board->objects[2][4].type = WALL;
    board->objects[2][5].type = WALL;
    board->objects[2][11].type = WALL;

    board->objects[4][0].type = WALL;

    board->objects[4][3].type = WALL;
    board->objects[4][4].type = WALL;
    board->objects[4][5].type = WALL;
    board->objects[4][6].type = WALL;
    board->objects[4][7].type = WALL;
    board->objects[4][8].type = WALL;
    board->objects[4][9].type = WALL;
    board->objects[4][10].type = WALL;
    board->objects[4][11].type = WALL;

    board->objects[6][0].type = WALL;
    board->objects[6][1].type = WALL;
    board->objects[6][2].type = WALL;
    board->objects[6][3].type = WALL;

    board->objects[6][5].type = WALL;
    board->objects[6][6].type = WALL;

    board->objects[6][10].type = WALL;
    board->objects[6][11].type = WALL;

    Coordinates coo_p;
	coo_p.x = 7;
    coo_p.y = 0;
    board->p1 = init_player(coo_p, SOUTH, une_milliseconde * 10, PLAYER1);
    board->objects[coo_p.x][coo_p.y].type = board->p1.typePlayer;


	return board;

}


/**
 * \fn Board level3()
 * \brief Function to initialize a game board (level 3)
 * \return Board, a game board
 */
Board level3(){

	Board board;
    Coordinates size_board, coo_dest;
    size_board.x = 8;
    size_board.y = 12;
    board = malloc_board(size_board);
    init_board(board, size_board);

    Generation* gen;
    Generation* gen3;
    Generation* gen4;
    gen = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen);
    gen3 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen3);
    gen4 = (Generation*)malloc(sizeof(Generation));
    verif_malloc(gen4);

	gen->allure_proj = une_milliseconde * 300;
    gen->intervalle = une_seconde;
	gen3->allure_proj = une_milliseconde * 300;
    gen3->intervalle = une_seconde;
	gen4->allure_proj = une_milliseconde * 300;
    gen4->intervalle = une_seconde;

	board->objects[0][9].type = LAUNCHER;
    board->objects[0][9].data = gen;
	board->objects[4][11].type = LAUNCHER;
    board->objects[4][11].data = gen3;
	board->objects[5][2].type = LAUNCHER;
    board->objects[5][2].data = gen4;
    board->objects[0][6].type = DESTINATION;
    coo_dest.x = 0;
    coo_dest.y = 6;
    board->coo_destination = coo_dest;
	/* init WALL */
    board->objects[1][0].type = WALL;
    board->objects[1][1].type = WALL;

    board->objects[3][0].type = WALL;

    board->objects[0][7].type = WALL;
    board->objects[1][7].type = WALL;
    board->objects[2][7].type = WALL;
    board->objects[2][6].type = WALL;
    board->objects[2][5].type = WALL;
    board->objects[2][4].type = WALL;
    board->objects[2][3].type = WALL;
    board->objects[3][3].type = WALL;
    board->objects[4][3].type = WALL;
    board->objects[5][3].type = WALL;
    board->objects[6][3].type = WALL;

    board->objects[5][4].type = WALL;
    board->objects[5][5].type = WALL;
    board->objects[5][6].type = WALL;
    board->objects[6][6].type = WALL;
    board->objects[6][7].type = WALL;
    board->objects[6][8].type = WALL;
    board->objects[6][9].type = WALL;

    Coordinates coo_p;

	coo_p.x = 3;
    coo_p.y = 4;
    board->p1 = init_player(coo_p, SOUTH, une_milliseconde * 10, PLAYER1);
    board->objects[coo_p.x][coo_p.y].type = board->p1.typePlayer;
    

	return board;
}
