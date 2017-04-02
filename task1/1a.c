#include <stdlib.h>
#include <stdio.h>

typedef struct virus virus;
 
struct virus {
    unsigned short length;
    char name[16];
    char signature[];
};
struct virus *allocate_virus(unsigned short len){
    virus *v = malloc(sizeof *v + len*sizeof (*v).signature[0]);
    if(!v){
        exit(EXIT_FAILURE);
    }
    (*v).length = len;
    unsigned short ix;
    for(ix = 0;ix < len; ix++)
        (*v).signature[ix] = 0;

    return v;
}

void PrintHex(char* buffer, int length){
    int i;
    for(i = 0;i < length; i++){ 
        printf("%hhX ",buffer[i]);
    }
}


int main(int argc, char** argv){
    void* endian = (char*)malloc(2*sizeof(char));
    char length[2] = {'0','0'};
    virus* v = allocate_virus(80);
    FILE* f = fopen(argv[1],"r");
    
    fread(endian,sizeof(char),2,f);
    fread(length,sizeof(char),2,f);
    
    printf("%hu",(*v).length);
    
    printf("%hu",(*v).length);
    fread((void*)((*v).name),sizeof(char),16,f);
    
    fread((void*)((*v).signature),sizeof(char),80,f);
    PrintHex((char*)endian,2);
    
  
    printf("%s \n",(*v).name);
    PrintHex((*v).signature,(int)(*v).length);
    free(endian);
    free(v);
    return 0;
    
}