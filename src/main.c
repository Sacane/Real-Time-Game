#include <stdio.h>
#include "../include/test.h"
#include "../include/test_gui.h"
#include "../include/opt.h"

void command_launch(){
	

    
    Plateau niveau = niveau0();
    Tas* tas = construit_Tas (niveau);
    Evenement e;
    printf("affichage du tas au début : \n");
    affiche_Niveau(niveau);
    while (true) { 

        if ( un_evenement_est_pret(tas)) {
            e = ote_minimum(tas);
            execute_evenement(e, tas, niveau);
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
                execute_evenement(e, tas, niveau);
            }
            affiche_Niveau(niveau);
        }   
        else
            millisleep (10); 
        if(niveau->est_vivant == false){
            break;
        }
    }

    free_Tas(tas);
    free_Niveau(niveau);
}


int main(int argc, char* argv[]) {
    
    int mode;
    char* name_file;
    mode = COMMAND;
    name_file = (char*)malloc(sizeof(char) * BUFSIZ);
    if(argc >= 2){
        parse_opt(argc, argv, &mode, name_file);
    }

    switch(mode){
        case DEBUG:
            main_test();
            break;
        case COMMAND:
            command_launch();
            break;
        case GRAPHIC:
            main_gui_test();
            break;
        default:
            break;
    }

    free(name_file);
    return EXIT_SUCCESS;
}
