#include "../include/level_maker.h"


/* a modifié en local*/

Board niveau0() {

    Board niveau;
    Coordonnees taille_niveau, coo_destination;
    taille_niveau.x = 5;
    taille_niveau.y = 10;
    niveau = malloc_Niveau(taille_niveau);
    init_niveaux(niveau, taille_niveau);
    
    Generation* gen;
    Generation* gen2;
    gen2 = (Generation*)malloc(sizeof(Generation));
    gen = (Generation*)malloc(sizeof(Generation));

    gen2->allure_proj = une_milliseconde*300;
    gen2->intervalle = une_seconde;
    gen->allure_proj = une_milliseconde*300;
    gen->intervalle = une_seconde;

    niveau->objets[0][0].type = LAUNCHER;
    niveau->objets[0][0].donnee_suppl = gen;
    niveau->objets[3][5].type = LAUNCHER;
    niveau->objets[3][5].donnee_suppl = gen2;
    niveau->objets[4][9].type = DESTINATION;
	coo_destination.x = 4;
    coo_destination.y = 9;
    niveau->coo_destination = coo_destination;
    /* init WALL */
    niveau->objets[1][0].type = WALL;
    niveau->objets[1][1].type = WALL;
    niveau->objets[1][2].type = WALL;
    niveau->objets[1][3].type = WALL;
    niveau->objets[1][4].type = WALL;
    niveau->objets[1][5].type = WALL;
    niveau->objets[1][6].type = WALL;
    niveau->objets[1][8].type = WALL;
    niveau->objets[2][8].type = WALL;
    niveau->objets[3][8].type = WALL;
    niveau->objets[4][8].type = WALL;

    Coordonnees coo_p1, coo_p2;
    coo_p1.x = 4;
    coo_p1.y = 0;
    coo_p2.x = 3;
    coo_p2.y = 9;
    niveau->p2 = init_player(coo_p2, SOUTH, une_milliseconde * 10, PLAYER2);
    niveau->p1 = init_player(coo_p1, SOUTH, une_milliseconde * 10, PLAYER1);
    niveau->objets[coo_p1.x][coo_p1.y].type = PLAYER1;
    niveau->objets[coo_p2.x][coo_p2.y].type = PLAYER2;
    niveau->mulptiplayer_mode = true;
    
    return niveau;
}



Board niveau1test(){

    Board niveau;
    Generation* gen;
    Coordonnees taille_niveau, coo_door, coo_door2;
    taille_niveau.x = 5;
    taille_niveau.y = 10;
    coo_door.x = 3;
    coo_door.y = 2;
    niveau = malloc_Niveau(taille_niveau);
    init_niveaux(niveau, taille_niveau);
    coo_door2.x = 1;
    coo_door2.y = 8;
    Trigger *trigg, *trigg2;
    trigg = (Trigger*)malloc(sizeof(Trigger));
    trigg2 = (Trigger*)malloc(sizeof(Trigger));
    trigg->coo_door = coo_door; 
    trigg2->coo_door = coo_door2;
    
    gen = (Generation*)malloc(sizeof(Generation));
    gen->allure_proj = une_milliseconde*300;
    gen->intervalle = une_seconde;
    niveau->objets[4][2].type = LAUNCHER;
    niveau->objets[4][2].donnee_suppl = gen;
    niveau->objets[3][2].type = DOOR;
    niveau->objets[1][8].type = DOOR;
    niveau->objets[3][9].type = SWITCH;
    niveau->objets[2][8].type = SWITCH;
    niveau->objets[3][9].donnee_suppl = trigg;
    niveau->objets[2][8].donnee_suppl = trigg2;
    Coordonnees coo_p1, coo_p2;
    coo_p1.x = 0;
    coo_p1.y = 0;
    coo_p2.x = 2;
    coo_p2.y = 4;

    niveau->p2 = init_player(coo_p2, SOUTH, une_milliseconde * 10, PLAYER2);
    niveau->p1 = init_player(coo_p1, SOUTH, une_milliseconde * 10, PLAYER1);
    niveau->objets[coo_p1.x][coo_p1.y].type = PLAYER1;
    niveau->objets[coo_p2.x][coo_p2.y].type = PLAYER2;
    niveau->mulptiplayer_mode = true;

    return niveau;

}


Board niveau1(){

    Board niveau;
    Coordonnees taille_niveau, coo_destination;
    taille_niveau.x = 5;
    taille_niveau.y = 10;
    niveau = malloc_Niveau(taille_niveau);
    init_niveaux(niveau, taille_niveau);

    Generation* gen;
    Generation* gen2;
    Generation* gen3;
    gen = (Generation*)malloc(sizeof(Generation));
    gen2 = (Generation*)malloc(sizeof(Generation));
    gen3 = (Generation*)malloc(sizeof(Generation));
    
    gen->allure_proj = une_milliseconde*300;
    gen->intervalle = une_seconde;
	gen2->allure_proj = une_milliseconde*300;
    gen2->intervalle = une_seconde;
	gen3->allure_proj = une_milliseconde*300;
    gen3->intervalle = une_seconde;


	niveau->objets[4][0].type = LAUNCHER;
    niveau->objets[4][0].donnee_suppl = gen;
    niveau->objets[1][6].type = LAUNCHER;
    niveau->objets[1][6].donnee_suppl = gen2;
	niveau->objets[3][9].type = LAUNCHER;
    niveau->objets[3][9].donnee_suppl = gen3;
    niveau->objets[0][3].type = DESTINATION;
    coo_destination.x = 0; 
    coo_destination.y = 3;
    niveau->coo_destination = coo_destination;
    /* init WALL */
    niveau->objets[0][2].type = WALL;
    niveau->objets[1][2].type = WALL;
    niveau->objets[1][3].type = WALL;
    niveau->objets[1][4].type = WALL;
    niveau->objets[1][5].type = WALL;
    niveau->objets[2][3].type = WALL;
    niveau->objets[4][5].type = WALL;
    niveau->objets[4][6].type = WALL;

    Coordonnees coo_p1;
	coo_p1.x = 0;
    coo_p1.y = 0;
    niveau->p1 = init_player(coo_p1, SOUTH, une_milliseconde * 10, PLAYER1);
    niveau->objets[coo_p1.x][coo_p1.y].type = niveau->p1.typePlayer;
    

	return niveau;
}


Board niveau2(){

	Board niveau;
    Coordonnees taille_niveau, coo_destination;
    taille_niveau.x = 8;
    taille_niveau.y = 12;
    niveau = malloc_Niveau(taille_niveau);
    init_niveaux(niveau, taille_niveau);
    
    Generation* gen;
    Generation* gen2;
    Generation* gen3;
    Generation* gen4;
    gen = (Generation*)malloc(sizeof(Generation));
    gen2 = (Generation*)malloc(sizeof(Generation));
    gen3 = (Generation*)malloc(sizeof(Generation));
    gen4 = (Generation*)malloc(sizeof(Generation));

	gen->allure_proj = une_milliseconde * 300;
    gen->intervalle = une_seconde;
	gen2->allure_proj = une_milliseconde * 300;
    gen2->intervalle = une_seconde;
	gen3->allure_proj = une_milliseconde * 300;
    gen3->intervalle = une_seconde;
	gen4->allure_proj = une_milliseconde * 300;
    gen4->intervalle = une_seconde;

	niveau->objets[1][2].type = LAUNCHER;
    niveau->objets[1][2].donnee_suppl = gen;
    niveau->objets[2][10].type = LAUNCHER;
    niveau->objets[2][10].donnee_suppl = gen2;
	niveau->objets[6][4].type = LAUNCHER;
    niveau->objets[6][4].donnee_suppl = gen3;
	niveau->objets[6][9].type = LAUNCHER;
    niveau->objets[6][9].donnee_suppl = gen4;
    niveau->objets[0][0].type = DESTINATION;
    coo_destination.x = 0;
    coo_destination.y = 0;
    niveau->coo_destination = coo_destination;
	/* init WALL */
    niveau->objets[1][5].type = WALL;

    niveau->objets[2][0].type = WALL;
    niveau->objets[2][1].type = WALL;
    niveau->objets[2][2].type = WALL;
    niveau->objets[2][3].type = WALL;
    niveau->objets[2][4].type = WALL;
    niveau->objets[2][5].type = WALL;
    niveau->objets[2][11].type = WALL;

    niveau->objets[4][0].type = WALL;

    niveau->objets[4][3].type = WALL;
    niveau->objets[4][4].type = WALL;
    niveau->objets[4][5].type = WALL;
    niveau->objets[4][6].type = WALL;
    niveau->objets[4][7].type = WALL;
    niveau->objets[4][8].type = WALL;
    niveau->objets[4][9].type = WALL;
    niveau->objets[4][10].type = WALL;
    niveau->objets[4][11].type = WALL;

    niveau->objets[6][0].type = WALL;
    niveau->objets[6][1].type = WALL;
    niveau->objets[6][2].type = WALL;
    niveau->objets[6][3].type = WALL;

    niveau->objets[6][5].type = WALL;
    niveau->objets[6][6].type = WALL;

    niveau->objets[6][10].type = WALL;
    niveau->objets[6][11].type = WALL;

    Coordonnees coo_p;
	coo_p.x = 7;
    coo_p.y = 0;
    niveau->p1 = init_player(coo_p, SOUTH, une_milliseconde * 10, PLAYER1);
    niveau->objets[coo_p.x][coo_p.y].type = niveau->p1.typePlayer;


	return niveau;

}


Board niveau3(){

	Board niveau;
    Coordonnees taille_niveau, coo_dest;
    taille_niveau.x = 8;
    taille_niveau.y = 12;
    niveau = malloc_Niveau(taille_niveau);
    init_niveaux(niveau, taille_niveau);

    Generation* gen;
    Generation* gen3;
    Generation* gen4;
    gen = (Generation*)malloc(sizeof(Generation));
    gen3 = (Generation*)malloc(sizeof(Generation));
    gen4 = (Generation*)malloc(sizeof(Generation));

	gen->allure_proj = une_milliseconde * 300;
    gen->intervalle = une_seconde;
	gen3->allure_proj = une_milliseconde * 300;
    gen3->intervalle = une_seconde;
	gen4->allure_proj = une_milliseconde * 300;
    gen4->intervalle = une_seconde;

	niveau->objets[0][9].type = LAUNCHER;
    niveau->objets[0][9].donnee_suppl = gen;
	niveau->objets[4][11].type = LAUNCHER;
    niveau->objets[4][11].donnee_suppl = gen3;
	niveau->objets[5][2].type = LAUNCHER;
    niveau->objets[5][2].donnee_suppl = gen4;
    niveau->objets[0][6].type = DESTINATION;
    coo_dest.x = 0;
    coo_dest.y = 6;
    niveau->coo_destination = coo_dest;
	/* init WALL */
    niveau->objets[1][0].type = WALL;
    niveau->objets[1][1].type = WALL;

    niveau->objets[3][0].type = WALL;

    niveau->objets[0][7].type = WALL;
    niveau->objets[1][7].type = WALL;
    niveau->objets[2][7].type = WALL;
    niveau->objets[2][6].type = WALL;
    niveau->objets[2][5].type = WALL;
    niveau->objets[2][4].type = WALL;
    niveau->objets[2][3].type = WALL;
    niveau->objets[3][3].type = WALL;
    niveau->objets[4][3].type = WALL;
    niveau->objets[5][3].type = WALL;
    niveau->objets[6][3].type = WALL;

    niveau->objets[5][4].type = WALL;
    niveau->objets[5][5].type = WALL;
    niveau->objets[5][6].type = WALL;
    niveau->objets[6][6].type = WALL;
    niveau->objets[6][7].type = WALL;
    niveau->objets[6][8].type = WALL;
    niveau->objets[6][9].type = WALL;

    Coordonnees coo_p;

	coo_p.x = 3;
    coo_p.y = 4;
    niveau->p1 = init_player(coo_p, SOUTH, une_milliseconde * 10, PLAYER1);
    niveau->objets[coo_p.x][coo_p.y].type = niveau->p1.typePlayer;
    

	return niveau;
}
