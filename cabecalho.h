#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int pos_cabeca;
    int pos_topo;
    int pos_livre;
}cabecalho;

typedef struct {
    int info;
    int prox;
} no;

// cria cabecalho vazia para o arquivo 
// pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos-condicao: cabecalho vazio criado e escrito no arquivo
void cria_lista_vazia(FILE* arq);

cabecalho* le_cabecalho(FILE *arq);

// le um no em uma determinada posicao do arquivo
// pre-condicao: o arquivo deve estar aberto e ser um arquivo de lista
//               pos deve ser uma posicao valida da lista
// pos-condicao: ponteiro para no lido eh retornado
no* le_no(FILE *arq, int pos);

// escreve no arquivo contendo as informacoes da lista
// pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
// pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab);
