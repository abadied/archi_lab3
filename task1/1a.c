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
    void* endian = (char*)malloc(sizeof(char));
    char* length = (char*)malloc(2*sizeof(char));
    /*virus* v = allocate_virus(80);*/
    FILE* f = fopen(argv[1],"r");
    
    fread(endian,sizeof(char),1,f);
    
    while(fread(length,sizeof(char),2,f) != 0){
        unsigned short len = ((length[1] << 8) & 0xFF00) | (length[0] & 0xFF);
        virus* v = allocate_virus(len);
        printf("%hu \n",(*v).length);
        fread((void*)((*v).name),sizeof(char),16,f);
        fread((void*)((*v).signature),sizeof(char),len,f);
        printf("%s \n",(*v).name);
        PrintHex((*v).signature,(int)(*v).length);
        free(v);
        
    }
   
    free(endian);
    
    return 0;
    
}