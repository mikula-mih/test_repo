#include "stdfunc.h"
#include "sim.h"

#include <stdio.h>
#include <string.h>

void print_master(struct master m)
{
  printf("Master rank: %d\n", m.rank);
  printf("Master name: %s\n", m.name);
  printf("Master strength: %lf\n", m.strength);
}

struct master build_master(int rank, const char *name, double strength)
{
  struct master m;

  m.rank = rank;
  strcpy(m.name, name);
  m.strength = strength;

  return m;
}


