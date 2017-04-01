#include <stdio.h>
#include <stdlib.h>

void PrintHex(char* buffer, int length){
    int i;
    for(i = 0;i < length; i++){ 
        printf("%hhx ",buffer[i]);
    }
}


int main(int argc, char** argv){
    void* s = malloc(16*sizeof(char));
    FILE* f = fopen(argv[1],"r");
    fread(s,sizeof(char),15,f);
    PrintHex((char*)s,15);
    free(s);
    return 0;
}