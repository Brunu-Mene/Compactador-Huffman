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

void recontroiBits(int byte,char *bits){
    int grandeza = 128, num = 0;
    for(int j=7; j>=0 ;j--){
            if((num + grandeza) <= byte){
                num = num + grandeza;
                bits[j] = '1';
            }else{
                bits[j] = '0';
            }
        grandeza = grandeza/2;
    }
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

void geraSaida(unsigned char **tabelaHuff, char *nomeArq, tArvore *arvHuff){
    char adress[50] = "data/";
    strcat(adress,nomeArq);
    FILE *arqConta = fopen(adress,"r");
    FILE *arqLe = fopen(adress,"r");
    if(arqConta == NULL){
        printf("Arquivo não encontrado!\n");
        exit(1);
    }
    unsigned long int qtdBitsTxt = tamanhoBinarioTxt(tabelaHuff,arqConta);
    unsigned long int qtdBitsArv = tamanhoBinarioArv(arvHuff,0);
    printf("\n%ld - %ld\n",qtdBitsTxt,qtdBitsArv);
    fclose(arqConta);

    adress[strlen(adress)-3] = 'c';
    adress[strlen(adress)-2] = 'o'; 
    adress[strlen(adress)-1] = 'm'; 
    strcat(adress,"p\0");
    FILE *arqB = fopen(adress,"wb");
    if(arqB == NULL){
        printf("Erro na criação do arquivo binário de saida!\n");
        exit(1);
    }
    bitmap *bitMapArv = bitmapInit(qtdBitsArv);
    bitmap *bitMapText = bitmapInit(qtdBitsTxt);
    geraCodigoArv(arvHuff, bitMapArv);
    geraCodigoTxt(tabelaHuff, bitMapText, arqLe);
    fclose(arqLe);
    
    fwrite(bitmapGetContents(bitMapArv),sizeof(char)*((qtdBitsArv+7)/8),1,arqB);
    fwrite(bitmapGetContents(bitMapText),sizeof(char)*((qtdBitsTxt+7)/8),1,arqB);
    fclose(arqB);
    bitmapLibera(bitMapArv);
    bitmapLibera(bitMapText);

    /*TESTANDO MONTAR A ARVORE A PARTIR DO ARQUIVO BINARIO GERADO AQUI SO DE MEME XDXDXDXD
    unsigned char *bytes = malloc(sizeof(char)*13);
    FILE *arqKK = fopen("data/test.comp","rb");
    fread(bytes,sizeof(char),13,arqKK);
    fclose(arqKK);
    unsigned char *bitsArvores = malloc((sizeof(char)*13*8)+1);
    for(int i=0; i<13 ;i++){
        recontroiBits(bytes[i],&bitsArvores[i*8]);
    }
    bitsArvores[(13*8)] = '\0';
    printf("%s\n",bitsArvores);
    tArvore *MEME = recriaArvore2(MEME,bitsArvores);
    imprimeArv(MEME);
    free(bytes);
    free(bitsArvores);
    liberaArvore(MEME);*/
    //tArvore *arvRecriada = 
}