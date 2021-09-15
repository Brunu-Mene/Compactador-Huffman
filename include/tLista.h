#ifndef T_LISTA
#define T_LISTA

typedef struct Lista tLista;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tArvore.h"

tLista *iniciaLista();
void insereLista(tLista *list,tArvore *arv);
void procuraElemento(tLista *list, char c);
void preencheLista(tLista *list, char *nomeArq);
void ordenaLista(tLista *list);
void combinaListArv(tLista *list);
tArvore *retornaPriArv(tLista *list);

void liberaLista(tLista *list);

//função de test
void printaLista(tLista *list);

#endif