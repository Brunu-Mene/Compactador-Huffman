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
        if(tabelaHuff[i]!=NULL)
            free(tabelaHuff[i]);
    }
    free(tabelaHuff);
}

void geraSaida(char **tabelaHuff, char *nomeArq){
    char adress[50] = "data/";
    char c;
    strcat(adress,nomeArq);
    FILE *arq = fopen(adress,"r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        exit(1);
    }
    while(fscanf(arq,"%c",&c) == 1){
        printf("%s ",tabelaHuff[c]);
    }
    printf("\n");

    fclose(arq);
}