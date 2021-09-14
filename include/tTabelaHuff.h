#ifndef T_TABELAHUFF
#define T_TABELAHUFF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **inicializaTabela();
char *inicializaString(int tam);
void liberaString(char *string);
void liberaTabela(char **tabelaHuff);

#endif