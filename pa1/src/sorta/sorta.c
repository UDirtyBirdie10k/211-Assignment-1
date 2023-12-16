#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int compareString(const void* a, const void* b){
    return strcmp(*(const char**) a, *(const char**) b);
}

int main(int argc, char* argv[]) {

    if(argc == 1){

        return 0; 
    }

    qsort(argv + 1, argc - 1, sizeof(char*), compareString);

    for(int i = 1; i < argc; i++){

        printf("%s\n", argv[i]);

    }

    return 0;
}