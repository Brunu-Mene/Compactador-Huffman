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
    return (unsigned char *)calloc('0',sizeof(unsigned char)*tam);
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

unsigned long int tamanhoBinarioTxt(unsigned char **tabelaHuff, FILE *arq){
    unsigned char c;
    int qtdBits = 0;
    while(fscanf(arq,"%c",&c) == 1){
        printf("%s ",tabelaHuff[c]);
        qtdBits = qtdBits + strlen(tabelaHuff[c]);
    }

    return qtdBits;
}

void geraCodigoTxt(unsigned char **tabelaHuff,bitmap *bitMap,FILE *arq){
    unsigned char c;
    while(fscanf(arq,"%c",&c) == 1){
        for(int i=0; i<strlen(tabelaHuff[c]) ;i++){
            if(tabelaHuff[c][i] == '1'){
                bitmapAppendLeastSignificantBit(bitMap,1);
            }else if(tabelaHuff[c][i] == '0'){
                bitmapAppendLeastSignificantBit(bitMap,0);
            }
        }
    }
}

//mudar pra um unico bitmap provavelmente
void geraSaida(unsigned char **tabelaHuff, char *nomeArq, tArvore *arvHuff){
    char adress[50] = "data/";
    strcat(adress,nomeArq);
    FILE *arqConta = fopen(adress,"r");
    FILE *arqLe = fopen(adress,"r");
    adress[strlen(adress)-3] = 'c';
    adress[strlen(adress)-2] = 'o'; 
    adress[strlen(adress)-1] = 'm'; 
    strcat(adress,"p\0");
    FILE *arqB = fopen(adress,"wb");
    if(arqB == NULL){
        printf("Erro na criação do arquivo binário de saida!\n");
        exit(1);
    }

    unsigned long int qtdBitsTxt = tamanhoBinarioTxt(tabelaHuff,arqConta);
    unsigned long int qtdBitsArv = tamanhoBinarioArv(arvHuff,0);
    printf("\n%ld - %ld\n",qtdBitsTxt,qtdBitsArv);
    fclose(arqConta);

    bitmap *bitMap = bitmapInit(qtdBitsArv + qtdBitsTxt);
    //bitmap *bitMapArv = bitmapInit(qtdBitsArv);
    //bitmap *bitMapText = bitmapInit(qtdBitsTxt);
    //geraCodigoArv(arvHuff, bitMapArv);
    //geraCodigoTxt(tabelaHuff, bitMapText, arqLe);
    geraCodigoArv(arvHuff, bitMap);
    geraCodigoTxt(tabelaHuff, bitMap, arqLe);
    fclose(arqLe);
    
    //fwrite(bitmapGetContents(bitMapArv),sizeof(char)*((qtdBitsArv+7)/8),1,arqB);
    //fwrite(bitmapGetContents(bitMapText),sizeof(char)*((qtdBitsTxt+7)/8),1,arqB);
    fwrite(bitmapGetContents(bitMap),sizeof(char)*(((qtdBitsArv+qtdBitsTxt)+7)/8),1,arqB);
    fclose(arqB);
    //bitmapLibera(bitMapArv);
    //bitmapLibera(bitMapText);
    bitmapLibera(bitMap);
}