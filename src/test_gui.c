#include "../include/test_gui.h"

void test_gui(){

    Plateau niveau = niveau0();
    int x, y;
    int size_case = niveau->taille.x * niveau->taille.y;
    MLV_Image *font;
    MLV_create_window("RealTimeGame", "Game", size_case * niveau->taille.y, size_case * niveau->taille.x);

    font = MLV_load_image("assets/font.jpeg");
    assert(font != NULL);

    MLV_resize_image(font, size_case * niveau->taille.y, size_case * niveau->taille.x);
    MLV_draw_image(font, 0, 0);
    init_plateau(niveau, size_case);
    
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);

    MLV_free_image(font);
    free_Niveau(niveau);

    MLV_free_window();
}