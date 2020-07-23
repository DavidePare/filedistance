//
// Created by Davide on 14/05/2020.
//

#ifndef FILEDISTANCE_FILEPATH_H
#define FILEDISTANCE_FILEPATH_H
typedef struct listafile{
    char *nome;
    int distanza;
    struct listafile *next;
}listafile_t;
listafile_t* fileindir(listafile_t *file,char * directory);
void calculatedistancelist(listafile_t *lista, char *file);
void printlimitdistance(listafile_t *lista, int limit);
int findminlist(listafile_t *lista, char *file);
void printmindistance(listafile_t *lista, int minimo);
#endif //FILEDISTANCE_FILEPATH_H
