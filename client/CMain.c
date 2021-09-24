#include "../include/tArvore.h"
#include "../include/tLista.h"
#include "../include/tCompacta.h"

int main(int argc, char **argv)
{
    if (argc < 1){
        printf("Numero de parametros incorreto!\n");
        exit(1);
    }
    tLista *list = iniciaLista();
    preencheLista(list, argv[1]);
    combinaListArv(list);
    tArvore *arvHuff = retornaPriArv(list);
    liberaLista(list);
    
    unsigned char **tabelaHuff = inicializaTabela();
    unsigned char *cod = inicializaString(altura(arvHuff)+2);
    preencheTabela(tabelaHuff, arvHuff, cod, 0);
    liberaString(cod);
    geraSaida(tabelaHuff,argv[1],arvHuff);

    liberaTabela(tabelaHuff);
    imprimeArv(arvHuff);
    liberaArvore(arvHuff);
    
    return 0;
}