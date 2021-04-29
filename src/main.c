#include <stdio.h>
#include "../include/test.h"
#include "../include/test_gui.h"
#include "../include/opt.h"
#include "../include/parser.h"
#include "../include/config_stdin.h"


void launch_command(Plateau niveau){
    
    init_stdin();
    Tas* tas = construit_Tas(niveau);
    Evenement e;
	char touche;
    printf("affichage du tas au début : \n");
    affiche_Niveau(niveau);
    printf("\n");
    while (true) {
        verifie_mouvement_personnage(niveau);
        while((touche = getchar()) != EOF){
            if(niveau->depl_perso_autorise == true){
                switch (touche)
                {
                case 'z':
                    niveau->dir_perso = HAUT;
                    break;
                case 's':
                    niveau->dir_perso = BAS;
                    break;
                case 'd':
                    niveau->dir_perso = DROITE;
                    break;
                case 'q':
                    niveau->dir_perso = GAUCHE;
                    break;
                default:
                    break;
                }
                deplace_joueur(niveau);
            }
        }

        if ( un_evenement_est_pret(tas)) {
            e = ote_minimum(tas);
            execute_evenement(e, tas, niveau);
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
                execute_evenement(e, tas, niveau);
            }
            affiche_Niveau(niveau);
    		printf("\n");
        }   
        else
            millisleep (10); 
        if(niveau->est_vivant == false){
            break;
        }
    }
    free_Tas(tas);
    restaure_stdin();

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
