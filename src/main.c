#include <stdio.h>
#include "../include/niveau.h"
#include "../include/commande.h"
#include "../include/test.h"

int main(void) {

    /* Partie test pour comprendre le castage (utilisation dans commande.c) */
    Deplacement* dep; /*Déclaration du déplacement à stocker*/
    dep = (Deplacement*)malloc(sizeof(Deplacement)); /*Allouage car manipulation de pointeur*/
    dep->direction = HAUT; /* initialisation */
    dep->allure = 1001.0;  /* des champs à stocker */
    
    Objet obj; /*Déclaration de l'objet à manipuler*/
    unsigned long ld = 10.0; /*Juste pour flex*/
    obj.donnee_suppl = dep; /*transtypage (ou castage) du générique (void *)*/
    printf("%ld\n", ((Deplacement*)(obj.donnee_suppl))->allure); /*Manipulation du générique avec castage. */
    printf("%ld\n", ld + ((Deplacement*)(obj.donnee_suppl))->allure);
    

    /* Test d'allocation de mémoire et d'affichage de niveau */
    printf("===== Test d'allocation de mémoire et d'affichage de niveau  ======\n\n");

    Plateau niveau = NULL;
    niveau = niveau0();
    affiche_Niveau(niveau);

    free_Niveau(niveau);
    

    printf("\n");

    free(dep);

    /* ======== TEST ========*/
    

    main_test();
    return 0;
}
