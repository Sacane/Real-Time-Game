#include "../include/temps.h"


long unsigned maintenant() { return clock(); }

/* La fonction `millisleep(i)` fait en sorte que le programme 
 * attende i millisecondes avant de continuer a s'executer. */
void millisleep(unsigned long i) {
    struct timeval tim;
    tim.tv_sec = 0;
    tim.tv_usec =  i * 1000;
    select(0, NULL, NULL, NULL, &tim);
}

