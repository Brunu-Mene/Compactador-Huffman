#ifndef T_DESCOMPACTA
#define T_DESCOMPACTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tArvore.h"
#include "tBitmap.h"

/*
 *  Explicação da Função
 *  Inputs:
 *  Output:
 *  pre-condição:
 *  pos-condição:
*/

/*
 *  Função para alocar espaço na memória destinado a uma variável tipo int;
 *  Output: Um ponteiro tipo int;
 *  pos-condição: Existencia de um espaço na memória heap ppara carregar um int;
*/
int *inicializaID();

/*
 *  Função para liberar da memória um ponteiro tipo int;
 *  Inputs: Ponteiro tipo int;
 *  pre-condição: O ponteiro deve estar inicializado;
 *  pos-condição: O espaço dedicado agora foi liberado da memória;
*/
void liberaID(int *id);

/*
 *  Função para retornar a quantidade de bytes do arquivo de interesse;
 *  Inputs: Um ponteiro para uma string;
 *  Output: Um inteiro unsigned;
 *  pre-condição: O ponteiro char deve conter o nome corredo do arquivo de interesse;
 *  pos-condição: Agora o tamanho em bytes do texto é acessível;
*/
unsigned int qtdByteArq(char *nomeArq);

/*
 *  Função para converter um número int >= 0 ou <= 256 em uma sequencia de 8 bits;
 *  Inputs: Um inteiro e um ponteiro de string;
 *  pre-condição: O inteiro deve carregar um valor entre 0 e 256, e o prontiero char deve estar previamente alocado com espaço 8;
 *  pos-condição: Agora o ponteiro string carrega a combinação de bits para representar o inteiro em questão;
*/
void recontroiBits(int byte,char *bits);

/*
 *  Função para preencher um bitmap com base no conteudo binario do arquivo de interesse;
 *  Inputs: Ponteiro para um bitmap e um ponteiro para uma string;
 *  pre-condição: Bitmap deve estar inicializado e a string deve conter o nome do arquivo de intresse;
 *  pos-condição: O ponteiro de bitmapa gora carrega o conteudo binário do arquivo em questão;
*/
void preencheBitMap(bitmap *bitMap,char *nomeArq);

/*
 *  Função para descompactar o texto binário de entrada;
 *  Inputs: Ponteiros para arvotre, bitmap e string;
 *  pre-condição: Os ponteiros arv e bitmap devem estar definidos e preenchidos, o ponteiro para a string deve conter o nome do arquivo passado de parametro;
 *  pos-condição: Criação e preenchimento de um arquivo com a reconstrução do arquivo compactado;
*/

void decodificaTexto(tArvore *arv,bitmap *bitMap, char *nomeArq);

#endif