#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __MMU__H__
#define __MMU__H__
#define SIZE        65536

typedef short       byte_t; 
typedef long int    address_t;

//HOLE IN MEMORY
typedef struct hole {
    address_t       adr; //address of the hole in memory
    int             sz; //size of the hole
    struct hole*    next; //next hole 
    struct hole*    prev; //previous hole
} hole_t;

//MEMORY STRUCTURE
typedef struct {
    byte_t          mem[SIZE];
    hole_t*         root; // holes list
} mem_t;

//-----------------------TOOLS FUNCTIONS-----------------------

//display the list of holes in memory
void displayHoles(mem_t* mem);
//Add a new hole into the list
void addHole(mem_t* mp, hole_t* nextHole, address_t p, int sz);
void insertHole(mem_t* mp, hole_t* prev, hole_t* next, address_t p, int sz);
//enlarge a hole
void enlargeHole(hole_t* hole, int sz, address_t newAdress);
//delete a hole
void deleteHole(mem_t* mp, hole_t* hole);
//give the memory from a hole & create a new address
address_t giveMemory(hole_t* hole, int sz);

//-----------------------MAIN FUNCTIONS-----------------------
// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem(); 
// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fit
address_t myAlloc(mem_t *mp, int sz);
address_t firstFit(mem_t *mp, int sz);
address_t bestFit(mem_t *mp, int sz);
address_t worstFit(mem_t *mp, int sz);
// release memory that has already been allocated previously
void myFree(mem_t *mp, address_t p, int sz);
// assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val);
// read memory from a byte
byte_t myRead(mem_t *mp, address_t p);
#endif