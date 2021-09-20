#include "../include/tArvore.h"
#include "../include/tDescompacta.h"

int main(int argc, char **argv){
    if (argc < 1){
        printf("Numero de parametros incorreto!\n");
        exit(1);
    }
    bitmap *bitMap = bitmapInit(qtdByteArq(argv[1])*8);
    preencheBitMap(bitMap, argv[1]);
    bitmapLibera(bitMap);
    return 0;
}