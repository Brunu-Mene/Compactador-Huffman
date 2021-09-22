#include "../include/tArvore.h"
#include "../include/tDescompacta.h"

int main(int argc, char **argv){
    if (argc < 1){
        printf("Numero de parametros incorreto!\n");
        exit(1);
    }
    printf("%d\n",qtdByteArq(argv[1])*8);
    bitmap *bitMap = bitmapInit(qtdByteArq(argv[1])*8);
    preencheBitMap(bitMap, argv[1]);
    tArvore *arv = recriaArvore(arv,bitMap,3);
    imprimeArv(arv);
    decodificaTexto(arv,bitMap,argv[1]);
    liberaArvore(arv);
    bitmapLibera(bitMap);
    return 0;
}