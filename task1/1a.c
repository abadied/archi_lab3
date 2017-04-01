#include <stdlib.h>
#include <stdio.h>

typedef struct virus virus;
 
struct virus {
    unsigned short length;
    char name[16];
    char signature[];
};

void PrintHex(char* buffer, int length){
    int i;
    for(i = 0;i < length; i++){ 
        printf("%hhx ",buffer[i]);
    }
}


int main(int argc, char** argv){
    void* endian = (char*)malloc(2*sizeof(char));
    virus* v = (virus*)(malloc(sizeof(virus)));;
    FILE* f = fopen(argv[1],"r");
    
    fread(endian,sizeof(char),2,f);
    fread((void*)(&(*v).length),sizeof(char),2,f);
    fread((void*)((*v).name),sizeof(char),16,f);
    
    fread((void*)((*v).signature),sizeof(char),80,f);
    PrintHex((char*)endian,2);
    printf("%d \n",(*v).length);
  
    
    printf("%s \n",(*v).name);
    
    free(endian);
    free(v);
    return 0;
    
}