#include "cabecalho.h"
#include<stdio.h>
#include<stdlib.h>

void cria_lista_vazia(FILE* arq){
    cabecalho* cab = (cabecalho *) malloc(sizeof(cabecalho));
    cab->pos_cabeca = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;
    escreve_cabecalho(arq, cab);
    free(cab);
}

// le o cabecalho do arquivo contendo as informacoes da lista
// pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos-condicao: retorna o ponteiro para o cabecalho lido

cabecalho* le_cabecalho(FILE *arq){
    cabecalho* cab = (cabecalho*)malloc(sizeof(cabecalho));
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, arq);
    return cab;
}

void escreve_cabecalho(FILE* arq, cabecalho* cab){
    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, arq);
}

no* le_no(FILE *arq, int pos){
    no* x = malloc(sizeof(no));
    fseek(arq, sizeof(cabecalho) + pos*sizeof(no), SEEK_SET);
    fread(x, sizeof(no), 1, arq);
    return x;
}