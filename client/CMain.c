#include "../include/tArvore.h"
#include "../include/tLista.h"

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        printf("Numero de parametros incorreto!\n");
        exit(1);
    }
    tLista *list = iniciaLista();
    preencheLista(list, argv[1]);
    //test
    //printaLista(list);

    list = combinaListArv(list);
    tArvore *arvHuff = retornaPriArv(list);
    liberaLista(list);
    unsigned char **tabelaHuff = malloc(sizeof(char *) * 256);
    for(int i=0; i<256; i++){
        tabelaHuff[i] = malloc(sizeof(char)*8);//puta que pariu ???
    }
    unsigned char *cod = malloc(sizeof(char) * 8);
    preencheTabela(tabelaHuff, arvHuff, cod, 0);
    imprimeArv(arvHuff);
    printf("\n%ld-%s\n",strlen(tabelaHuff['f']),tabelaHuff['f']);
    
    liberaArvore(arvHuff);
    return 0;
}