#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "filedistance.h"
#include "operationfile.h"
#include "filepath.h"
#include "utility.h"
void searchfunction(char *file, char *path);
void searchallfunction(char *filedist,char *path,int limit);
void distancefunction(char *fileA , char *fileB ,char *fileM, int paramaterNumber);
int main(int argc, char **argv) {
    if((strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")==0) && argc==2) {
        menuCommand();
        return 0;
    }
    if(strcmp(argv[1],"distance")==0){
        distancefunction(argv[2],argv[3],argv[4],argc);
        return 0;
    }
    if(strcmp(argv[1], "apply")==0 && argc==5){
        apply(load_file(argv[2]),argv[3],argv[4]);
        return 0;
    }
    if(strcmp(argv[1], "search")==0 && argc==4){
        searchfunction(argv[2],argv[3]);
        return 0;
    }
    if(strcmp(argv[1], "searchall")==0 && argc==5){
        searchallfunction(argv[2],argv[3],atoi(argv[4]));
        return 0;
    }
    printf("See instruction with command -h");

    return 0;
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
    free(lista);
}

void searchfunction(char *file, char *path){
    listafile_t *lista=malloc(sizeof(listafile_t));
    lista->nome=NULL;
    lista=fileindir(lista,path);
    int minimo=findminlist(lista,file);
    printmindistance(lista,minimo);
    free(lista);
}