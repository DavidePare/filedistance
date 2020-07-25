//
// Created by root on 24/06/20.
//
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void dealloclistname(listafile_t *lista);
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

void distancefunction(char *fileA , char *fileB ,char *fileM, int paramaterNumber){
    int distance=0;
    clock_t begin = clock();
    if(paramaterNumber==4){
        distance= Levenshtein_distance(load_file(fileA),load_file(fileB));
    }
    if(paramaterNumber==5){
        distance=Levenshtein_distance_Modify(load_file(fileA),load_file(fileB),fileM);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("EDIT DISTANCE: %d \nTIME: %lf \n",distance,time_spent);
}

void searchallfunction(char *filedist,char *path,int limit){
    listafile_t *lista=malloc(sizeof(listafile_t));
    lista->nome =NULL;
    lista=fileindir(lista,path); // if argv[4] is a character or string it would be NULL and it will considereted 0
    calculatedistancelist(lista,filedist);
    orderlist(lista);
    printlimitdistance(lista,limit);
    dealloclistname(lista);
}

void searchfunction(char *file, char *path){
    listafile_t *lista=malloc(sizeof(listafile_t));
    lista->nome=NULL;
    lista=fileindir(lista,path);
    int minimo=findminlist(lista,file);
    printmindistance(lista,minimo);
    dealloclistname(lista);
}

void dealloclistname(listafile_t *lista){
    listafile_t *primo=lista;
    lista=lista->next;
    listafile_t *appoggio;
    do{
        appoggio=lista->next;
        free(lista);
        lista=appoggio;

    }while(lista->next != primo);
    free(primo);

}
