//
// Created by Davide on 14/05/2020.
//

#ifndef FILEDISTANCE_FILEDISTANCE_H
#define FILEDISTANCE_FILEDISTANCE_H
#include "operationfile.h"
#include "applymodify.h"
typedef unsigned char byte; // 0 - 255 1 BYTE
typedef struct vOption{
    char *istruction;
    unsigned int posizione;         //4 BYTE
    byte imposta;               // cosi abbiamo una variabile che assume valori da 0 a 255 --> 8 bit -> 1 byte
}vOption_t;
int Levenshtein_distance(vkey_t *x,vkey_t *y);

void clearmatrix(int **matrix,int m);
int** inizializzatematrix(int **matrix,int m,int n);
int WagnerFischer_Alg(char *stringA, char *stringB, int m, int n);
int lcscreate(int **matrix,char *stringA,char *stringB , int m , int n);
int Levenshtein_distance_Modify(vkey_t *x,vkey_t *y, char *filesave);

int WagnerFischer_Alg_Modify(char *stringA, char *stringB, int m, int n,char *filesave);
char *generatestring(vkey_t *x);
#endif //FILEDISTANCE_FILEDISTANCE_H
