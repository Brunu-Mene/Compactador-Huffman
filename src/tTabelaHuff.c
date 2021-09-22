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
    int sobraBits = 0;
    //printf("%d-",qtdBitsTxt+qtdBitsArv+3);
    while((qtdBitsTxt+qtdBitsArv+sobraBits+3)%8!=0){
        sobraBits++;
    }
    fclose(arqConta);

    bitmap *bitMap = bitmapInit(qtdBitsArv + qtdBitsTxt + 3);
    int grandeza = 4, aux = 0;
    for(int i=0; i<3 ;i++){
        if(grandeza + aux <= sobraBits){
            aux = aux + grandeza;
            bitmapAppendLeastSignificantBit(bitMap,1);
        }else{
            bitmapAppendLeastSignificantBit(bitMap,0);
        }
        grandeza = grandeza/2;
    }

    geraCodigoArv(arvHuff, bitMap);
    geraCodigoTxt(tabelaHuff, bitMap, arqLe);
    fclose(arqLe);
    
    fwrite(bitmapGetContents(bitMap),sizeof(char)*(((qtdBitsArv+qtdBitsTxt+3)+7)/8),1,arqB);
    fclose(arqB);

    bitmapLibera(bitMap);
}