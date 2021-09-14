#include "tLista.h"

typedef struct Celula tCelula;
struct Celula{
    tArvore *arv;
    tCelula *prox;
};

struct Lista{
    tCelula *pri;
    tCelula *ult;
};

tLista *iniciaLista(){
    tLista *list = (tLista *) malloc(sizeof(tLista));
    list->pri = NULL;
    list->ult = NULL;

    return list;
}

void insereLista(tLista *list,tArvore *arv){
    tCelula *novaCel = (tCelula *)malloc(sizeof(tCelula));
    novaCel->arv = arv;
    novaCel->prox = NULL;

    if(list->pri == NULL){
        list->pri = novaCel;
        list->ult = novaCel;
    }else{
        list->ult->prox = novaCel;
        list->ult = novaCel;
    }
}

void procuraElemento(tLista *list, char c){
    for(tCelula *p = list->pri; p!=NULL ; p=p->prox){
        if(retornaCaracter(p->arv) == c){
            incrementaContador(p->arv);
            return;
        }
    }
    tArvore *arv = inicializaArv(c);
    insereLista(list, arv);
}

void preencheLista(tLista *list, char *nomeArq){
    char adress[50] = "data/";
    char c;
    strcat(adress,nomeArq);
    FILE *arq = fopen(adress,"r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        exit(1);
    }
    while(fscanf(arq,"%c",&c) == 1){
        procuraElemento(list,c);
    }

    fclose(arq);
}

void ordenaLista(tLista *list){
    tCelula *p,*j;
    tArvore *aux;
    for(j=list->pri->prox; j!=NULL ;j=j->prox){
        for(p=list->pri; p->prox!=NULL ;p=p->prox){
            if(retornaQtd(p->arv) > retornaQtd(p->prox->arv)){
                aux = p->arv;
                p->arv = p->prox->arv;
                p->prox->arv = aux; 
            }
        }
    }
}

tLista *combinaListArv(tLista *list){
    if(list->pri->prox == NULL) return list;

    tLista *novaList = iniciaLista();
    ordenaLista(list);
    for(tCelula *p=list->pri; p!=NULL ;p=p->prox){
        if(p->prox == NULL){
            insereLista(novaList,p->arv);
        }else{
            tArvore *arv = inicializaArvVazia();
            arv = preencheArvore(arv,p->arv,p->prox->arv,retornaQtd(p->arv)+retornaQtd(p->prox->arv));
            insereLista(novaList,arv);
            p=p->prox;
        }
    }

    liberaLista(list);
    if(novaList->pri->prox!=NULL) return combinaListArv(novaList);
    else return novaList;
}

void liberaLista(tLista *list){
    tCelula *p = list->pri;
    tCelula *t;
    while(p!=NULL){
        t = p->prox;
        free(p);
        p = t;
    }
    free(list);
}

tArvore *retornaPriArv(tLista *list){
    return list->pri->arv;
}

//função de test
void printaLista(tLista *list){
    for(tCelula *p = list->pri; p!=NULL ;p=p->prox){
        printf("%c %d\n",retornaCaracter(p->arv),retornaQtd(p->arv));
    }
}