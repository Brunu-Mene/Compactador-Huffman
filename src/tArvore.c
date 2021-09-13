#include "../include/tArvore.h"

struct Arvore{
    tArvore *esq;
    tArvore *dir;
    char c;
    int qtd;
};

tArvore *inicializaArv(char c){
    tArvore *arv = (tArvore *) malloc(sizeof(tArvore));
    arv->esq = NULL;
    arv->dir = NULL;
    arv->c = c;
    arv->qtd = 1;

    return arv;
}

tArvore *inicializaArvVazia(){
    tArvore *arv = (tArvore *) malloc(sizeof(tArvore));
    arv->esq = NULL;
    arv->dir = NULL;
    
    return arv;
}


tArvore *preencheArvore(tArvore *arv,tArvore *esq, tArvore *dir, int qtd){
    arv->dir = dir;
    arv->esq = esq;
    arv->qtd = qtd;

    return arv;
}

char retornaCaracter(tArvore *arv){
    return arv->c;
}
int retornaQtd(tArvore *arv){
    return arv->qtd;
}

void incrementaContador(tArvore *arv){
    arv->qtd++;
}

void liberaArvore(tArvore *arv){
    if(arv == NULL) return;

    liberaArvore(arv->esq);
    liberaArvore(arv->dir);

    free(arv);
}



void imprimeArv(tArvore *arv){
    printf("<");
    if(arv != NULL){
        printf("%d",arv->qtd);
        imprimeArv(arv->esq);
        imprimeArv(arv->dir);
    }
    printf(">");
}