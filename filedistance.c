//
// Created by Davide on 27/05/2020.
//

#include "operationfile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filedistance.h"
#include "utility.h"
#include "generatefilem.h"


int Levenshtein_distance(vkey_t *x, vkey_t* y) {
    int distance;
    char *s1, *s2;
    if(x->block==NULL && y->block==NULL) return 0;
    if(x->block==NULL){
        return (int) strlen(generatestring(y))-1;
    }
    if(y->block==NULL){
        return (int) strlen(generatestring(x))-1;
    }
    s1=generatestring(x);
    s2=generatestring(y);
    distance= WagnerFischer_Alg(s1, s2, (int)strlen(s1), (int)strlen(s2));
    free(s1);
    free(s2);
    return distance;
}

/*
 * Da ricontrollare inserimento stringhe vuote modifica apportata 15/06
 */
int Levenshtein_distance_Modify(vkey_t *x,vkey_t *y, char *filesave){
    int distance;
    char *s1, *s2;
    if(x->block==NULL){
        s1=malloc(sizeof(char));
        memset(s1,'\0',sizeof(char));
        printf("%s",s1);
    }else s1=generatestring(x);
    if(y->block==NULL){
        s2=malloc(sizeof(char));
        memset(s2,'\0',sizeof(char));
        printf("%s",s2);
    }else s2=generatestring(y);
    distance= WagnerFischer_Alg_Modify(s1, s2, (int)strlen(s1), (int)strlen(s2),filesave);
    free(s1);
    free(s2);
    return distance;
}



int WagnerFischer_Alg(char *stringA, char *stringB, int m, int n) {
    int **matrix=NULL;
    int lcs;
    matrix=inizializzatematrix(matrix,m,n);
    lcs = lcscreate(matrix,stringA,stringB,m,n);
    clearmatrix(matrix,m);
    return lcs;
}

int WagnerFischer_Alg_Modify(char *stringA, char *stringB, int m, int n, char *filesave) {
    int **matrix=NULL;
    int lcs;
    matrix=inizializzatematrix(matrix,m,n);
    lcs = lcscreate(matrix,stringA,stringB,m,n);
    printActualEdits(matrix, stringA, stringB,((int)strlen(stringA)+1),((int)strlen(stringB)+1),filesave);
    clearmatrix(matrix,m);
    return lcs;
}

void clearmatrix(int **matrix,int m){
    int i;
    for (i = 0; i < m + 2; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int lcscreate(int **matrix, char *stringA, char *stringB , int m , int n){
    int i,j;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {

            if (stringA[i -1] == stringB[j-1]) {
                matrix[i][j] = matrix[i - 1][j - 1];
            } else {
                matrix[i][j] = min(min(matrix[i][j - 1], matrix[i - 1][j - 1]), matrix[i - 1][j]) + 1;
            }
        }
    }
    return matrix[m][n];
}

int** inizializzatematrix(int **matrix,int m,int n) {
    int i;
    matrix = (int **) calloc(m + 2, sizeof(int *));
    for (i = 0; i < m + 2; i++) {
        matrix[i] = (int *) calloc(n + 2, sizeof(int));
    }
    for (i = 0; i <= n; i++) {
        matrix[0][i] = i;
    }
    for (i = 0; i <= m; i++) {
        matrix[i][0] = i;
    }
    return matrix;
}

char *generatestring(vkey_t *x) {
    vblock_t *appuno = x->block;
    char * s1;
    s1= malloc(sizeof(char));
    s1[0]='\0';
    do {
        void *tmp = realloc(s1, strlen(s1) + x->block->size+1);
        if (tmp == NULL) {
            free(s1);
            exit(-1);
        }
        s1 = tmp;
        if (s1[0] == '\0')  strcpy(s1, getblocco(x));
        else strcat(s1, x->block->key);
        x->block = x->block->next;
    } while (appuno != x->block);
    free(x);
    free(appuno);
    return s1;
}


