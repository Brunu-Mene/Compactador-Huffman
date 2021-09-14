#include "../include/tArvore.h"
#include "../include/tLista.h"
#include "../include/tTabelaHuff.h"

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("Numero de parametros incorreto!\n");
        exit(1);
    }
    tLista *list = iniciaLista();
    preencheLista(list, argv[1]);
    list = combinaListArv(list);
    tArvore *arvHuff = retornaPriArv(list);
    liberaLista(list);

    char **tabelaHuff = inicializaTabela();
    char *cod = inicializaString(9);
    preencheTabela(tabelaHuff, arvHuff, cod, 0);
    liberaString(cod);
    //imprimeArv(arvHuff);
    char *tes = strdup(tabelaHuff['g']);
    printf("%ld - %s\n",strlen(tabelaHuff['g']),tes);
    liberaString(tes);


    liberaTabela(tabelaHuff);
    liberaArvore(arvHuff);
    return 0;
}