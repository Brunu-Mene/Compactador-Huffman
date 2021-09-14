#include "../include/tTabelaHuff.h"

char **inicializaTabela(){
    char **tabelaHuff = (char **)malloc(256*sizeof(char *));
    for(int i=0; i<256 ;i++){
        tabelaHuff[i] = NULL;
    }
    return tabelaHuff;
}

char *inicializaString(int tam){
    return (char *)malloc(sizeof(char)*tam);
}

void liberaString(char *string){
    free(string);
}

void liberaTabela(char **tabelaHuff){
    for(int i=0; i<256 ;i++){
        free(tabelaHuff[i]);
    }
    free(tabelaHuff);
}