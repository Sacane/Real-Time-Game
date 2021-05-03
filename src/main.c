#include <stdio.h>
#include "../include/test.h"
#include "../include/gui.h"
#include "../include/opt.h"
#include "../include/config_stdin.h"



static void launch_command(Plateau niveau, bool *is_reached){
    
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
                if(niveau->depl_perso_autorise == true)
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
        if(check_level_reached(niveau)){
            (*is_reached) = true;
            break;
        }
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
    bool is_level_reached = false;
    
    opt_management(argc, argv, &mode, name_file, &niveau);

    if(niveau == NULL){
        niveau = niveau0();
    }
    switch(mode){
        case DEBUG:
            main_test();
            break;
        case COMMAND:
            launch_command(niveau, &is_level_reached);
            break;
        case GRAPHIC:
            launch_gui(niveau); 
            break;
        case ERROR:
            printf("Une erreur est apparue, sortie du programme\n");
            if(NULL != niveau){
                free_Niveau(niveau);
            }
            free(name_file);
            return EXIT_FAILURE;
        default:
            break;
    }

    (is_level_reached) ? printf("Félicitation vous avez fini le niveau !\n") : printf("Vous avez perdu ! \n");

    free_Niveau(niveau);
    free(name_file);
    return EXIT_SUCCESS;
}
