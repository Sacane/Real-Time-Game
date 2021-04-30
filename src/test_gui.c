#include "../include/test_gui.h"



void launch_gui(Plateau niveau){
    unsigned int x, y;
    
    int decalage_x, decalage_y;
    decalage_x = (niveau->taille.y < niveau->taille.x) ? 50 : 25;
    decalage_y = (niveau->taille.y > niveau->taille.x) ? 50 : 25;
    printf("%d %d\n", decalage_x, decalage_y);
    MLV_Image *font;
    MLV_Image *array_img[11];
    MLV_get_desktop_size(&x, &y);
    unsigned int width = (x / (niveau->taille.y)) - decalage_y, height = (y / niveau->taille.x) - decalage_x; 
    int size_case = 60;
    printf("%d\n", size_case);
    MLV_Keyboard_button touche;
    Arbre tas = construit_Tas (niveau);
    Evenement e;
    MLV_create_window("RealTimeGame", "Game", x, y);
    printf("x : %d | y : %d\n", x, size_case * niveau->taille.x);
    init_array_img(array_img, size_case);
    resize_all_img(array_img, width, height);
    font = MLV_load_image("assets/font.jpeg");
    assert(font != NULL);
    MLV_resize_image(font, width * niveau->taille.y, height * niveau->taille.x);

    update_plateau(niveau, array_img, font, width, height);
    niveau->dir_perso = DROITE;
    while (true) {
        if(niveau->est_vivant == false){
            break;
        }
        while(MLV_get_event(&touche, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL) != MLV_NONE){
            verifie_mouvement_personnage(niveau);
            action_listener(touche, niveau);
        }
        if(touche == MLV_KEYBOARD_ESCAPE){
            break;
        }
        if (un_evenement_est_pret(tas)) {
            e = ote_minimum(tas);
            execute_evenement(e, tas, niveau);
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
                execute_evenement(e, tas, niveau);
            }
            
            update_plateau(niveau, array_img, font, width, height);
            MLV_actualise_window();
            
        }   
        else
            millisleep (100);
        MLV_actualise_window();
    }
    MLV_free_image(font);
    MLV_free_window();
    printf("program ended in : %lums\n", maintenant());
    free_Tas(tas);
    printf("end_free\n");
}