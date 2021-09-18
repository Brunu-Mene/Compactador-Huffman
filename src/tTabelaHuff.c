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
    bitmap *bitMap = bitmapInit(tamanhoBinarioArv(arvHuff,0));
    geraCodigoArv(arvHuff, bitMap);
    //pode apagar provavelmente ****
    /*int tam = tamanhoCodArv(arvHuff,0);
    unsigned char *codArv = inicializaString(tam+1);
    codArv[tam] = '\0';
    geraCodigoArv(arvHuff,codArv);
    for(int i=0; i<tam ;i++){
        if(codArv[i] == '1'){
            bitmapAppendLeastSignificantBit(bitMap,1);
        }else if(codArv[i] == '0'){
            bitmapAppendLeastSignificantBit(bitMap,0);
        }else if(codArv[i] != '\0'){
            int num = 0, grandeza = 128;
            for(int j=0; j<8 ;j++){
                if((num + grandeza) <= codArv[i]){
                    num = num + grandeza;
                    bitmapAppendLeastSignificantBit(bitMap,1);
                }else{
                    bitmapAppendLeastSignificantBit(bitMap,0);
                }
                grandeza = grandeza/2;
            }
        }
    }
    liberaString(codArv);*/
    fwrite(bitmapGetContents(bitMap),sizeof(char)*((bitmapGetLength(bitMap)+7)/8),1,arqB);
    fclose(arqB);
    bitmapLibera(bitMap);

    /*TESTANDO MONTAR A ARVORE A PARTIR DO ARQUIVO BINARIO GERADO AQUI SO DE MEME XDXDXDXD*/
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
    liberaArvore(MEME);
    //tArvore *arvRecriada = 


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