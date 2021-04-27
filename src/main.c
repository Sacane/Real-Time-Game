#include <stdio.h>
#include "../include/test.h"
#include "../include/test_gui.h"
void main_naif(){
	
    Niveau* niveau = niveau0();
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
            millisleep (10); /* Toujours attendre quelques millisecondes
            quand on ne fait pas grand chose (ici un
            seul test) dans la boucle. */
        if(niveau->est_vivant == false){
            break;
        }
    }

    free_Tas(tas);
    free_Niveau(niveau);
}


int main(void) {
    
    int choice;
    printf("1 : tests\n");
    printf("2 : main\n");
    printf("3 : graphic_test\n");
    scanf("%d", &choice);
	
	if(choice == 2){
    	main_naif();
	}    
    else if(choice == 1){
        main_test();
    }
    else if(choice == 3){
        main_gui_test();
    }
    

    return EXIT_SUCCESS;
}
