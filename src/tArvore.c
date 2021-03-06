#include "../include/tArvore.h"
#include "../include/tCompacta.h"

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
        if(id == 0){
            tabela[arvHuff->c] = inicializaString(2);
            tabela[arvHuff->c][0] = '0';
            tabela[arvHuff->c][1] = '\0';
        }else{
            tabela[arvHuff->c] = inicializaString(id+1);
            for(int i=0; i<id ;i++){
                tabela[arvHuff->c][i] = cod[i];
            }
            tabela[arvHuff->c][id] = '\0';
        }
    }else{
        cod[id] = '0';
        preencheTabela(tabela,arvHuff->esq,cod,id+1);
        cod[id] = '1';
        preencheTabela(tabela,arvHuff->dir,cod,id+1);
    }
}

unsigned int tamanhoBinarioArv(tArvore *arv, int tam){
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

int reconstroiChar(char *byte){
    int valor = 0, grandeza = 128;
    for(int i=0; i<8; i++){
        if(byte[i] == '1'){
            valor = valor+grandeza;
        }
        grandeza = grandeza/2;
    }
    return valor;
}

tArvore *recriaArvore(tArvore *arv, bitmap *bitMap, int *id){
    arv = (tArvore *)malloc(sizeof(tArvore));
    arv->esq = NULL;
    arv->dir = NULL;
    if(bitmapGetBit(bitMap,*id) == 0){
        *id = *id + 1;
        arv->esq = recriaArvore(arv->esq,bitMap,id);
        arv->dir = recriaArvore(arv->dir,bitMap,id);
    }else{
        char bits[8];
        for(int i=0; i<8 ;i++) bits[i] = '0';
        for(int i=0; i<8 ;i++){
            if(bitmapGetBit(bitMap,*id+1+i) == 0){
                bits[i] = '0';
            }else{
                bits[i] = '1';
            }
        }
        arv->esq = arv->dir = NULL;
        arv->c = reconstroiChar(bits);
        *id = *id + 9;
    }
    return arv;
}

void recriaTexto(tArvore *arv,bitmap *bitMap, unsigned int id, int sobraBits, FILE *arq){
    tArvore *raiz = arv;
    if(raiz->esq == NULL && raiz->dir == NULL){
        while(id < bitmapGetLength(bitMap) - sobraBits){
            fprintf(arq,"%c",arv->c);
            id++;
        }
        return;
    }
    while(id < bitmapGetLength(bitMap) - sobraBits){
        if(arv->dir != NULL && arv->esq != NULL){
            if(bitmapGetBit(bitMap,id) == 1){
                arv = arv->dir;
            }else{
                arv = arv->esq;
            }
            id++;
        }
        if(arv->dir == NULL && arv->esq == NULL){
            fprintf(arq,"%c",arv->c);
            arv = raiz;
        }
    }
}