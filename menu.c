#include<stdio.h>
#include<stdlib.h>

#include "menu.h"

void imprime_opcoes(){
    printf(" ____________________________________________________________________\n");
    printf("|                                                                    |\n");
    printf("|                    SELECIONE A OPCAO DESEJADA:                     |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     1 -->   CADASTRO                               |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     2 -->   IMPRIMIR                               |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     3 -->   REMOVER DISTRIBUICAO                   |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     4 -->   CARREGAR ARQUIVO EM LOTE               |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     5 -->   SAIR                                   |\n");
    printf("|____________________________________________________________________|\n");
}

void printar_OpcoesCadastros(){
    printf(" ____________________________________________________________________\n");
    printf("|                                                                    |\n");
    printf("|                    SELECIONE O TIPO DE CADASTRO:                   |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     1 -->   CADASTRO DE CURSO                      |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     2 -->   CADASTRO DE DISCIPLINA                 |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     3 -->   CADASTRO DE PROFESSOR                  |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     4 -->   CADASTRO DE DISTRIBUICAO               |\n");
    printf("|                             DE DISCIPLINA                          |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                     5 -->   SAIR                                   |\n");
    printf("|____________________________________________________________________|\n");
    
}

void printa_OpcoesImprimir(){
    printf(" ____________________________________________________________________\n");
    printf("|                                                                    |\n");
    printf("|                    SELECIONE O QUE DESEJA LISTAR:                  |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                 1 -->   LISTAR CURSOS DISPONIVEIS                  |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                 2 -->   LISTAR DISCIPLINAS DISPONIVEIS             |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                 3 -->   LISTAR PROFESSOR CADASTRADOS               |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                 4 -->   LISTAR DISTRIBUICAO                        |\n");
    printf("|                         ORDENADA P/CURSO                           |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                 5 -->   LISTAR TODA DISTRIBUICAO ORDENADA          |\n");
    printf("|                         ORDENADA P/ANO LETIVO                      |\n");
    printf("|____________________________________________________________________|\n");
    printf("|                                                                    |\n");
    printf("|                 6 -->   VOLTAR                                     |\n");
    printf("|____________________________________________________________________|\n");
}