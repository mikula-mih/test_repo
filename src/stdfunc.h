#ifndef STDFUNC_H
#define STDFUNC_H

#define NAME_LEN 100
#define EXIT_SUCCESS 0

struct master build_master(int rank, const char *name, double strength);
void print_master(struct master m);

#endif

