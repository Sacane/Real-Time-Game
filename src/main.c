#include <stdio.h>
#include "../include/test.h"
#include "../include/test_gui.h"
#include "../include/opt.h"
#include "../include/parser.h"

void command_launch(){
    
    Plateau niveau = niveau1();
    Tas* tas = construit_Tas(niveau);
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
    printf("before free\n");
    free_Tas(tas);
    printf("after free\n");
    free_Niveau(niveau);
    
}

void launch_command(Plateau niveau){
    
    Tas* tas = construit_Tas(niveau);
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
    printf("before free\n");
    free_Tas(tas);
    printf("after free\n");

}


int main(int argc, char* argv[]) {
    
    Plateau niveau = NULL;
    int mode;
    char* name_file = NULL;
    mode = COMMAND;
    name_file = (char*)malloc(sizeof(char) * BUFSIZ);
    
    
    opt_management(argc, argv, &mode, name_file, &niveau);
    

    switch(mode){
        case DEBUG:
            main_test();
            break;
        case COMMAND:
            launch_command(niveau);
            break;
        case GRAPHIC:
            launch_gui(niveau); 
            break;
        default:
            break;
    }
    free_Niveau(niveau);
    free(name_file);
    return EXIT_SUCCESS;
}
