#include "../include/gui.h"

static void init_vertical(int taillecase, int colonne, int lignes){
	int i, j;
	for(i = 0; i < colonne+1; i++){
		for(j = 0; j < lignes+1; j++){
			MLV_draw_line(i*taillecase, j*taillecase, i*taillecase, taillecase, MLV_COLOR_WHITE);
		}
	}
	MLV_actualise_window();
}

static void init_horizontal(int taillecase, int colonne, int ligne){
	int i, j;
	for(i = 0; i < ligne+1; i++){
		for(j = 0; j < colonne+1; j++){
			MLV_draw_line(j*taillecase, i*taillecase, taillecase, i*taillecase, MLV_COLOR_WHITE);
		}
	}
	MLV_actualise_window();
}

void init_plateau(Plateau niveau, int height){  
    init_vertical(height, niveau->taille.y, niveau->taille.x);
    init_horizontal(height, niveau->taille.y, niveau->taille.x);
    MLV_draw_line(0, 0, 0, height, MLV_COLOR_WHITE);
    MLV_draw_rectangle(0, 0, height * niveau->taille.y, height * niveau->taille.x, MLV_COLOR_WHITE);
    MLV_actualise_window();
}