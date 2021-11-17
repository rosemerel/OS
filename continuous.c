#include "includes.c"

// allocates space in bytes (byte_t) using First-Fit, Best-Fit or Worst-Fit
address_t myAllocConts(mem_t *mp, int sz){
    
    //first fit
    return firstFit(mp, sz);
    //best fit 
    //return bestFit(mp, sz);
    //worst fit
    //return worstFit(mp, sz);
} 

address_t firstFit(mem_t *mp, int sz){
     //from the first hole in memory
    hole_t* hole = mp->root;
    //browse the list of holes
    while(hole != NULL){
        //if the hole has a sufficient size
        if(hole->sz >= sz){

            //if the size to allocate == the size of the hole
            if(hole->sz == sz){
                //define the address to allocate
                address_t adr = hole->adr;
                //delete this hole in the list
                deleteHole(mp, hole);
                return adr;
            }
            //if the size of the hole is > of the size to allocate
            else{
                address_t adr = giveMemory(hole, sz);
                return adr;
            }         
        }

        else{
            //check the next hole
            hole = hole->next;
        }
        
    }
    //Error (return null?)
    return -1;
}

address_t bestFit(mem_t *mp, int sz){
    //from the first hole in memory
    hole_t* hole = mp->root;
    hole_t* smallestHole = hole;

    //Research the smallest hole (>= sz)
    while(hole != NULL){

        if(hole->sz < smallestHole->sz && hole->sz >= sz){
            smallestHole = hole;
        }
        hole = hole->next;
    }

    //if the size is stricly sufficient
    if(smallestHole->sz > sz){
        address_t adr = giveMemory(smallestHole, sz);
        return adr;
    }
    //if it's exactly the size
    else if(smallestHole->sz == sz){
        address_t adr = smallestHole->adr;
        deleteHole(mp, smallestHole);
        return adr;
    }

    //Error (return null?)
    return -1;
}

address_t worstFit(mem_t* mp, int sz){
    //from the first hole in memory
    hole_t* hole = mp->root;
    hole_t* largestHole = hole;
    //Research the largest hole
    while(hole != NULL){

        if(hole->sz > largestHole->sz){
            largestHole = hole;
        }
        hole = hole->next;
    }
    //if the size of the largest hole is stricly sufficient
    if(largestHole->sz > sz){
        //allocate the memory into the largest hole
        address_t adr = giveMemory(largestHole, sz);
        return adr;
    }
    //if it's exaclty the size 
    else if(largestHole->sz == sz){
        //allocate the memory into the largest hole
        address_t adr = largestHole->adr;
        //delete the hole in the list
        deleteHole(mp, largestHole);
        return adr;
    }
    //error
    return -1;
}




// release memory that has already been allocated previously
void myContFree(mem_t *mp, address_t p, int sz){

    //add this hole in the list
    hole_t* hole = mp->root;

    //For each hole in the list
    while(hole != NULL){
        //search where is the hole into the list
        if(hole->prev && hole->adr > p && p > hole->prev->adr){
            insertHole(mp, hole->prev, hole, p, sz);
            break;
        }else if(p < hole->adr){
            insertHole(mp, hole->prev, hole, p, sz);
            break;
        }
        //go to the next hole
        hole = hole->next;
    }
}

void insertHole(mem_t* mp, hole_t* before, hole_t* after, address_t p, int sz){
    //if the new hole is next to the after & before
    if(after != NULL && before != NULL && ((before->adr + before->sz) == p && (p + sz) == after->adr)){
        enlargeHole(after, before->sz + sz, before->adr);
        
        if(before->prev){
            before->prev->next = after;
        }
        else{
            mp->root = after;
        }
    }
    //if the new hole is next to the after hole
    else if(after != NULL && (after->adr == (p +sz))){
        enlargeHole(after, sz, p);
          
    }
    //if the hole is next to the previous
    else if(before != NULL && ((before->adr + before->sz) == p)){
        enlargeHole(before, sz, before->adr);
    }
    //the hole is alone 
    else {
        addHole(mp, after, p, sz);
    }
}

// assign a value to a byte
/* void myWrite(mem_t *mp, address_t p, byte_t val){
   if(p >= 0 && p < SIZE){
        mp->mem[p] = val;
   }
}

// read memory from a byte
byte_t myRead(mem_t *mp, address_t p){
    if(p >= 0 && p < SIZE){
        return mp->mem[p];
    }
    return - 1;
    
} */


//TOOLS FUNCTIONS

//delete a hole from the list
void deleteHole(mem_t* mp, hole_t* hole){
    //if there is a hole before this one in the list
    if(hole->prev){
        hole->prev->next = hole->next;
    }
    //if it's the first hole & there is a next hole
    else if(hole->next){
        mp->root = hole->next;
    }
    //if it was the only hole in the list
    else{
        mp->root = NULL;
    } 
}

//enlarge a hole (if 2 holes are next to each other)
void enlargeHole(hole_t* hole, int sz, address_t newAdress){
    hole->sz  += sz;
    hole->adr = newAdress;
}

//add a new hole into the list
void addHole(mem_t* mp, hole_t* nextHole, address_t p, int sz){
    //create the new hole
    hole_t* newHole = (hole_t*) malloc(sizeof(hole_t));
    newHole->adr = p;
    newHole->sz = sz;
    //insert the new hole into the list
    newHole->next = nextHole;
    newHole->prev = nextHole->prev;

    if(nextHole->prev){
        nextHole->prev->next = newHole;
    }else{
        mp->root = newHole;
    }
    
    nextHole->prev = newHole;
}

//give some memory from a hole and genere a new address
address_t giveMemory(hole_t* hole, int sz){
    address_t adr = hole->adr;
    hole->sz -= sz;
    hole->adr += sz; 
    return adr;
}