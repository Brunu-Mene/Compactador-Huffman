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

void insereListaOrdenado(tLista *lista, tArvore *arv){
    tCelula *novaCel = (tCelula *)malloc(sizeof(tCelula));
    novaCel->arv = arv;
    novaCel->prox = NULL;

    if(lista->pri == NULL){
        lista->pri = novaCel;
        lista->ult = novaCel;
        return;
    }else if(retornaQtd(arv) <= retornaQtd(lista->pri->arv)){
        novaCel->prox = lista->pri;
        lista->pri = novaCel;
        return;
    }else if(retornaQtd(lista->ult->arv) < retornaQtd(arv)){
        lista->ult->prox = novaCel;
        lista->ult = novaCel;
        return;
    }
    tCelula *p,*t;
    t = lista->pri;
    p = lista->pri->prox;
    while(1){
        if(retornaQtd(arv)<=retornaQtd(p->arv)){
            t->prox = novaCel;
            novaCel->prox = p;
            return;
        }
        t=t->prox;
        p=p->prox;
    }
}

void preencheLista(tLista *list, char *nomeArq){
    char adress[50] = "data/";
    unsigned char c;
    int elementos[257];
    for(int i=0; i<257 ;i++){
        elementos[i] = 0;
    }
    strcat(adress,nomeArq);
    FILE *arq = fopen(adress,"r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        exit(1);
    }
    while(fscanf(arq,"%c",&c) == 1){
        elementos[c]++;
    }
    for(int i=0; i<257 ;i++){
        if(elementos[i]!=0){
            tArvore *arv = inicializaArv(i,elementos[i]);
            insereListaOrdenado(list,arv);
        }
    }
    fclose(arq);
}

void combinaListArv(tLista *list){
    tCelula *p;
    for(p=list->pri; p->prox!=NULL ;p=p){
        tArvore *arv = inicializaArvVazia();
        arv = preencheArvore(arv,p->arv,p->prox->arv,retornaQtd(p->arv)+retornaQtd(p->prox->arv));
        insereListaOrdenado(list,arv);
        
        if(p->prox->prox != NULL){
            tCelula *aux = p->prox->prox;
            free(p->prox);
            free(p);
            p = aux;
            list->pri = p;
        }
    }
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
        printf("%d ",retornaQtd(p->arv));
    }
}