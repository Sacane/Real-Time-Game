#ifndef __OPT__H__
#define __OPT__H__


#include <getopt.h>
#include "parser.h"
#include "level_maker.h"

void opt_management(int argc, char* argv[], int *mode, char *name_file, Plateau *niveau);



#endif