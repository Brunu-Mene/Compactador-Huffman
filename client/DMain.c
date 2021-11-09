#include "../include/tArvore.h"
#include "../include/tDescompacta.h"
//

int main(int argc, char **argv){
    if (argc < 1){
        printf("Numero de parametros incorreto!\n");
        exit(1);
    }
    bitmap *bitMap = bitmapInit(qtdByteArq(argv[1])*8);
    preencheBitMap(bitMap, argv[1]);
    int *id = inicializaID();
    tArvore *arv = recriaArvore(arv,bitMap,id);
    liberaID(id);
    decodificaTexto(arv,bitMap,argv[1]);
    liberaArvore(arv);
    bitmapLibera(bitMap);
    return 0;
}

