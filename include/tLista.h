#ifndef T_LISTA
#define T_LISTA

// Definição da estrutura de uma lista encadeada;
typedef struct Lista tLista;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tArvore.h"

/*
 * Função para alocar espaço na memória para lista;
 * Output: Um ponteiro para um endereço reservado a lista;
 * pos-condição: O ponteiro de lista retornado agora tem um espaço reservado na memória;
*/
tLista *iniciaLista();

/*
 *  Função para inserer ponteiros arv numa lista de maneira ordenada(a julgar pelos pesos das árvores);
 *  Inputs: Ponteiros para a lista e para o elemento(tArvore);
 *  pre-condição: O pontiro lista deve estar inicializa e o ponteiro arvore deve estar inicializado/preenchido;
 *  pos-condição: O elemtno arv agora faz parte da lista;
*/
void insereListaOrdenado(tLista *lista, tArvore *arv);

/*
 *  Função para preencher uma lista com base nas árvores formadas a partir do arquivo de entrada;
 *  Inputs: Ponteiro para uma lista e para uma string(nome do arquivo de entrada);
 *  pre-condição: A lista deve estar definida e a string deve contar o nome do arquivo onde o conteudo de interesse está armazenado;
 *  pos-condição: A lista agora contem uma sequência de n árvores formadas a partir do arquivo de entrada;
*/
void preencheLista(tLista *list, char *nomeArq);


void combinaListArv(tLista *list);

/*
 * Função para liberar as celulas e a sentinela de uma lista;
 * Inputs: Ponteiro para lista;
 * pre-condição: A lista deve estar inicializa;
 * pos-condição: Agora a lista está liberado porém seu conteudo permanece na memória;
*/
void liberaLista(tLista *list);

/*
 * Função de acesso para primeiro elemento da lista;
 * Inputs: Ponteiro para lista;
 * Output: Ponteiro para primeira árvore da lista;
 * pre-condição: A lista deve estar inicializa e preenchida;
 * pos-condição: Retorno uma árvore já pre definida;
*/
tArvore *retornaPriArv(tLista *list);

#endif