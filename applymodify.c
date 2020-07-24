//
// Created by root on 15/06/20.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "applymodify.h"
char *deloperation(char *stringAppoggio,char *stringOriginaria,vOption_t *app);
char *addoperation(char *stringAppoggio, char *stringOriginaria, vOption_t *app);
char *applyoperation(FILE *fp, char *stringOriginaria,char *stringAppoggio, vOption_t *app);

void apply(vkey_t* x, char *filem, char *resultm){
    char *stringOriginaria;
    char *stringAppoggio;
    stringOriginaria=generateStringOriginaria(x);
    FILE *fp;
    fp= fopen(filem,"r");
    if(fp== NULL) exit(0);
    vOption_t *app=malloc(sizeof(vOption_t));
    stringAppoggio = malloc(strlen(stringOriginaria)+1);
    stringOriginaria=applyoperation(fp,stringOriginaria,stringAppoggio,app);
    stringOriginaria[strlen(stringOriginaria)]='\0';
    fclose(fp);
    saveintofile(stringOriginaria,resultm);
    free(stringOriginaria);
}
char *applyoperation(FILE *fp, char *stringOriginaria,char *stringAppoggio, vOption_t *app){
    while(!feof(fp)) {
        fscanf(fp,"%03s%10u%hhu\n", app->istruction, &app->posizione, &app->imposta);
        if(app->posizione>strlen(stringOriginaria)){
            app->posizione=strlen(stringOriginaria)-1;
        }
        if(strcmp(app->istruction,"DEL") ==0) {
            if(strlen(stringOriginaria)==0) continue ;
            char *p=realloc(stringAppoggio,sizeof(char)*strlen(stringOriginaria)+1);
            if(!p) exit(0);
            else stringAppoggio=p;
            stringOriginaria=deloperation(stringAppoggio,stringOriginaria,app);
        }
        else if(strcmp(app->istruction,"ADD") ==0){
            stringAppoggio=realloc(stringAppoggio,sizeof(char)*strlen(stringOriginaria)+3);
            stringOriginaria=addoperation(stringAppoggio,stringOriginaria,app);
        }
        else if(strcmp(app->istruction,"SET")==0){
            stringOriginaria[app->posizione]=(char)app->imposta;
        }
    }
    free(stringAppoggio);
    return stringOriginaria;
}
char *deloperation(char *stringAppoggio,char *stringOriginaria,vOption_t *app){

    char *p=realloc(stringOriginaria,sizeof(char)*strlen(stringOriginaria)+1);
    if(!p) exit(0);
    stringOriginaria=p;
    strncpy(stringAppoggio,stringOriginaria,app->posizione);
    stringAppoggio[app->posizione]='\0';
    strncat(stringAppoggio, stringOriginaria + app->posizione+1 , strlen(stringOriginaria));
    strncpy(stringOriginaria,stringAppoggio,strlen(stringAppoggio));
    stringOriginaria[strlen(stringAppoggio)]='\0';
    memset(stringAppoggio,'\0',strlen(stringAppoggio));
    return stringOriginaria;
}
char *addoperation(char * stringAppoggio, char *stringOriginaria, vOption_t *app){
    char *p=realloc(stringOriginaria, sizeof(char)*strlen(stringOriginaria)+3);
    if(p==NULL) exit(0);
    stringOriginaria=p;
    strncpy(stringAppoggio,stringOriginaria,app->posizione);
    stringAppoggio[app->posizione]= app->imposta;
    stringAppoggio[app->posizione+1]='\0';
    strncat(stringAppoggio, stringOriginaria + app->posizione , (int) strlen(stringOriginaria));
    strcpy(stringOriginaria, stringAppoggio);
    stringOriginaria[strlen(stringOriginaria)+1]='\0';
    memset(stringAppoggio,'\0',strlen(stringAppoggio));
    return stringOriginaria;
}
char *generateStringOriginaria(vkey_t *x){
    char *stringOriginaria;
    if(x->block!= NULL) stringOriginaria=generatestring(x);
    else {
        stringOriginaria=malloc(sizeof(char));
        memset(stringOriginaria,'\0',sizeof(char));
    }
    return stringOriginaria;
}