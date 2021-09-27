#ifndef T_ARVORE
#define T_ARVORE
// Definição da estrutura da árvore;
typedef struct Arvore tArvore;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBitmap.h"

/*
 * Função para inicializar na memória um ponteiro do tipo arv e preenhcer alguns dos seus campos;
 * Inputs: Um valor char e um valor int com valores dos campos a serem inicializados;
 * Output: Um ponteiro tipo arv inicializado e preenchido;
 * pre-condição: Os conteudos a serem inseredos no nó da arvore devem estar computados;
 * pos-condição: Um ponteiro com um endereço de memória para uma árvore foi inciaizalido/preenchido;
*/
tArvore *inicializaArv(unsigned char c, int qtd);

/*
 * Função para inicializar na memória um ponteiro do tipo arv;
 * Output: Um ponteiro tipo arv inicializado;
 * pos-condição: Um ponteiro com um endereço de memória para uma árvore foi inciaizalido;
*/
tArvore *inicializaArvVazia();

/*
 * Função para comparar o tamanho de dois inteiros;
 * Inputs: Dois inteiros;
 * Output: O dos inteiros inseridos;
 * pre-condição: Inteiros com valores associados;
 * pos-condição: O maior elementos entre os dois será retornado;
*/
static int maior(int a, int b);

/*
 * Função para determinar a altura de uma árvore binária;
 * Inputs: Um ponteiro de árvore;
 * Output: Um inteiro;
 * pre-condição: A árvore deve estar inicializada;
 * pos-condição: Retornamos o tamanho dessa árvore;
*/
int altura(tArvore *arv);

/*
 * Função para preencher os campos arv->esq e arv->dir de uma arvore ja inicializada;
 * Inputs: Tres ponteiros do tipo arvore e um inteiro;
 * Output: Um ponteiro do tipo árvore;
 * pre-condição: Os ponteiros de árvore devem estar inicializados;
 * pos-condição: O ponteiro arv tem agora seus campos preenchidos;
*/
tArvore *preencheArvore(tArvore *arv,tArvore *esq, tArvore *dir, int qtd);

/*
 * Função para acessar caracter contido no ponteiro tArvore;
 * Inputs: Um ponteiro tipo tAvore;
 * Output: Um char;
 * pre-condição: O ponteiro tArvore deve estar inicializado e preenchido;
 * pos-condição: O caracter contido em arv agr é visível;
*/
unsigned char retornaCaracter(tArvore *arv);

/*
 * Função para acessar o inteiro contido no ponteiro tArvore;
 * Inputs: Um ponteiro tipo tAvore;
 * Output: Um inteiro;
 * pre-condição: O ponteiro tArvore deve estar inicializado e preenchido;
 * pos-condição: O inteiro peso contido em arv agr é visível;
*/
int retornaQtd(tArvore *arv);

/*
 * Função para liberar o conteúdo contido no ponteiro tArvore;
 * Inputs: Um ponteiro tipo tAvore;
 * pre-condição: O ponteiro tArvore deve estar inicializado e preenchido;
 * pos-condição: O ponteiro do tipo tArvore bem como seu conteúdo é liberado da memória;    
*/
void liberaArvore(tArvore *arv);

/*
 * Função para preencher a tabela de Huffman através da recursividade;
 * Inputs: Um vetor de strings do tipo unsigned char, um ponteiro tipo tArvore, um código do tipo unsigned char e um inteiro;
 * pre-condição: O ponteiro do tipo tArvore ter sido inicializado, e os valores dos outros parâmetros inseridos serem válidos;
 * pos-condição: A função é chamada de maneira recursiva, percorrendo a árvore e preenchendo a tabela com os códigos do algoritmo de huffman;    
*/
void preencheTabela(unsigned char **tabela, tArvore *arvHuff,unsigned char *cod, int id);

/*
 * Função para determinar o tamanho binário que uma árvore irá ocupar;
 * Inputs: Um ponteiro do tipo arv e um inteiro;
 * Output: Um inteiro >=0;
 * pre-condição: A árvore deve estar inicializada e o inteiro a principio será passado como 0;
 * pos-condição: Será possível visualizar quantos bits a árvore ocupará na codificação ;
*/
unsigned int tamanhoBinarioArv(tArvore *arv, int tam);

/*
 * Função para codificar uma árvore em binario;
 * Inputs: Um ponteiro para carregar a árvore e um ponteiro para carregar o bitmap;
 * pre-condição: O ponteiro de arv deveestra incializado/preenchdio, o ponteiro bitmap deve estar inicializado;
 * pos-condição: O bitmap agora carrega o código de representação binária da árvore em questão;
*/
void geraCodigoArv(tArvore *arv, bitmap *bitMap);

/*
 * Função para transformar sequencia de bits em sua representação inteira;
 * Inputs: Um ponteiro para uma string;
 * Output: Um inteiro;
 * pre-condição: O ponteiro da string deve estar inicializado e preenchido, com tamanho ==8;
 * pos-condição: A representação agora poderá ser visualizada como um inteiro
*/
int reconstroiChar(char *byte);

/*
 * Função para ler arquivo binario e reconstruir árvore de codificação;
 * Inputs: Ponteiros para arvore, bitmap e para um inteiro;
 * Output: Um ponteiro do tipo arvore;
 * pre-condição: O ponteiro para bitmap deve estar inicializado/preenchido, o ponteiro de id deve carregar valor 3(correspondente a primeira posição do código da arvore no bitmap);
 * pos-condição: Um ponteiro para a raiz de uma árvore preenchida;
*/
tArvore *recriaArvore(tArvore *arv, bitmap *bitMap, int *id);

/*
 * Função andar pela árvore de codificação e gerar um arquivo de saída decodificado;
 * Inputs: Ponteiros para árvore, bitmap e arquivo, alem de duas varáveis tipo inteiro;
 * pre-condição: O ponteiro arv deve carregar a árvore de decodificação, bitmap deve estar preenchido, id deve conter a primeira posição do código do texto e sobra bits deve ser >=0 ou <=7;
 * pos-condição: O arquivo de saída agora está preenchido com a decodificação;
*/
void recriaTexto(tArvore *arv,bitmap *bitMap, unsigned int id, int sobraBits, FILE *arq);

#endif