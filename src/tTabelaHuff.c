#include "../include/tTabelaHuff.h"
#include "../include/tBitmap.h"

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

void geraSaida(unsigned char **tabelaHuff, char *nomeArq, tArvore *arvHuff){
    char adress[50] = "data/";
    unsigned char c;
    strcat(adress,nomeArq);
    FILE *arqT = fopen(adress,"r");
    if(arqT == NULL){
        printf("Arquivo não encontrado!\n");
        exit(1);
    }
    adress[strlen(adress)-3] = 'c';
    adress[strlen(adress)-2] = 'o';
    adress[strlen(adress)-1] = 'm';
    strcat(adress,"p\0");
    FILE *arqB = fopen(adress,"wb");
    if(arqB == NULL){
        printf("Erro na criação do arquivo binário de saida!\n");
        exit(1);
    }
    geraCodigoArv(arvHuff,arqB);
    fclose(arqB);
    imprimeArv(arvHuff);
    printf("\n");
    FILE *arqBT = fopen("data/test.comp","r");
    tArvore *newArv = recriaArvore(newArv,arqBT);
    imprimeArv(newArv);
    printf("\n");
    liberaArvore(newArv);
    fclose(arqBT);

    /*char *MEME = calloc('0',sizeof(char)*500);
    int i=0;
    while(fscanf(arqT,"%c",&c) == 1){
        int j=0;
        printf("%s",tabelaHuff[c]);
        /*if(strlen(tabelaHuff[c])%8!=0){
            fwrite(tabelaHuff[c],(strlen(tabelaHuff[c])/8)+1,strlen(tabelaHuff[c]),arqB);
        }else{
            fwrite(tabelaHuff[c],strlen(tabelaHuff[c])/8,strlen(tabelaHuff[c]),arqB);
        }
        //strcat(MEME,tabelaHuff[c]);
        while(j<strlen(tabelaHuff[c])){
            MEME[i] = tabelaHuff[c][j];
            j++;
            i++;
        }
    }
    MEME[i+1] = '\0';
    printf("\n");
    printf("%s\n",MEME);
    if(strlen(MEME)%8!=0){
        fwrite(MEME,sizeof(char),1,arqB);
    }else{
        fwrite(MEME,(strlen(MEME)/8),strlen(MEME),arqB);
    }

    free(MEME);*/

    fclose(arqT);
    //fclose(arqB);
}


//funções implementadas com sucesso!!
/*void geraCodigoArv(tAvore *arv, FILE *arqB){
    if(arv == NULL) return;
    if(arv->esq!=NULL || arv->dir!=NULL){
        printa bit 0;
        geraCodigoArv(arv->esq,arqB);
        geraCodigoArv(arv->dir,arqB);
    }else{
        printa bit 1;
        printa 8 bits(ou 1 byte) do caracter da folha
    }
}*/
//funçao pai printa bit 1

/*tArvore *recriaArvore(tArvore *arv, FILE *arqB){
    //bit = ler bit do arquivo;
    arv = (tAvore *)malloc(sizeof(tArvore));
    if(bit == 0){
        arv->esq = recriaArvore(arv->esq,arqB);
        arv->dir = recriaArvore(arv->dir,arqB);
    }else{
        c = leio 8 bits na seqeucia
        arv->c = c;
        arv->esq = NULL;
        arv->dir = NULL;
    }
    return arv;
}*/