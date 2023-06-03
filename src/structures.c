/* Structures, Unions, Enumerations */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "stdfunc.h"
#include "weopon.h"
#include "sim.h"


int main(void)
{
  struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
  } part1 = {528, "Disk drive", 10},    // initializing structure variables
    part2 = {.number = 914, "Printer cable", .on_hand = 5};  // designated initializer

  struct {
    char name[NAME_LEN+1];
    int number;
    char sex;
  } employee1, employee2;

  printf("Part number: \t%10d\n", part1.number);
  printf("Part name: \t%10s\n", part1.name);
  printf("Quantity on hand: \t%d\n", part1.on_hand);

  part1.number = 158;
  part1.on_hand++;

  printf("Employee name: ");
  scanf(" %s", &employee1.name);

  /* "dummpy" structures to copy array */
  struct { int a[10]; } arr1, arr2;

  struct { 
    int a[10];
  } arr3 = {1,2,3,4,5,6,7,8,9,10};

  arr1 = arr2;  /* legal, since a1 and a2 are structures */

  printf("Hi, %s\n"
         "Your serial number is: %d\n",
         employee1.name, arr1.a[5] = 5);

  struct dummy {
    float array[10];
  };    /* declare a structure tag named dummpy */

  struct master theif, rouge;

  Weapon machineGun, lightSaber, dagger;

  struct master puss;
  puss = build_master(5, "Puss_in_Boots", 999);
  print_master(puss);

  print_master((struct master) { 4, "Goy", -1 });   /* compound literal */
  theif = (struct master) { 7, "Varid", 534 };
  print_master(theif);
















  if (EXIT_SUCCESS == false)
    printf("Wow you are such a loser!\n");
  
  return EXIT_SUCCESS;
}


