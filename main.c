#include "includes.c"
#include "continuous.c"
#include "paging.c"

//It should be possible to use this memory as indicated in the main :
int main() {
    //initialize the memory
    mem_t *mem      = initMem();

    //allocate some space 
/*     address_t adr1  = myAlloc(mem, 5);
    address_t adr2  = myAlloc(mem, 10);
    address_t adr3  = myAlloc(mem, 100);

    //Free some space in memory
    myFree(mem, adr1, 5);
    myFree(mem, adr2, 10);
    displayHoles(mem);

    //write on bytes
    myWrite(mem, adr3, 543); // write on the 1st byte

    myWrite(mem, adr3+9, 34); // write on the 10th byte

    //get those values written via the memory
    byte_t val1 = myRead(mem, adr3);
    byte_t val2 = myRead(mem, adr3+9);

    //print them 
    printf("\nval1 = %d\nval2 = %d\n", val1, val2);

    address_t adr4  = myAlloc(mem, 7);
    displayHoles(mem);
} */
}

// dynamically allocates a mem_t structure and initializes its content
mem_t *initMem(){
    //INTIALIZE MEMORY structure
    mem_t* memory       = (mem_t*) malloc(sizeof(mem_t));
    memory->root        = (hole_t*) malloc(sizeof(hole_t));
    //INITIALIZE HOLE LIST
    //=> here there is 1 hole which is of the size of the memory (all the memory is a hole bc it's empty)
    memory->root->adr   = 0;
    memory->root->next  = NULL;
    memory->root->prev  = NULL;
    memory->root->sz    = MEM_SIZE;

    return memory;
}




//display the list of holes in memory (debug using)
void displayHoles(mem_t* mem){

    hole_t* root = mem->root;
    int i = 0;

    printf("\n---LIST OF HOLES---\n");

    while(root != NULL){
        int prev, hole, next;
        if(root->prev){
            prev = root->prev->adr;
        }else{
            prev = -1;
        }
        if(root->next){
            next = root->next->adr;
        }
        else{
            next = -1;
        }
        hole = root->adr;
        printf("\nhole nb:%d \nhole size:%d\nprev hole address:%d\nhole address:%d\nnext hole address:%d\n", 
        i, root->sz, prev, hole, next);
        root = root->next;
        ++i;
    }
}