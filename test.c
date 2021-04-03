#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {

    VIDE = 0,          LANCEUR,           MUR,
    PROJECTILE,        PERSONNAGE,        DESTINATION,

} TypeObjet;

typedef struct {
  TypeObjet type;     /* Type de l'objet */
  void* donnee_suppl; /* Donnee supplementaire: son type depend de 
                       * `type` ci-dessus:
                       * - Deplacement*  si  type == PROJECTILE
                       * - Generation* si type == LANCEUR
                       * - donnee\_suppl vaut NULL pour les 
                       *   autres types. */
} Objet;

typedef struct {
  unsigned long intervalle; /* Intervalle entre deux envois
                             * de projectiles */
  unsigned long allure_proj; /* Allure des projectiles envoyes */
} Generation;


typedef enum { 
  HAUT,              
  GAUCHE, 
  BAS,               
  DROITE
} Direction;


typedef struct {
  Direction direction; /* Direction du deplacement */
  unsigned long allure; /* Allure du deplacement */
} Deplacement;


int main(int argc, char const *argv[])
{
    Objet obj;
    obj.type = LANCEUR;
    /* Initialisation du type gen */
    Generation* gen;
    gen = (Generation*)malloc(sizeof(Generation));
    gen->allure_proj = 1000.0;
    gen->intervalle = 100;
    /* Initialisation du type deplacement */
    Deplacement* deplacement;
    deplacement = (Deplacement*)malloc(sizeof(Deplacement));
    deplacement->direction = HAUT;
    deplacement->allure = 1000;

    if(obj.type == LANCEUR){
        obj.donnee_suppl = gen;
        printf("%ld\n", ((Generation*)obj.donnee_suppl)->allure_proj);
    }
    else if(obj.type == PROJECTILE){
        obj.donnee_suppl = deplacement;
        printf("%ld\n", ((Deplacement*)obj.donnee_suppl)->allure);
    }

    
    
    return 0;
}
