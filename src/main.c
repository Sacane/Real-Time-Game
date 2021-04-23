#include <stdio.h>
/*#include "../include/test.h"*/
#include "../include/tas.h"
#include "../include/commande.h"

static void main_naif(){
    Niveau* niveau = niveau0();
    Tas* tas = construit_Tas (niveau );
    printf("affichage du tas au début : \n");
    affiche_Tas(tas);
    affiche_Niveau(niveau);
    while (true) { /* La partie ne se termine jamais car on n ' a pas
        encore d ' actions de l ' utilisateur */

        if ( un_evenement_est_pret(tas)) {
            printf("pret !\n");
            Evenement e = ote_minimum(tas);
            printf("evenement : %lu\n", e.moment);
            execute_evenement(e, tas , niveau);
            affiche_Niveau(niveau);
        }   
        else
            millisleep (10000); /* Toujours attendre quelques millisecondes
            quand on ne fait pas grand chose (ici un
            seul test) dans la boucle. */
    }
}

void main_naif2(){
	
    Niveau* niveau = niveau0();
    Tas* tas = construit_Tas (niveau );
    Evenement e;
    printf("affichage du tas au début : \n");
    affiche_Tas(tas);
    affiche_Niveau(niveau);
    millisleep(100);
    while (true) { /* La partie ne se termine jamais car on n ' a pas
        encore d ' actions de l ' utilisateur */

        if ( un_evenement_est_pret(tas)) {
            e = ote_minimum(tas);
            execute_evenement(e, tas, niveau);
            while(e.moment == tas->valeurs[0].moment){
                e = ote_minimum(tas);
                execute_evenement(e, tas, niveau);
            }
            execute_evenement(e, tas, niveau);
            affiche_Niveau(niveau);
        }   
        else
            millisleep (50); /* Toujours attendre quelques millisecondes
            quand on ne fait pas grand chose (ici un
            seul test) dans la boucle. */
    }
    free_Tas(tas);
    free_Niveau(niveau);
}


int main(void) {

    main_naif2();

    /*main_test();*/

    return EXIT_SUCCESS;
}
