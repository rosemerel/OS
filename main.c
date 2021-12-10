#include "includes.c"
#include "paging.c"
#include "display.c"

// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem();
//display the list of holes in memory
void displayHoles(mem_t *mem);

//It should be possible to use this memory as indicated in the main :
int main()
{
     system("clear");
    //initialize the memory
    mem_t *mem = initMem();

    //allocate some space
    address_t adr1 = MyAlloc(mem, 5);
    address_t adr2 = MyAlloc(mem, 10);
    address_t adr3 = MyAlloc(mem, 100);

    printf("\nWe allocated 3 adresses:\nadr1: %ld (page %ld)\nadr2: %ld (page %ld)\nadr3: %ld (page %ld)\n", adr1, adr1/PAGE_SIZE, adr2, adr2/PAGE_SIZE, adr3, adr3/PAGE_SIZE);
    displayAll(mem);

    //Free some space
    myFree(mem, adr1, 5);
    printf("WE RELEASED adr1 (at adress %ld, size %d)\n", adr1, 5);
    displayAll(mem);

    myFree(mem, adr2, 10);
    printf("WE RELEASED adr2 (at address %ld, size %d)\n", adr2, 10);
    displayAll(mem);


    //write on bytes
    myWrite(mem, adr3, 543); // write on the 1st byte
    myWrite(mem, adr3+9, 34); // write on the 10th byte
    printf("WE WRITTEN ON THE 1ST AND 10TH BYTE OF adr3 (at address %ld)\n", adr3);
    display_physmem(14, 28, mem->physmem); getchar(); system("clear");

    //get those values written via the memory
    printf("WE CALLED THE READ FUNCTION AS WELL\n");
    byte_t val1 = myRead(mem, adr3);
    byte_t val2 = myRead(mem, adr3+9);
    //print them 
    printf("\nval1 = %d\nval2 = %d\n", val1, val2);
    getchar(); system("clear");

    //Release adr3
    myFree(mem, adr3, 100);
    printf("WE RELEASED THE adr3\n");
    displayAll(mem);

}

// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem()
{
    printf("Initialization of memory ...\n");
    //INTIALIZE MEMORY structure
    mem_t *memory = (mem_t *)malloc(sizeof(mem_t));
    memory->root = (hole_t *)malloc(sizeof(hole_t));
    //INITIALIZE HOLE LIST
    //=> here there is 1 hole which is of the size of the memory (all the memory is a hole bc it's empty)
    memory->root->adr = 0;
    memory->root->next = NULL;
    memory->root->prev = NULL;
    memory->root->sz = MEM_SIZE;
    displayHoles(memory); getchar(); 
    //INITIALIZE PAGE TABLE
    
    for (int i = 0; i < PAGETABLE_SIZE; ++i)
    {
        memory->page_table[i] = -1; //not allocated
    }
    displayPageTable(0,10, memory->page_table); getchar(); 
    //INITIALIZE RAM VECTOR
    for (int i = 0; i < PAGETABLE_SIZE; ++i)
    {
        memory->RAM_vector[i] = 0; //empty
    }
    displayRAMVector(0,10, memory->RAM_vector); getchar(); 
    display_physmem(0,10, memory->physmem); getchar(); system("clear");

    return memory;
}

