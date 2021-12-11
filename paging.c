#include "includes.c"
#include "continuous.c"

typedef int bool;
#define true 1
#define false 0

//functions definition
address_t MyAlloc(mem_t *mem, int size);
bool allocateRAM(mem_t *mem, int i);
// assign a value to a byte
void myWrite(mem_t *mp, address_t p, byte_t val);
// read memory from a byte
byte_t myRead(mem_t *mp, address_t p);

address_t MyAlloc(mem_t *mem, int size)
{
    int adr = myAllocCont(mem, size);

    int beginning_page = adr / PAGE_SIZE;
    int ending_page = (adr + size - 1) / PAGE_SIZE;

    //for each page used in this new allocation
    for (int i = beginning_page; i <= ending_page; ++i)
    {
        //if this page is not aleady allocated
        if (mem->page_table[i] == -1)
        {
            if(allocateRAM(mem, i) == false){
                printf("memory full");
            }
        }
    }
    return adr;
}
bool allocateRAM(mem_t *mem, int i)
{
    //then allocate it in the RAM
    for (int j = 0; j < MEM_SIZE; ++j)
    {
        //if this part of memory is empty
        if (mem->RAM_vector[j] == 0)
        {
            //create the link btwn page table & physmem
            int RAM_address = j * PAGE_SIZE;
            mem->page_table[i] = RAM_address;
            //tell to the programm that this part of memory is not available anymore
            mem->RAM_vector[j] = 1;
            //quite the function
            return true;
        }
    }
}
void myFree(mem_t *mem, address_t adr, int size)
{
    int beginning_page = adr / PAGE_SIZE;
    int ending_page = (adr + size - 1) / PAGE_SIZE;

    //release the allocated space in virtual memory
    myContFree(mem, adr, size);
    //for each page which was containing this memory
    for (int page = beginning_page; page <= ending_page; ++page)
    {
        //search if they are empty now
        hole_t *hole = mem->root;
        while (hole)
        {
            //if the page is empty now
            if (hole->adr <= (page * PAGE_SIZE) && (hole->adr + hole->sz) >= (page * PAGE_SIZE + PAGE_SIZE))
            {
                //release the memory
                mem->RAM_vector[mem->page_table[page]] = 0;
                mem->page_table[page] = -1;
                //quit the while
                break;
            }
            hole = hole->next;
        }
    }
}

void myWrite(mem_t *mp, address_t p, byte_t val)
{
    int page = p / PAGE_SIZE;
    int offset = p % PAGE_SIZE;

    mp->physmem[mp->page_table[page] + offset] = val;
}

byte_t myRead(mem_t *mp, address_t p)
{
    int page = p / PAGE_SIZE;
    int offset = p % PAGE_SIZE;
    return mp->physmem[mp->page_table[page] + offset];
}