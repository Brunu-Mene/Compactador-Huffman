#include "../include/tDescompacta.h"

unsigned int qtdByteArq(char *nomeArq){
    char adress[50] = "data/";
    strcat(adress,nomeArq);
    FILE *arq = fopen(adress,"rb");
    if(arq == NULL){
        printf("Arquivo binario nao encontrado!");
        exit(1);
    }
    unsigned char *byte = malloc(sizeof(unsigned char));
    unsigned int qtdBytes = 0;
    while(fread(byte,sizeof(unsigned char),1,arq) == 1){
        qtdBytes++;
    }
    free(byte);
    fclose(arq);

    return qtdBytes;
}

void recontroiBits(int byte,char *bits){
    int grandeza = 128, num = 0;
    for(int j=0; j<8 ;j++){
            if((num + grandeza) <= byte){
                num = num + grandeza;
                bits[j] = '1';
            }else{
                bits[j] = '0';
            }
        grandeza = grandeza/2;
    }
}

void preencheBitMap(bitmap *bitMap,char *nomeArq){
    char adress[50] = "data/";
    strcat(adress,nomeArq);
    FILE *arq = fopen(adress,"rb");
    char *bits = malloc(sizeof(char)*8);
    unsigned char *byte = malloc(sizeof(unsigned char));
    while(fread(byte,sizeof(unsigned char),1,arq) == 1){
        recontroiBits(*byte,bits);
        for(int i=0; i<8; i++){
            if(bits[i] == '1'){
                bitmapAppendLeastSignificantBit(bitMap,1);
            }else if(bits[i] == '0'){
                bitmapAppendLeastSignificantBit(bitMap,0);
            }
        }
    }
    free(byte);
    free(bits);
    fclose(arq);
}

void decodificaTexto(tArvore *arv,bitmap *bitMap, char *nomeArq){
    char adress[50] = "data/New";
    nomeArq[strlen(nomeArq)-2] = 't';
    nomeArq[strlen(nomeArq)-3] = 'x';
    nomeArq[strlen(nomeArq)-4] = 't';
    nomeArq[strlen(nomeArq)-1] = '\0';
    strcat(adress,nomeArq);
    FILE *arq = fopen(adress,"w");
    if(arq == NULL){
        printf("Erro na criação doa rquivo decodificado!\n");
        exit(1);
    }
    int sobraBits = 0, grandeza = 4;
    for(int i=0; i<3 ;i++){
        if(bitmapGetBit(bitMap,i) == 1){
            sobraBits = sobraBits + grandeza;
        }
        grandeza = grandeza/2;
    }
    //printf("%d",bitmapGetLength(bitMap));
    recriaTexto(arv,bitMap,tamanhoBinarioArv(arv,0) + 3, sobraBits,arq);
    fclose(arq);
}