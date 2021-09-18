#ifndef T_ARVORE
#define T_ARVORE

typedef struct Arvore tArvore;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBitmap.h"

tArvore *inicializaArv(unsigned char c, int qtd);
tArvore *inicializaArvVazia();
int altura(tArvore *arv);
static int maior(int a, int b);
void liberaArvore(tArvore *arv);
unsigned char retornaCaracter(tArvore *arv);
int retornaQtd(tArvore *arv);
tArvore *preencheArvore(tArvore *arv,tArvore *esq, tArvore *dir, int qtd);
void preencheTabela(unsigned char **tabela, tArvore *arvHuff,unsigned char *cod, int id);

//test
void imprimeArv(tArvore *arv);
void geraCodigoArv(tArvore *arv, bitmap *bitMap);
tArvore *recriaArvore(tArvore *arv, FILE *arqB);
int tamanhoBinarioArv(tArvore *arv, int tam);
//int tamanhoCodArv(tArvore *arv, int tam);


//MEME
tArvore *recriaArvore2(tArvore *arv, char *bits);

#endif