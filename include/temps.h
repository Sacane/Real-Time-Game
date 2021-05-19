/**
 * Extern module use to make the time manipulation more understandable
 * \authors : University 'Gustave eiffel'
 * 
 */ 

#ifndef __TEMPS__H__
#define __TEMPS__H__

#include <sys/select.h>
#include <time.h>



/* La variable globale `une_seconde` vaut le nombre de "tick"
 * correspondant a une seconde.  Par exemple, si la condition
 * `maintenant()>=une_seconde` est vraie, cela signifie qu'au 
 * moins une seconde s'est ecoulee depuis le lancement du 
 * programme.  Similairement `maintenant()+une_seconde` 
 * represente le moment une seconde dans l'avenir. */
static const long unsigned une_seconde = CLOCKS_PER_SEC;


/* La variable globale `une_milliseconde` vaut le nombre de "tick" 
 * correspondant a une milliseconde, c'est-a-dire un millieme 
 * de seconde. */
static const long unsigned une_milliseconde = une_seconde/1000;


long unsigned maintenant();


/* La fonction `millisleep(i)` fait en sorte que le programme 
 * attende i millisecondes avant de continuer a s'executer. */
void millisleep(unsigned long i);


#endif