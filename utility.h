//
// Created by root on 24/06/20.
//

#ifndef FILEDISTANCE_UTILITY_H
#define FILEDISTANCE_UTILITY_H
#include "filepath.h"
#include "filedistance.h"
void menuCommand();
int min(int x, int y);
void swap(listafile_t *x,listafile_t *y);
void orderlist(listafile_t *first);
int max(int x, int y);

void searchfunction(char *file, char *path);
void searchallfunction(char *filedist,char *path,int limit);
void distancefunction(char *fileA , char *fileB ,char *fileM, int paramaterNumber);
#endif //FILEDISTANCE_UTILITY_H
