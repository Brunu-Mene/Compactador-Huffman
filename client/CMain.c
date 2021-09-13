#include "../include/tArvore.h"
#include "../include/tLista.h"

int main(int argc, char **argv){
    if(argc < 1){
        printf("Numero de parametros incorreto!\n");
        exit(1);
    }
    tLista *list = iniciaLista();
    preencheLista(list, argv[1]);
    printaLista(list);

    list = combinaArvores(list);
    printf("\n");

    printaListaTest(list);
    liberaLista(list);
    return 0;
}