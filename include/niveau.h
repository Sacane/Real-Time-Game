/**
 * \fichier : niveau.h
 * \auteurs : Johan RAMAROSON RAKOTOMIHAMINA - Christine LI
 * \date de création : 01-04-21
 * \dernière modification : 21-05-21
 * 
 * DESCRIPTION
 *
 */

#ifndef __NIVEAU__H__
#define __NIVEAU__H__

#include "objet.h"

typedef struct player{

    TypeObjet typePlayer;
    Coordonnees coo_player;
    Direction dir_player;
    unsigned long moment_depl_player;
    bool is_player_alive;
    bool can_player_move;
    unsigned long speed_player;

}Player;

typedef struct Niveau{
    
    Coordonnees taille; 
    Objet** objets; 
    Coordonnees coo_perso; 
    unsigned long allure_perso; 
    bool depl_perso_autorise; 
    Direction dir_perso; 
    unsigned long moment_depl_perso;
    bool est_vivant;
    bool est_niveau_termine;
    Coordonnees coo_destination;
    Player p1;
    
} Niveau, *Plateau;



void affiche_coordonnee(Coordonnees coordonnee);

Plateau malloc_Niveau (Coordonnees taille); /* Effectue les malloc's
                                             * pour obtenir un 
                                             * Niveau* de la taille 
                                             * donnee */
void free_Niveau (Plateau niveau); /* Libere la memoire prise par un
                                    * Niveau */


Player init_player(Coordonnees init_coo, Direction init_dir, unsigned long speed_player_init, TypeObjet type);

void init_niveaux(Plateau niveau, Coordonnees taille);


/**
 * \arg niveau : plateau concernant le déplacement du joueur
 * Deplace le joueur selon une direction renseigné
 * \return true si le personnage ne meurt pas après son déplacement, false sinon.
 */
int deplace_joueur(Plateau niveau); 

int move_players(Plateau board, Player* player);


void verifie_mouvement_personnage(Plateau niveau);

void check_player_move(Plateau niveau, Player *p);

/**
 * Renvoi true si l'objet est prêt à rentré en contact avec un mur, false sinon.
*/
bool mur_en_contact(Plateau plateau, Objet obj);

/**
 * Renvoi true si l'objet est prêt à rentrer en contact avec le bord du terrain.
*/
bool bordure_en_contact(Plateau plateau, Objet obj);


/*Vérifie et renvoi true si le personnage est s'apprête à rentrer en conflit avec un mur */
bool perso_en_contact(Plateau plateau);

bool est_coordonnee_equivalent(Coordonnees first, Coordonnees second);

void deplace_projectile(Plateau niveau, Coordonnees *coordonnees);

bool se_dirige_vers_mur(unsigned int x, unsigned int y, Direction direction, Plateau plateau);

bool est_dans_plateau(Direction direction, Plateau plateau, unsigned int x, unsigned int y);

bool check_level_reached(Plateau niveau);

bool check_player_reached(Plateau niveau);

void affiche_Niveau (Plateau niveau); /* Affiche dans le terminal le
                                       * Niveau donnee en argument */

#endif