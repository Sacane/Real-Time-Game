#include "../include/test_gui.h"

void test_gui(){

    Plateau niveau = niveau0();
    int x, y;
    int size_case = niveau->taille.x * niveau->taille.y;
    MLV_Image *font;
    MLV_Image *array_img[11];
    
    MLV_create_window("RealTimeGame", "Game", size_case * niveau->taille.y, size_case * niveau->taille.x);
    init_array_img(array_img, size_case);
    printf("init of the images.. OK\n");
    font = MLV_load_image("assets/font.jpeg");
    assert(font != NULL);
    MLV_resize_image(font, size_case * niveau->taille.y, size_case * niveau->taille.x);
    printf("Init of board..");
    init_plateau(niveau, size_case, font);
    printf("OK\n");
    printf("update of the board..");
    update_plateau(niveau, array_img, size_case, font);
    printf("OK\n");
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);

    MLV_free_image(font);
    free_Niveau(niveau);
    free_array_img(array_img);
    MLV_free_window();
}

void main_gui_test(){

    MLV_Image *font;
    MLV_Image *array_img[11];
    Plateau niveau = niveau0();
    int size_case = niveau->taille.x * niveau->taille.y;
    MLV_Keyboard_button touche;
    Arbre tas = construit_Tas (niveau);
    Evenement e;
    MLV_create_window("RealTimeGame", "Game", size_case * niveau->taille.y, size_case * niveau->taille.x);
    init_array_img(array_img, size_case);
    font = MLV_load_image("assets/font.jpeg");
    assert(font != NULL);
    MLV_resize_image(font, size_case * niveau->taille.y, size_case * niveau->taille.x);
    init_plateau(niveau, size_case, font);
    update_plateau(niveau, array_img, size_case, font);
    
    while (MLV_get_event(&touche, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL) == MLV_NONE || touche != MLV_KEYBOARD_ESCAPE) {
        if (un_evenement_est_pret(tas)) {
            e = ote_minimum(tas);
            execute_evenement(e, tas, niveau);
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
                execute_evenement(e, tas, niveau);
            }
            execute_evenement(e, tas, niveau);
            update_plateau(niveau, array_img, size_case, font);
            MLV_actualise_window();
            
        }   
        else
            millisleep (100);
    }
    free_Tas(tas);
    free_Niveau(niveau);
}