#include "../include/tTabelaHuff.h"

unsigned char **inicializaTabela(){
    unsigned char **tabelaHuff = (unsigned char **)malloc(257*sizeof(unsigned char *));
    for(int i=0; i<257 ;i++){
        tabelaHuff[i] = NULL;
    }
    return tabelaHuff;
}

unsigned char *inicializaString(int tam){
    return (unsigned char *)malloc(sizeof(unsigned char)*tam);
}

void liberaString(unsigned char *string){
    free(string);
}

void liberaTabela(unsigned char **tabelaHuff){
    for(int i=0; i<257 ;i++){
        if(tabelaHuff[i]!=NULL)
            free(tabelaHuff[i]);
    }
    free(tabelaHuff);
}

void geraSaida(unsigned char **tabelaHuff, char *nomeArq){
    char adress[50] = "data/";
    unsigned char c;
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