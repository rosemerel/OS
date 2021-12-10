#include "includes.c"


//display the list of holes in memory (debug using)
void displayHoles(mem_t *mem)
{

    hole_t *root = mem->root;
    int i = 0;

    printf("\n---LIST OF HOLES---\n");

    while (root != NULL)
    {
        int prev, hole, next;
        if (root->prev)
        {
            prev = root->prev->adr;
        }
        else
        {
            prev = -1;
        }
        if (root->next)
        {
            next = root->next->adr;
        }
        else
        {
            next = -1;
        }
        hole = root->adr;
        printf("\nhole nb:%d \nhole size:%d\nprev hole address:%d\nhole address:%d\nnext hole address:%d\n",
               i, root->sz, prev, hole, next);
        root = root->next;
        ++i;
    }
    printf("\n");

}

//display the content of the page table between the two indexes requested
void displayPageTable(int begin, int end, int* page_table){
    printf("\n------PAGE TABLE------\n\n");
    if(begin != 0){
        printf("...\n");
    }
    for(int i = begin; i < end; ++i){
        printf("page_table[%d]=%d\n", i, page_table[i]);
    }
    if(end != PAGETABLE_SIZE){
        printf("...\n");
    }
}

//display the content of the RAMVector between the two indexes requested
void displayRAMVector(int begin, int end, int* RAM_vector){
    printf("\n------RAM Vector------\n\n");
    if(begin != 0){
        printf("...\n");
    }
    for(int i = begin; i < end; ++i){
        printf("RAM_vector[%d]=%d\n", i, RAM_vector[i]);
    }
    if(end != PAGETABLE_SIZE){
        printf("...\n");
    }
}

//display the content of the physmem between the two indexes requested
void display_physmem(int begin, int end, byte_t* physmem){
    printf("\n------Physical Memory content------\n\n");
    if(begin != 0){
        printf("...\n");
    }
    for(int i = begin; i < end; ++i){
        printf("physmem[%d]=%d\n", i, physmem[i]);
    }
    if(end != PAGETABLE_SIZE){
        printf("...\n");
    }
} 

void displayAll(mem_t* mem){
    displayHoles(mem);
    getchar();
    displayPageTable(0,5, mem->page_table);
    getchar();
    displayRAMVector(0,5, mem->RAM_vector);
    getchar();
    system("clear");
}