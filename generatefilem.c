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
    FILE *fp;
    fp= fopen(filesave, "wt");
    if(fp == NULL)  exit(1);
    while(i != 0 || j != 0) {
        if(i==0 || j==0) finishAString(app,str1,str2,&i,&j,fp);

        else{
            if (str1[i - 1] == str2[j - 1]) {
                i--;
                j--;
            } else{
                if (matrix[i][j] == matrix[i - 1][j - 1] + 1) {
                    impostadati(app, 0, str2[j - 1], i - 1,&i,&j);
                }
                else if (matrix[i][j] == matrix[i - 1][j] + 1) {
                    impostadati(app, 1, ' ', i - 1,&i,&j);
                } else if (matrix[i][j] == matrix[i][j - 1] + 1) {
                    impostadati(app, 2, str2[j - 1], i, &i, &j);
                }
                saveappintofile(fp, app);
            }
        }
    }
}

void impostadati(vOption_t *app, int opzione, char carattere, int posizione, int *i,int *j){
    switch(opzione){
        case 0:
            memcpy(app->istruction,"SET\0",4);
            app->imposta= (unsigned char) carattere;
            app->posizione=posizione;
            (*i)--;
            (*j)--;
            break;
        case 1:
            memcpy(app->istruction,"DEL\0",4);
            app->imposta= 32;
            app->posizione=posizione;
            (*i)--;
            break;
        case 2:
            memcpy(app->istruction,"ADD\0",4);
            app->imposta= (unsigned char) carattere;
            app->posizione=posizione;
            (*j)--;
            break;
        default:
            break;
    }
}


void finishAString(vOption_t *app, char *str1, char *str2, int *i, int *j, FILE *fp) {
    if(*i==0){
        endStringA(app,str1,str2,i,j,fp);
    }
    if(*j==0){
        endStringB(app,str1,str2,i,j,fp);
    }
}

void endStringA(vOption_t *app, char *strA, char *strB, int *i,int *j,FILE *fp){
    while(*j>0) {

        memcpy(app->istruction,"ADD\0",4);
        app->imposta= strB[*j-1];
        app->posizione= *i;
        (*j)--;
        saveappintofile(fp,app);
    }
}
void endStringB(vOption_t *app, char *strA, char *strB, int *i,int *j, FILE *fp){
    while(*i>0) {

        memcpy(app->istruction,"DEL\0",4);
        app->imposta= 32;
        app->posizione=*i-1;
        (*i)--;
        saveappintofile(fp,app);
    }
}
void saveappintofile(FILE *fp, vOption_t *app){
    fprintf(fp, "%03s%010u%hhu\n", app->istruction, app->posizione, app->imposta);
}