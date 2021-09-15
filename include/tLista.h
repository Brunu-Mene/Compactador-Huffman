#ifndef T_LISTA
#define T_LISTA

typedef struct Lista tLista;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tArvore.h"

tLista *iniciaLista();
void insereListaOrdenado(tLista *lista, tArvore *arv);
void preencheLista(tLista *list, char *nomeArq);
void combinaListArv(tLista *list);
tArvore *retornaPriArv(tLista *list);
void liberaLista(tLista *list);

//função de test
//void ordenaLista(tLista *list);
void printaLista(tLista *list);

#endif