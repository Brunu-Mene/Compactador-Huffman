#ifndef T_ARVORE
#define T_ARVORE

typedef struct Arvore tArvore;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBitmap.h"

tArvore *inicializaArv(char c);
tArvore *inicializaArvVazia();
void liberaArvore(tArvore *arv);
char retornaCaracter(tArvore *arv);
int retornaQtd(tArvore *arv);
tArvore *preencheArvore(tArvore *arv,tArvore *esq, tArvore *dir, int qtd);
void incrementaContador(tArvore *arv);
void geraSaida(tArvore *arvHuff, char *nomeArq);
void preencheTabela(char **tabela, tArvore *arvHuff,char *cod, int id);

//test
void imprimeArv(tArvore *arv);

#endif