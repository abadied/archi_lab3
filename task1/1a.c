#include <stdlib.h>
#include <stdio.h>

typedef struct virus virus;
 
struct virus {
    unsigned short length;
    char name[16];
    char signature[];
};
struct virus *allocate_virus(unsigned short len){
    virus *v = malloc(sizeof(virus) + len*sizeof (char));
    if(!v){
        exit(EXIT_FAILURE);
    }
    (*v).length = len;
    unsigned short i;
    for(i = 0;i < len; i++)
        (*v).signature[i] = 0;

    return v;
}

void PrintHex(char* buffer, int length){
    int i;
    for(i = 0;i < length; i++){ 
        printf("%hhX ",buffer[i]);
    }
}


int main(int argc, char** argv){
    
    char* length = (char*)malloc(2*sizeof(char));
    FILE* f = fopen(argv[1],"r");
    char endian = fgetc(f);
    
    
    while(fread(length,sizeof(char),2,f) != 0){
        printf("%s \n",length);
        unsigned short len;
        if(endian)
            len = (length[0]<<8) + length[1];
        else
            len = (length[1]<<8) + length[0];
        
        virus* v = allocate_virus(len-18);
        printf("%hu \n",(*v).length);
        fread(((*v).name),sizeof(char),16,f);
        fread(((*v).signature),sizeof(char),len - 18,f);
        printf("%s \n",(*v).name);
        PrintHex((*v).signature,(int)(*v).length);
        free(v);
        
    }
    free(length);
    fclose(f);
    
    return 0;
    
}