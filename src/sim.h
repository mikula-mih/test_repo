#ifndef __STDC__
#error This header requires a Standard C compiler
#endif

#include "stdfunc.h"

struct master {
  int rank;
  char name[NAME_LEN+1];
  double strength;
};
