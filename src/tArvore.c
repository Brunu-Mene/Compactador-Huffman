#include "../include/tArvore.h"
#include "../include/tTabelaHuff.h"

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

void preencheTabela(char **tabela, tArvore *arvHuff,char *cod, int id){
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

//test
void imprimeArv(tArvore *arv){
    printf("<");
    if(arv != NULL){
        printf("%d",arv->qtd);
        imprimeArv(arv->esq);
        imprimeArv(arv->dir);
    }
    printf(">");
}