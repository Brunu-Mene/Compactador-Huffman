#ifndef T_TABELAHUFF
#define T_TABELAHUFF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char **inicializaTabela();
unsigned char *inicializaString(int tam);
void liberaString(unsigned char *string);
void liberaTabela(unsigned char **tabelaHuff);
void geraSaida(unsigned char **tabelaHuff, char *nomeArq);

#endif