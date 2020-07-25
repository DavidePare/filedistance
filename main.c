#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "filedistance.h"
#include "operationfile.h"
#include "utility.h"
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


