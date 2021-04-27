#include "../include/test_gui.h"

void test_gui(){

    Plateau niveau = niveau0();
    int x, y;
    int size_case = niveau->taille.x * niveau->taille.y;
    MLV_Image *font;
    MLV_Image *array_img[11];
    
    MLV_create_window("RealTimeGame", "Game", size_case * niveau->taille.y, size_case * niveau->taille.x);
    init_array_img(array_img, niveau, size_case);
    printf("initialisation of the images.. OK\n");
    font = MLV_load_image("assets/font.jpeg");
    assert(font != NULL);
    MLV_resize_image(font, size_case * niveau->taille.y, size_case * niveau->taille.x);
    printf("Initialisation du plateau..");
    init_plateau(niveau, size_case, font);
    printf("OK\n");
    printf("update du plateau..");
    if(array_img[0] != NULL){
        printf("!=null\n");
    }
    update_plateau(niveau, array_img, size_case, font);
    printf("OK\n");
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);

    MLV_free_image(font);
    free_Niveau(niveau);
    free_array_img(array_img);
    MLV_free_window();
}