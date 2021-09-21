#include "../include/tArvore.h"
#include "../include/tTabelaHuff.h"

struct Arvore{
    tArvore *esq;
    tArvore *dir;
    unsigned char c;
    int qtd;
};

tArvore *inicializaArv(unsigned char c, int qtd){
    tArvore *arv = (tArvore *) malloc(sizeof(tArvore));
    arv->esq = NULL;
    arv->dir = NULL;
    arv->c = c;
    arv->qtd = qtd;

    return arv;
}

tArvore *inicializaArvVazia(){
    tArvore *arv = (tArvore *) malloc(sizeof(tArvore));
    arv->esq = NULL;
    arv->dir = NULL;
    
    return arv;
}

static int maior(int a, int b){
    if(a > b) return a;

    return b;
}

int altura(tArvore *arv){
    if(arv == NULL) return -1;

    return 1 + maior(altura(arv->esq),altura(arv->dir));
}

tArvore *preencheArvore(tArvore *arv,tArvore *esq, tArvore *dir, int qtd){
    arv->dir = dir;
    arv->esq = esq;
    arv->qtd = qtd;

    return arv;
}

unsigned char retornaCaracter(tArvore *arv){
    return arv->c;
}
int retornaQtd(tArvore *arv){
    return arv->qtd;
}

void liberaArvore(tArvore *arv){
    if(arv == NULL) return;

    liberaArvore(arv->esq);
    liberaArvore(arv->dir);

    free(arv);
}

void preencheTabela(unsigned char **tabela, tArvore *arvHuff,unsigned char *cod, int id){
    if(arvHuff == NULL) return;
    else if(arvHuff->esq == NULL && arvHuff->dir == NULL){
        tabela[arvHuff->c] = inicializaString(id+1);
        for(int i=0; i<id ;i++){
            tabela[arvHuff->c][i] = cod[i];
        }
        tabela[arvHuff->c][id] = '\0';
    }else{
        cod[id] = '0';
        preencheTabela(tabela,arvHuff->esq,cod,id+1);
        cod[id] = '1';
        preencheTabela(tabela,arvHuff->dir,cod,id+1);
    }
}

unsigned long int tamanhoBinarioArv(tArvore *arv, int tam){
    if(arv == NULL) return 0;
    if(arv->esq!=NULL && arv->dir!=NULL){
        tam = tam + tamanhoBinarioArv(arv->esq,1);
        tam = tam + tamanhoBinarioArv(arv->dir,0);
        return tam;
    }else{
        tam = tam + tamanhoBinarioArv(arv->esq,0);
        tam = tam + tamanhoBinarioArv(arv->dir,0);
        return tam+9;
    }
}
/*int tamanhoCodArv(tArvore *arv, int tam){
    if(arv == NULL) return 0;
    if(arv->esq!=NULL && arv->dir!=NULL){
        tam = tam + tamanhoCodArv(arv->esq,1);
        tam = tam + tamanhoCodArv(arv->dir,0);
        return tam;
    }else{
        return tam+2;
    }
}*/

/*void geraCodigoArv(tArvore *arv, unsigned char *cod){
    if(arv == NULL) return;
    if(arv->esq!=NULL || arv->dir!=NULL){
        strcat(cod,"0");
        //
        //fprintf(arqB,"0");
        geraCodigoArv(arv->esq,cod);
        geraCodigoArv(arv->dir,cod);
    }else{
        unsigned char aux[2];
        aux[0] = '1';
        aux[1] = arv->c;
        strcat(cod,aux);
        //
        //fprintf(arqB,"1%c",arv->c);
        //printa 8 bits(ou 1 byte) do caracter da folha
    }
}*/

void geraCodigoArv(tArvore *arv, bitmap *bitMap){
    if(arv == NULL) return;
    if(arv->esq!=NULL || arv->dir!=NULL){
        bitmapAppendLeastSignificantBit(bitMap,0);
        //printf("0");
        geraCodigoArv(arv->esq,bitMap);
        geraCodigoArv(arv->dir,bitMap);
    }else{
        bitmapAppendLeastSignificantBit(bitMap,1);
        //printf("1%c",arv->c);
        int grandeza = 128, num = 0;
        for(int j=0; j<8 ;j++){
                if((num + grandeza) <= arv->c){
                    //printf("1");
                    num = num + grandeza;
                    bitmapAppendLeastSignificantBit(bitMap,1);
                }else{
                    //printf("0");
                    bitmapAppendLeastSignificantBit(bitMap,0);
                }
            grandeza = grandeza/2;
        }
        //printf("\n");
    }
}

tArvore *recriaArvore(tArvore *arv, FILE *arqB){
    char bit = '\0';
    fscanf(arqB,"%c",&bit);
    arv = (tArvore *)malloc(sizeof(tArvore));
    if(bit == '0'){
        arv->esq = recriaArvore(arv->esq,arqB);
        arv->dir = recriaArvore(arv->dir,arqB);
    }else if(bit == '1'){
        char c;
        fscanf(arqB,"%c",&c);
        arv->c = c;
        arv->esq = NULL;
        arv->dir = NULL;
    }
    return arv;
}
int reconstroiChar(char *byte){
    int valor = 0, grandeza = 128;
    for(int i=0; i<8; i++){
        if(byte[i] == '1'){
            valor = valor+grandeza;
        }
        grandeza = grandeza/2;
    }
    return valor;
}
int incrementaIdArv(tArvore *arv, int tam){
    if(arv == NULL) return 0;   

    if(arv->dir == NULL && arv->esq == NULL) return 9;
    else{
        if(arv->dir == NULL){
            //printf("Test1");
            return tam + incrementaIdArv(arv->esq,tam+1);
        }
        else{
            return tam + incrementaIdArv(arv->dir,tam) + incrementaIdArv(arv->esq,tam+1);
        }
    }
}
//<<<a<><>><<,<><>><<e<><>><<p<><>><m<><>>>>>><<<l<><>><d<><>>><<<n<><>><k<><>>><<t<><>><s<><>>>>>>
//<<<a<><>><<,<><>><<e<><>><<p<><>><m<><>>>>>><<<l<><>><d<><>>><<<n<><>><k<><>>><<t<><>><s<><>>>>>>
//<<<a<><>><<,<><>><<e<><>><<p<><>><m<><>>>>>><<<l<><>><d<><>>><�<><>>>>
//<<<a<><>><<,<><>><<e<><>><<p<><>><m<><>>>>>><<<l<><>><d<><>>><�<><>>>>
//<<<a<><>><<,<><>><<e<><>><<p<><>><m<><>>>>>><�<><>>>
//<<<a<><>><<,<><>><<e<><>><<p<><>><m<><>>>>>><<�<><>><<�<><>><<�<><>><k<><>>>>>>

//infuncional, pensar como fazer dps
tArvore *recriaArvore2(tArvore *arv, bitmap *bitMap, int id){
    arv = (tArvore *)malloc(sizeof(tArvore));
    //printf("%d\n",id);
    arv->esq = NULL;
    arv->dir = NULL;
    if(bitmapGetBit(bitMap,id) == 0){
        //printf("0");
        arv->esq = recriaArvore2(arv->esq,bitMap,id+1);
        id = id + incrementaIdArv(arv,0);
        //printf("%d\n",id);
        arv->dir = recriaArvore2(arv->dir,bitMap,id+1);
    }else{
        //printf("1");
        //printf("%d\n",id);
        char bits[9];
        for(int i=0; i<9 ;i++) bits[i] = '0';
        for(int i=0; i<8 ;i++){
            if(bitmapGetBit(bitMap,id+1+i) == 0){
                bits[i] = '0';
            }else{
                bits[i] = '1';
            }
        }
        bits[8] = '\0';
        //printf("|%s|",bits);
        arv->esq = arv->dir = NULL;
        //printf("-%d-",reconstroiChar(bits));
        arv->c = reconstroiChar(bits);
    }
    return arv;
}

//test
void imprimeArv(tArvore *arv){
    printf("<");
    if(arv != NULL){
        if(arv->dir == NULL && arv->esq == NULL)
            printf("%c",arv->c);
        imprimeArv(arv->esq);
        imprimeArv(arv->dir);
    }
    printf(">");
}