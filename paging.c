#include "includes.c"

int MyAlloc(mem_t* mem, int size){
    int adr = myAllocCont(mem, size);
    int allowed_memory = adr + size;

}

/* int* getPages(int min, int max){
    int page_table_size = MEM_SIZE/PAGE_SIZE;
    int* pages = (int*)malloc(sizeof(int));
    int i = 0, index = 0;

    while(i < page_table_size){ 
        int begin = i;
        int end = begin + (PAGE_SIZE-1);
        
        if((min >= begin && min <= end) || (max >= begin && max <= end)){
            pages[index] = 
        }
        i += end +1;
    }
} */

int* getPages(int min, int max){
    
}