//
// Created by Davide on 15/05/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include "filedistance.h"
#include "filepath.h"
listafile_t* searchfileintosub(char *subdir, listafile_t *first , listafile_t *last,char *directory ,char * firstdir);
void generateblock(listafile_t **first, listafile_t **last, char *path, char *direct);
listafile_t * create_path_stringa(char *path , char *direct);



listafile_t* fileindir(listafile_t *file ,char *directory){
    char *subdir=NULL;
    char *firstdir=malloc(sizeof(char)*strlen(directory)+1);
    strncpy(firstdir,directory,strlen(directory)+1);
    listafile_t* first=searchfileintosub(subdir,file,file,directory,firstdir);
    free(subdir);
    return first;
}

listafile_t* searchfileintosub(char *subdir, listafile_t *first , listafile_t *last,char *directory,char *firstdir){
    struct dirent *de;
    DIR *dr = opendir(directory);
    char *subdirapp=malloc(strlen(directory)+1);
    strcpy(subdirapp,directory);
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory\n " );
        exit(1);
    }
    else {
        while ((de = readdir(dr)) != NULL){
            if(de->d_type==DT_REG) {
                generateblock(&first,&last,directory,de->d_name);
            }
        }
        rewinddir(dr);
        while(((de = readdir(dr)) != NULL)){
            if(strcmp(de->d_name,".")==0 || strcmp(de->d_name,"..")==0){
                continue;
            }
            if(de->d_type==DT_DIR) {
                subdir = realloc(subdir, sizeof(char) * strlen(directory) + sizeof(char) * strlen(de->d_name) + 2);
                if(subdir == NULL) exit(8);
                if(strstr(directory,firstdir)) strcpy(subdir, directory);
                else strcpy(directory,subdirapp);
                strncat(subdir, de->d_name, strlen(de->d_name));
                strcat(subdir, "/");
                last = searchfileintosub(subdir, first, last, subdir,firstdir);
                strcpy(directory,subdirapp);
            }
        }
        closedir(dr);
        free(subdirapp);
    }
    return first;
}
void generateblock(listafile_t **first, listafile_t **last, char *path, char *direct){
    listafile_t *new_block=create_path_stringa(path,direct);
    if((*first)->nome==NULL && (*last)->nome==NULL){
        *first= new_block;
        (*first)->next = *first;
    }else{
        new_block->next=(*last)->next;
        (*last)->next = new_block;
    }
    *last=new_block;
}

listafile_t * create_path_stringa(char *path, char *direct){
    listafile_t *new_block= malloc(sizeof(listafile_t)+1);
    if(new_block == NULL) exit(0);
    new_block->nome=malloc(sizeof(char)*strlen(direct)+strlen(path)+1);
    if(new_block->nome == NULL) exit(0);
    strcpy(new_block->nome,path);
    strcat(new_block->nome,direct);
    new_block->next= NULL;
    return new_block;
}

void calculatedistancelist(listafile_t *lista,char *file){
    listafile_t *first= lista;

    do{
        lista->distanza= Levenshtein_distance(load_file(file),load_file(lista->nome));
        lista=lista->next;
    }while(lista!=first);
}
void printlimitdistance(listafile_t *lista, int limit){
    listafile_t *first=lista;
    do{
        if(lista->distanza<=limit) printf("%d %s \n",lista->distanza,lista->nome);
        else break;
        lista=lista->next;
    }while(lista!=first);
}

int findminlist(listafile_t *lista,char *file){
    int min=INT_MAX;
    listafile_t *first=lista;
    do{
        lista->distanza= Levenshtein_distance(load_file(file),load_file(lista->nome));
        if(lista->distanza<min) min=lista->distanza;
        lista=lista->next;
    }while(lista!=first);
    return min;
}
void printmindistance(listafile_t *lista, int minimo){
    listafile_t *first=lista;
    do{
        if(lista->distanza==minimo) printf("%d %s\n",lista->distanza,lista->nome);
        lista=lista->next;
    }while(lista!=first);
}