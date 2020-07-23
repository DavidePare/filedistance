//
// Created by root on 24/06/20.
//
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int min(int x,int y){
    if(x>y) return y;
    else return x;
}

void menuCommand(){
    printf("Different Features: \n");
    printf("   -h or --help command to see al command \n");
    printf("   -v or --version command to see the version of software \n");
    printf("   filedistance distance file1 file2, distance is how u must pass \n");
    printf("   filedistance apply inputfile filem outputfile , inputfile is the file where u apply the filem that contains the different options and save result in outputfile \n");
    printf("   filedistance search inputfile dir \n");
    printf("   filedistance searchall inputfile dir limit \n");
}

void orderlist(listafile_t *first){
    listafile_t* list=first;
    listafile_t* lptr=NULL;
    int swapped;
    do{
        swapped=0;
        list=first;
        while(list->next!= first){
            if(list->distanza > list->next->distanza){
                swap(list,list->next);
                swapped=1;
            }
            list=list->next;
        }
        lptr = list;
    }while(swapped);
}
void swap(listafile_t *x,listafile_t *y){
    listafile_t *appoggio=malloc(sizeof(listafile_t));
    appoggio->nome=malloc(sizeof(char)*strlen(x->nome)+3);
    strcpy(appoggio->nome,x->nome);
    appoggio->distanza=x->distanza;
    x->nome=realloc(x->nome,sizeof(char)*strlen(y->nome)+1);
    strcpy(x->nome,y->nome);
    x->distanza=y->distanza;
    y->nome=realloc(y->nome,sizeof(char)*strlen(appoggio->nome)+1);
    strcpy(y->nome,appoggio->nome);
    y->distanza=appoggio->distanza;
    free(appoggio);
}


int max(int x, int y){
    if(x>y) return x;
    return y;
}


