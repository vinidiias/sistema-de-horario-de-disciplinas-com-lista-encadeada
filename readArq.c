#include<stdio.h>
#include<stdlib.h>

#include "readArq.h"
#include "cabecalho.h"

FBIN* open_files(){
    FBIN* arq = (FBIN*)malloc(sizeof(FBIN));

    arq->fc = fopen("curso.bin", "r+b");
    arq->fd = fopen("disciplina.bin", "r+b");
    arq->fp = fopen("professor.bin", "r+b");
    arq->fds = fopen("distribuicao.bin", "r+b");

    if(arq->fc == NULL){
        arq->fc = fopen("curso.bin", "w+b");
        cria_lista_vazia(arq->fc);
    }
    if(arq->fd == NULL){
        arq->fd = fopen("disciplina.bin", "w+b");
        cria_lista_vazia(arq->fd);
    }
    
    if(arq->fp == NULL){
        arq->fp = fopen("professor.bin", "w+b");
        cria_lista_vazia(arq->fp);
    }
    
    if(arq->fds == NULL){
        arq->fds = fopen("distribuicao.bin", "w+b");
        cria_lista_vazia(arq->fds);
    }
    return arq;
}

void fclose_bins(FBIN *fb){
    fclose(fb->fp);
    fclose(fb->fc);
    fclose(fb->fds);
    fclose(fb->fd);
}