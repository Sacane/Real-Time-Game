#include "../include/level_maker.h"
#include "../include/board.h"

/* a modifié en local*/

Plateau niveau0() {

    Plateau niveau;
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

    niveau->objets[0][0].type = LANCEUR;
    niveau->objets[0][0].donnee_suppl = gen;
    niveau->objets[3][5].type = LANCEUR;
    niveau->objets[3][5].donnee_suppl = gen2;
    niveau->objets[4][9].type = DESTINATION;
	coo_destination.x = 4;
    coo_destination.y = 9;
    niveau->coo_destination = coo_destination;
    /* init mur */
    niveau->objets[1][0].type = MUR;
    niveau->objets[1][1].type = MUR;
    niveau->objets[1][2].type = MUR;
    niveau->objets[1][3].type = MUR;
    niveau->objets[1][4].type = MUR;
    niveau->objets[1][5].type = MUR;
    niveau->objets[1][6].type = MUR;
    niveau->objets[1][8].type = MUR;
    niveau->objets[2][8].type = MUR;
    niveau->objets[3][8].type = MUR;
    niveau->objets[4][8].type = MUR;


    niveau->coo_perso.x = 4;
    niveau->coo_perso.y = 0;
    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = PERSONNAGE;
    niveau->allure_perso = une_milliseconde * 50;


    return niveau;
}


Board niveau0_b(){

    Board board;
    Player player;
    Coordonnees size_board, coo_destination;
    size_board.x = 5;
    size_board.y = 10;
    coo_destination.x = 4;
    coo_destination.y = 9;
    player.coo_player.x = 4;
    player.coo_player.y = 0;

    board = malloc_board(size_board);

    init_board(board, size_board);

    init_player(player.coo_player, player.dir_player);

    Generation* gen;
    Generation* gen2;
    gen = (Generation*)malloc(sizeof(Generation));
    gen2 = (Generation*)malloc(sizeof(Generation));

    gen->allure_proj = une_milliseconde*300;
    gen->intervalle = une_seconde;
    gen2->allure_proj = une_milliseconde*300;
    gen2->intervalle = une_seconde;

    Objet wall;
    wall.type = MUR;
    wall.donnee_suppl = NULL;

    Objet destination;
    destination.type = DESTINATION;
    destination.donnee_suppl = NULL;


    Objet launcher1;
    launcher1.type = LANCEUR;
    launcher1.donnee_suppl = gen;

    Objet launcher2;
    launcher2.type = LANCEUR;
    launcher2.donnee_suppl = gen2;

    add_obj_in_lst(&board->box[1][0], wall);
    add_obj_in_lst(&board->box[1][1], wall);
    add_obj_in_lst(&board->box[1][2], wall);
    add_obj_in_lst(&board->box[1][3], wall);
    add_obj_in_lst(&board->box[1][4], wall);
    add_obj_in_lst(&board->box[1][5], wall);
    add_obj_in_lst(&board->box[1][6], wall);
    add_obj_in_lst(&board->box[1][7], wall);
    add_obj_in_lst(&board->box[1][8], wall);
    add_obj_in_lst(&board->box[2][8], wall);
    add_obj_in_lst(&board->box[3][8], wall);
    add_obj_in_lst(&board->box[4][8], wall);

    add_obj_in_lst(&board->box[4][9], destination);
    add_obj_in_lst(&board->box[0][0], launcher1);
    add_obj_in_lst(&board->box[3][5], launcher2);

    return board;
}


Plateau niveau1(){

    Plateau niveau;
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

    niveau->allure_perso = une_milliseconde * 50;

	niveau->objets[4][0].type = LANCEUR;
    niveau->objets[4][0].donnee_suppl = gen;
    niveau->objets[1][6].type = LANCEUR;
    niveau->objets[1][6].donnee_suppl = gen2;
	niveau->objets[3][9].type = LANCEUR;
    niveau->objets[3][9].donnee_suppl = gen3;
    niveau->objets[0][3].type = DESTINATION;
    coo_destination.x = 0; 
    coo_destination.y = 3;
    niveau->coo_destination = coo_destination;
    /* init mur */
    niveau->objets[0][2].type = MUR;
    niveau->objets[1][2].type = MUR;
    niveau->objets[1][3].type = MUR;
    niveau->objets[1][4].type = MUR;
    niveau->objets[1][5].type = MUR;
    niveau->objets[2][3].type = MUR;
    niveau->objets[4][5].type = MUR;
    niveau->objets[4][6].type = MUR;

	niveau->coo_perso.x = 0;
    niveau->coo_perso.y = 0;
    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = PERSONNAGE;

	return niveau;
}


Plateau niveau2(){

	Plateau niveau;
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

	niveau->objets[1][2].type = LANCEUR;
    niveau->objets[1][2].donnee_suppl = gen;
    niveau->objets[2][10].type = LANCEUR;
    niveau->objets[2][10].donnee_suppl = gen2;
	niveau->objets[6][4].type = LANCEUR;
    niveau->objets[6][4].donnee_suppl = gen3;
	niveau->objets[6][9].type = LANCEUR;
    niveau->objets[6][9].donnee_suppl = gen4;
    niveau->objets[0][0].type = DESTINATION;
    coo_destination.x = 0;
    coo_destination.y = 0;
    niveau->coo_destination = coo_destination;
	/* init mur */
    niveau->objets[1][5].type = MUR;

    niveau->objets[2][0].type = MUR;
    niveau->objets[2][1].type = MUR;
    niveau->objets[2][2].type = MUR;
    niveau->objets[2][3].type = MUR;
    niveau->objets[2][4].type = MUR;
    niveau->objets[2][5].type = MUR;
    niveau->objets[2][11].type = MUR;

    niveau->objets[4][0].type = MUR;

    niveau->objets[4][3].type = MUR;
    niveau->objets[4][4].type = MUR;
    niveau->objets[4][5].type = MUR;
    niveau->objets[4][6].type = MUR;
    niveau->objets[4][7].type = MUR;
    niveau->objets[4][8].type = MUR;
    niveau->objets[4][9].type = MUR;
    niveau->objets[4][10].type = MUR;
    niveau->objets[4][11].type = MUR;

    niveau->objets[6][0].type = MUR;
    niveau->objets[6][1].type = MUR;
    niveau->objets[6][2].type = MUR;
    niveau->objets[6][3].type = MUR;

    niveau->objets[6][5].type = MUR;
    niveau->objets[6][6].type = MUR;

    niveau->objets[6][10].type = MUR;
    niveau->objets[6][11].type = MUR;

	niveau->coo_perso.x = 7;
    niveau->coo_perso.y = 0;
    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = PERSONNAGE;
    niveau->allure_perso = une_milliseconde * 50;

	return niveau;

}


Plateau niveau3(){

	Plateau niveau;
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

	niveau->objets[0][9].type = LANCEUR;
    niveau->objets[0][9].donnee_suppl = gen;
	niveau->objets[4][11].type = LANCEUR;
    niveau->objets[4][11].donnee_suppl = gen3;
	niveau->objets[5][2].type = LANCEUR;
    niveau->objets[5][2].donnee_suppl = gen4;
    niveau->objets[0][6].type = DESTINATION;
    coo_dest.x = 0;
    coo_dest.y = 6;
    niveau->coo_destination = coo_dest;
	/* init mur */
    niveau->objets[1][0].type = MUR;
    niveau->objets[1][1].type = MUR;

    niveau->objets[3][0].type = MUR;

    niveau->objets[0][7].type = MUR;
    niveau->objets[1][7].type = MUR;
    niveau->objets[2][7].type = MUR;
    niveau->objets[2][6].type = MUR;
    niveau->objets[2][5].type = MUR;
    niveau->objets[2][4].type = MUR;
    niveau->objets[2][3].type = MUR;
    niveau->objets[3][3].type = MUR;
    niveau->objets[4][3].type = MUR;
    niveau->objets[5][3].type = MUR;
    niveau->objets[6][3].type = MUR;

    niveau->objets[5][4].type = MUR;
    niveau->objets[5][5].type = MUR;
    niveau->objets[5][6].type = MUR;
    niveau->objets[6][6].type = MUR;
    niveau->objets[6][7].type = MUR;
    niveau->objets[6][8].type = MUR;
    niveau->objets[6][9].type = MUR;

	niveau->coo_perso.x = 3;
    niveau->coo_perso.y = 4;
    niveau->objets[niveau->coo_perso.x][niveau->coo_perso.y].type = PERSONNAGE;
    niveau->allure_perso = une_milliseconde * 50;

	return niveau;
}
