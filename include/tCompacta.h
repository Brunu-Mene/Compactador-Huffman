#ifndef T_COMPACTA
#define T_COMPACTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tArvore.h"

/*
 *  Função que inicializa uma tabela do algoritmo de Huffman;
 *  Outputs: Um vetor de ponteiros do tipo unsigned char;
 *  pos-condição: Há a inicialização e alocação do vetor com 256 espaços necessários para a construção da tabela de Huffman;
*/
unsigned char **inicializaTabela();

/*
 *  É a função padrão responsável por inicializar uma string qualquer;
 *  Inputs: O tamanho da string em questão;
 *  Output: Um vetor dinâmico do tipo unsigned char;
 *  pos-condição: Um vetor de caracteres com tamanho pré definido e bytes 0 nas "tam" posições alocadas;
*/
unsigned char *inicializaString(int tam);

/*
 *  Função responsável por liberar o espaço alocado por uma string qualquer;
 *  Inputs: Uma string do tipo unsigned char;
 *  pré-condição: Um vetor de caracteres do tipo unsigned char ter sido previamente alocado;
 *  pos-condição: O vetor de caracteres é liberado da memória juntamente com suas informações previamente alocadas;
*/
void liberaString(unsigned char *string);

/*
 *  Função responsável por liberar a tabela de huffman;
 *  Inputs: Um vetor dinâmico do tipo unsigned char;
 *  pré-condição: A prévia alocação de um vetor "tabela de huffman" do tipo unsigned char;
 *  pos-condição: A tabela e os caracteres que haviam sido alocados são liberados da memória;
*/
void liberaTabela(unsigned char **tabelaHuff);

/*
 *  Função responsável pela lógica de contabilizar a quantidade de bits dentro de um arquivo .txt tendo em base uma determinada tabela de huffman;
 *  Inputs: Um vetor dinâmico do tipo unsigned char e o ponteiro para um arquivo;
 *  Output: Um unsigned int representando a quantidade de bits;
 *  pré-condição: Tanto o vetor tabelaHuff, quanto o arquivo terem sido previamente inicializados;
 *  pos-condição: É retornada a quantidade de bits de um determinado arquivo .txt com base na tabela de huffman previamente gerada;
*/
unsigned int tamanhoBinarioTxt(unsigned char **tabelaHuff, FILE *arq);

/*
 *  Responsável por utilizar as funções do tad Bitmap para gerar o código de bits que será escrito no arquivo compactado;
 *  Inputs: Um vetor dinâmico do tipo unsigned char, um bitmap e o ponteiro para um arquivo;
 *  pré-condição: A tabela de Huffamn, o bitmap e o arquivo terem sido previamente inicializados;
 *  pos-condição: É gerado um código binário à partir do arquivo de texto, acessando a tabela de huffman de acordo com o caractere lido e utilizando o TAD bitmap para escrever o binário em cima do arquivo .comp;
*/
void geraCodigoArq(unsigned char **tabelaHuff,bitmap *bitMap,FILE *arq);

/*
 *  Função para gerar o arquivo compactado de saída;
 *  Inputs: Ponteiros duplo para a tabela com os códigos de cada caracter, dois ponteiros para string e para arv;
 *  pre-condição: Os ponteiros arv e tabelaHuff devem estar definidos/preenchidos e o ponteiro para string deve conter o nome do arquivo de interesse;
 *  pos-condição: Um arquivo .comp foi gerado com o cógido binário da arvore mais o arquivo em sua versão compactada;
*/
void geraSaida(unsigned char **tabelaHuff, char *nomeArq, tArvore *arvHuff);

#endif