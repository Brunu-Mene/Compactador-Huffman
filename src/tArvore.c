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

void geraCodigoArv(tArvore *arv, FILE*arqB){
    if(arv == NULL) return;
    if(arv->esq!=NULL || arv->dir!=NULL){
        fprintf(arqB,"0");
        geraCodigoArv(arv->esq,arqB);
        geraCodigoArv(arv->dir,arqB);
    }else{
        fprintf(arqB,"1%c",arv->c);
        //printa 8 bits(ou 1 byte) do caracter da folha
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