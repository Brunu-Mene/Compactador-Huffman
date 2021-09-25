#ifndef T_ARVORE
#define T_ARVORE

typedef struct Arvore tArvore;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBitmap.h"

tArvore *inicializaArv(unsigned char c, int qtd);
tArvore *inicializaArvVazia();
static int maior(int a, int b);
int altura(tArvore *arv);
tArvore *preencheArvore(tArvore *arv,tArvore *esq, tArvore *dir, int qtd);
unsigned char retornaCaracter(tArvore *arv);
int retornaQtd(tArvore *arv);
void liberaArvore(tArvore *arv);
void preencheTabela(unsigned char **tabela, tArvore *arvHuff,unsigned char *cod, int id);
unsigned int tamanhoBinarioArv(tArvore *arv, int tam);
void geraCodigoArv(tArvore *arv, bitmap *bitMap);
int reconstroiChar(char *byte);
int incrementaIdArv(tArvore *arv, int tam);
tArvore *recriaArvore(tArvore *arv, bitmap *bitMap, int id);
void recriaTexto(tArvore *arv,bitmap *bitMap, unsigned int id, int sobraBits, FILE *arq);

#endif