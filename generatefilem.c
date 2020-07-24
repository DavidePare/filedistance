//
// Created by root on 12/07/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generatefilem.h"
void printActualEdits(int **matrix, char *str1, char *str2,int i, int j,char * filesave) {
    vOption_t *app;
    app = malloc(sizeof(vOption_t));
    if(app== NULL)  exit(1);
    app->istruction=malloc(sizeof(char)*4);
    if(app->istruction == NULL) exit(1);
    FILE *fp;
    fp= fopen(filesave, "wt");
    if(fp == NULL)  exit(1);
    while(i != 0 || j != 0) {
        if(i==0 || j==0) finishAString(app,str1,str2,&i,&j,fp);
        else{
            calculateInternalMatrix(matrix,app,str1,str2,&i,&j,fp);
            }
    }
    fclose(fp);
}


void calculateInternalMatrix(int **matrix,vOption_t *app, char *str1, char *str2, int *i,int *j,FILE *fp){
    if (str1[*i - 1] == str2[*j - 1]) {
        (*i)--;
        (*j)--;
    } else {
        if (matrix[*i][*j] == matrix[*i - 1][*j - 1] + 1) {
            writeSetIntoFile(app, str2[*j - 1], *i - 1, &i, &j);
        } else if (matrix[*i][*j] == matrix[*i - 1][*j] + 1) {
            writeDelIntoFile(app, 32, *i - 1, &i, &j);
        } else if (matrix[*i][*j] == matrix[*i][*j - 1] + 1) {
            writeAddIntoFile(app, str2[*j - 1], *i, &i, &j);
        }
        saveappintofile(fp, app);
    }
}


void writeSetIntoFile(vOption_t *app, char carattere, int posizione, int **i,int **j){
    memcpy(app->istruction,"SET\0",4);
    app->imposta= (unsigned char) carattere;
    app->posizione=posizione;
    (**i)--;
    (**j)--;
}
void writeDelIntoFile(vOption_t *app, char carattere, int posizione, int **i,int **j){
    memcpy(app->istruction,"DEL\0",4);
    app->imposta= (unsigned char) carattere;
    app->posizione=posizione;
    (**i)--;
}
void writeAddIntoFile(vOption_t *app, char carattere, int posizione, int **i,int **j){
    memcpy(app->istruction,"ADD\0",4);
    app->imposta= (unsigned char) carattere;
    app->posizione=posizione;
    (**j)--;
}

void finishAString(vOption_t *app, char *str1, char *str2, int *i, int *j, FILE *fp) {
    if(*i==0){
        endStringA(app,str2,i,j,fp);
    }
    if(*j==0){
        endStringB(app,i,j,fp);
    }
}

void endStringA(vOption_t *app, char *strB, int *i,int *j,FILE *fp){
    while(*j>0) {
        writeAddIntoFile(app,strB[*j-1],*i,&i,&j);
        saveappintofile(fp,app);
    }
}
void endStringB(vOption_t *app, int *i,int *j, FILE *fp){
    while(*i>0) {
        writeDelIntoFile(app,32,(*i-1),&i,&j);
        saveappintofile(fp,app);
    }
}
void saveappintofile(FILE *fp, vOption_t *app){
    fprintf(fp, "%03s%010u%hhu\n", app->istruction, app->posizione, app->imposta);
}