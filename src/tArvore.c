#include "../include/tArvore.h"
#include "../include/tTabelaHuff.h"

struct Arvore{
    tArvore *esq;
    tArvore *dir;
    unsigned char c;
    int qtd;
};

tArvore *inicializaArv(unsigned char c, int qtd){
    tArvore *arv = (tArvore *) malloc(sizeof(tArvore));
    arv->esq = NULL;
    arv->dir = NULL;
    arv->c = c;
    arv->qtd = qtd;

    return arv;
}

tArvore *inicializaArvVazia(){
    tArvore *arv = (tArvore *) malloc(sizeof(tArvore));
    arv->esq = NULL;
    arv->dir = NULL;
    
    return arv;
}

static int maior(int a, int b){
    if(a > b) return a;

    return b;
}

int altura(tArvore *arv){
    if(arv == NULL) return -1;

    return 1 + maior(altura(arv->esq),altura(arv->dir));
}

tArvore *preencheArvore(tArvore *arv,tArvore *esq, tArvore *dir, int qtd){
    arv->dir = dir;
    arv->esq = esq;
    arv->qtd = qtd;

    return arv;
}

unsigned char retornaCaracter(tArvore *arv){
    return arv->c;
}
int retornaQtd(tArvore *arv){
    return arv->qtd;
}

void liberaArvore(tArvore *arv){
    if(arv == NULL) return;

    liberaArvore(arv->esq);
    liberaArvore(arv->dir);

    free(arv);
}

void preencheTabela(unsigned char **tabela, tArvore *arvHuff,unsigned char *cod, int id){
    if(arvHuff == NULL) return;
    else if(arvHuff->esq == NULL && arvHuff->dir == NULL){
        tabela[arvHuff->c] = inicializaString(id+1);
        for(int i=0; i<id ;i++){
            tabela[arvHuff->c][i] = cod[i];
        }
        tabela[arvHuff->c][id] = '\0';
    }else{
        cod[id] = '0';
        preencheTabela(tabela,arvHuff->esq,cod,id+1);
        cod[id] = '1';
        preencheTabela(tabela,arvHuff->dir,cod,id+1);
    }
}

unsigned long int tamanhoBinarioArv(tArvore *arv, int tam){
    if(arv == NULL) return 0;
    if(arv->esq!=NULL && arv->dir!=NULL){
        tam = tam + tamanhoBinarioArv(arv->esq,1);
        tam = tam + tamanhoBinarioArv(arv->dir,0);
        return tam;
    }else{
        tam = tam + tamanhoBinarioArv(arv->esq,0);
        tam = tam + tamanhoBinarioArv(arv->dir,0);
        return tam+9;
    }
}
/*int tamanhoCodArv(tArvore *arv, int tam){
    if(arv == NULL) return 0;
    if(arv->esq!=NULL && arv->dir!=NULL){
        tam = tam + tamanhoCodArv(arv->esq,1);
        tam = tam + tamanhoCodArv(arv->dir,0);
        return tam;
    }else{
        return tam+2;
    }
}*/

/*void geraCodigoArv(tArvore *arv, unsigned char *cod){
    if(arv == NULL) return;
    if(arv->esq!=NULL || arv->dir!=NULL){
        strcat(cod,"0");
        //
        //fprintf(arqB,"0");
        geraCodigoArv(arv->esq,cod);
        geraCodigoArv(arv->dir,cod);
    }else{
        unsigned char aux[2];
        aux[0] = '1';
        aux[1] = arv->c;
        strcat(cod,aux);
        //
        //fprintf(arqB,"1%c",arv->c);
        //printa 8 bits(ou 1 byte) do caracter da folha
    }
}*/

void geraCodigoArv(tArvore *arv, bitmap *bitMap){
    if(arv == NULL) return;
    if(arv->esq!=NULL || arv->dir!=NULL){
        bitmapAppendLeastSignificantBit(bitMap,0);
        geraCodigoArv(arv->esq,bitMap);
        geraCodigoArv(arv->dir,bitMap);
    }else{
        bitmapAppendLeastSignificantBit(bitMap,1);
        int grandeza = 128, num = 0;
        for(int j=0; j<8 ;j++){
                if((num + grandeza) <= arv->c){
                    num = num + grandeza;
                    bitmapAppendLeastSignificantBit(bitMap,1);
                }else{
                    bitmapAppendLeastSignificantBit(bitMap,0);
                }
            grandeza = grandeza/2;
        }
    }
}

tArvore *recriaArvore(tArvore *arv, FILE *arqB){
    char bit = '\0';
    fscanf(arqB,"%c",&bit);
    arv = (tArvore *)malloc(sizeof(tArvore));
    if(bit == '0'){
        arv->esq = recriaArvore(arv->esq,arqB);
        arv->dir = recriaArvore(arv->dir,arqB);
    }else if(bit == '1'){
        char c;
        fscanf(arqB,"%c",&c);
        arv->c = c;
        arv->esq = NULL;
        arv->dir = NULL;
    }
    return arv;
}
int reconstroiChar(char *byte){
    int valor = 0, grandeza = 128;
    for(int i=7; i>=0; i--){
        if(byte[i] == 1){
            valor = valor+grandeza;
        }
        grandeza = grandeza/2;
    }
    return valor;
}
//infuncional, pensar como fazer dps
tArvore *recriaArvore2(tArvore *arv, char *bits){
    printf("%s\n",bits);
    arv = (tArvore *)malloc(sizeof(tArvore));
    if(bits[0] == '0'){
        arv->esq = recriaArvore2(arv->esq,bits+1);
        arv->dir = recriaArvore2(arv->dir,bits+1);
    }else if(bits[0] == '1'){//
        //printf("%d\n",reconstroiChar(bits+1));
        //fscanf(arqB,"%c",&c);
        arv->c = 'k';
        arv->esq = NULL;
        arv->dir = NULL;
        bits = bits+9;
    }
    return arv;
}

//test
void imprimeArv(tArvore *arv){
    printf("<");
    if(arv != NULL){
        if(arv->dir == NULL && arv->esq == NULL)
            printf("%c",arv->c);
        imprimeArv(arv->esq);
        imprimeArv(arv->dir);
    }
    printf(">");
}