//
// Created by Davide on 14/05/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operationfile.h"

char* getblocco(vkey_t* key){
    return key->block->key;
}


vkey_t* create_key(vblock_t* first){
    vkey_t *key =malloc(sizeof(vkey_t));
    //key->index=0;
    key->block=first;
    return key;
}
vblock_t* create_block(char* block_content){
    vblock_t *new_block= malloc(sizeof(vblock_t));
    strcpy(new_block->key,block_content);
    new_block->size= (int) strlen(block_content);
    new_block->next= NULL;
    return new_block;
}
void add_block(char* content, vblock_t **first, vblock_t **last){
    vblock_t *new_block=create_block(content);
    if(*first == NULL){
        *first= new_block;
        (*first)->next = *first;
    }else{
        new_block->next=(*last)->next;
        (*last)->next = new_block;
    }
    *last=new_block;
}
vkey_t* load_file(char* file){
    vblock_t *first = NULL;
    vblock_t *last = NULL;
    char buffer[256];
    FILE *fin;
    fin=fopen(file, "r");
    if(fin== NULL){
        // printf("%s",file);
        perror("Si e verificato un errore");
        exit(1);
    }
    while(fgets(buffer,256* sizeof(char),fin) != NULL) {
        add_block(buffer, &first, &last);
    }
    fclose(fin);
    return create_key(first);
}

void saveintofile(char * s, char *file){
    FILE *fp;
    fp=fopen(file,"w");
    if(fp==NULL){
        exit(0);
    }
    fputs(s,fp);
    fclose(fp);
}