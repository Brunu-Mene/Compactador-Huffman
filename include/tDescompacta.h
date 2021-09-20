#ifndef T_DESCOMPACTA
#define T_DESCOMPACTA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBitmap.h"

unsigned int qtdByteArq(char *nomeArq);
void recontroiBits(int byte,char *bits);
void preencheBitMap(bitmap *bitMap,char *nomeArq);

#endif