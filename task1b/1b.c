#include <stdio.h>
#include <stdlib.h>

typedef struct link link;
 


typedef struct virus {
    unsigned short length;
    char name[16];
    char signature[];
}virus;

struct link {
    virus *v;
    link *next;
};

void PrintHex(char* buffer, int length){
    int i;
    for(i = 0;i < length; i++){ 
        printf("%hhX ",buffer[i]);
    }
}

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

void list_print(link *virus_list){
    virus *vir;
    while(virus_list){
        vir = virus_list->v;
        printf("Virus name: %s \n",(*vir).name);
        printf("Virus length: %hu \n",(*vir).length);
        printf("signature: \n");
        PrintHex((*vir).signature,(int)(*vir).length);
        printf("\n");
        virus_list = virus_list->next;
        
    }
} 
link* list_append(link* virus_list, virus* data){
    if(!virus_list){
        link* virus_link = (link*)malloc(sizeof(link));
        virus_link->next = NULL;
        virus_link->v = data;
        return virus_link;
    }
    virus_list->next = list_append(virus_list->next,data);
    return virus_list;
}
 
void list_free(link *virus_list){
    if(virus_list->next)
        list_free(virus_list->next);
    free(virus_list->v);
    free(virus_list);
    
}



int main(int argc, char** argv){
    char* length = (char*)malloc(2*sizeof(char));
    FILE* f = fopen(argv[1],"r");
    char endian = fgetc(f);
    fgetc(f);
    link* virus_link = NULL;
    
    while(fread(length,sizeof(char),2,f) != 0){
        unsigned short len;
        if(endian)
            len = (length[0]<<8) + length[1];
        else
            len = (length[1]<<8) + length[0];
        
        virus* v = allocate_virus(len-18);
        
        fread(((*v).name),sizeof(char),16,f);
        fread(((*v).signature),sizeof(char),len - 18,f);
        virus_link = list_append(virus_link, v);
            
        
    }
    free(length);
    fclose(f);
    list_print(virus_link);
    list_free(virus_link);
    return 0;
    
}