//
// Created by Davide on 14/05/2020.
//

#ifndef FILEDISTANCE_OPERATIONFILE_H
#define FILEDISTANCE_OPERATIONFILE_H
typedef struct vblock {
    char key[256];
    int size;
    struct vblock *next;
}vblock_t;
typedef struct vkey {
    vblock_t *block;
}vkey_t;

char* getblocco(vkey_t* key);
void add_block(char* content, vblock_t **first, vblock_t **last);
vkey_t* load_file(char* file);
void saveintofile(char * s, char *file);


#endif //FILEDISTANCE_OPERATIONFILE_H
