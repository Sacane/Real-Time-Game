#ifndef __OPT__H__
#define __OPT__H__


#include <getopt.h>
#include "wrapper.h"
#include "niveau.h"
#include "parser.h"
#include "commande.h"

void opt_management(int argc, char* argv[], int *mode, char *name_file, Plateau *niveau);



#endif