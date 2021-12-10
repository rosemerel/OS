#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef __MMU__H__
#define __MMU__H__
//#define SIZE        65536
#define PAGE_SIZE       128
#define MEM_SIZE        32768
#define PAGETABLE_SIZE  (MEM_SIZE/PAGE_SIZE)


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
    //byte_t          mem[SIZE];
    int             page_table[PAGE_SIZE]; //page table
    byte_t          physmem[MEM_SIZE]; //RAM
    int             RAM_vector[MEM_SIZE/PAGE_SIZE]; //RAM vector
    hole_t*         root; // holes list
} mem_t;

//-----------------------TOOLS FUNCTIONS-----------------------



//-----------------------MAIN FUNCTIONS-----------------------



#endif