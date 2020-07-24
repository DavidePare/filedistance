//
// Created by root on 12/07/20.
//

#ifndef FILEDISTANCE_GENERATEFILEM_H
#define FILEDISTANCE_GENERATEFILEM_H
#include "filedistance.h"
void printActualEdits(int **matrix, char *str1, char *str2,int i , int j,char * filesave);
void impostadati(vOption_t *app, int opzione, char carattere, int posizione, int *i,int *j);
void saveappintofile(FILE *fp, vOption_t *app);
void finishAString(vOption_t *app, char *str1, char *str2, int *i, int *j, FILE *fp);
void endStringA(vOption_t *app, char *strB, int *i,int *j,FILE *fp);
void endStringB(vOption_t *app,int *i,int *j,FILE *fp);

void writeSetIntoFile(vOption_t *app, char carattere, int posizione, int **i,int **j);
void writeDelIntoFile(vOption_t *app, char carattere, int posizione, int **i,int **j);
void writeAddIntoFile(vOption_t *app, char carattere, int posizione, int **i,int **j);
void calculateInternalMatrix(int **matrix,vOption_t *app, char *str1, char *str2, int *i,int *j,FILE *fp);
#endif //FILEDISTANCE_GENERATEFILEM_H
