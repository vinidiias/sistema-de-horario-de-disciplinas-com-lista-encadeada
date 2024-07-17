#ifndef DISTRIBUICOES_H
#define DISTRIBUICOES_H

#include<stdio.h>
#include "disciplina.h"
#include "readArq.h"
#include "professor.h"

typedef struct no4{
    int cod_disciplina;
    int ano_letivo;
    int cod_prof;
}DISTRIB;

typedef struct {
    DISTRIB prof_disciplina;
    int prox;
}NO_DISTRIB;

// Descrição: Escreve a estrutura NO_DISTRIB no arquivo na posição especificada.
// Entrada: Um ponteiro para um arquivo (FILE* fd), um ponteiro para uma estrutura NO_DISTRIB (NO_DISTRIB* distrib) e uma posição no arquivo (int pos).
// Retorno: Nenhum.
// Pré-condição: O arquivo deve estar aberto e pronto para escrita. A estrutura distrib deve conter dados válidos.
// Pós-condição: Os dados são escritos no arquivo na posição especificada.
void write_no_distrib(FILE *fd, NO_DISTRIB* distrib, int pos);

// Descrição: Lê a estrutura NO_DISTRIB do arquivo na posição especificada.
// Entrada: Um ponteiro para um arquivo (FILE* fd) e uma posição no arquivo (int pos).
// Retorno: Um ponteiro para uma estrutura NO_DISTRIB alocada dinamicamente.
// Pré-condição: O arquivo deve estar aberto e pronto para leitura. A posição especificada deve conter dados válidos.
// Pós-condição: A estrutura é lida do arquivo e retornada como um ponteiro alocado dinamicamente.
NO_DISTRIB* read_no_distrib(FILE* fd, int pos);

// Descrição: Insere uma nova distribuição de disciplina no início do arquivo de distribuições.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fd), um código de disciplina (int cod_disciplina), um ano letivo (int ano_letivo) e um código de professor (int cod_prof).
// Retorno: Nenhum.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para escrita. Os códigos de disciplina, ano letivo e professor devem ser válidos.
// Pós-condição: A nova distribuição é inserida no início do arquivo de distribuições.
void insertHead_distrib(FILE* fd, int cod_disciplina, int ano_letivo, int cod_prof);

// Descrição: Função auxiliar para remover uma distribuição de disciplina com base no código da disciplina e no ano letivo, do arquivo de distribuições (FILE* fd).
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fd), um inteiro representando o código da disciplina (int cod), e um inteiro representando o ano letivo (int ano).
// Retorno: Nenhum.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para escrita. cod e ano devem representar valores válidos para uma distribuição de disciplina.
// Pós-condição: A distribuição de disciplina correspondente é removida do arquivo de distribuições.
void remover_distribuicao_aux(FILE* fd, int cod, int ano);

// Descrição: Função para listar todas as distribuições de disciplina no arquivo de distribuições, organizadas por cursos.
// Entrada: Um ponteiro para uma estrutura FBIN contendo ponteiros para os arquivos de curso, disciplina e professor associados (FBIN* fb).
// Retorno: Nenhum.
// Pré-condição: Os arquivos de curso, disciplina e professor devem estar abertos e prontos para leitura.
// Pós-condição: Todas as distribuições de disciplina são listadas na saída padrão, organizadas por cursos.
void listar_distribuicoes(FBIN* fb);

// Descrição: Função para imprimir os detalhes de uma distribuição de disciplina, incluindo informações do curso, da disciplina e do professor associados a essa distribuição.
// Entrada: Um ponteiro para uma estrutura NO_DISTRIB contendo dados da distribuição (NO_DISTRIB* distrib), uma estrutura NO_CURSO contendo dados do curso associado (NO_CURSO curso), uma estrutura NO_DISC contendo dados da disciplina associada (NO_DISC disciplina) e uma estrutura NO_PROF contendo dados do professor associado (NO_PROF prof).
// Retorno: Nenhum.
// Pré-condição: As estruturas de distribuição, curso, disciplina e professor devem conter dados válidos.
// Pós-condição: Os detalhes da distribuição, curso, disciplina e professor são impressos na saída padrão.
void imprimeDistribuicoes(NO_DISTRIB* distrib, NO_CURSO curso, NO_DISC disciplina, NO_PROF prof);

// Descrição: Insere uma nova distribuição de disciplina no arquivo de distribuições, mantendo a ordem.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fds) e um ponteiro para uma estrutura NO_DISTRIB (NO_DISTRIB* x).
// Retorno: Nenhum.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para escrita. A estrutura x deve conter dados válidos.
// Pós-condição: A nova distribuição é inserida no arquivo de distribuições mantendo a ordem.
void insertDistribuicao(FILE* fds, NO_DISTRIB* x);

// Descrição: Insere uma nova distribuição de disciplina no arquivo de distribuições em uma posição específica.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fds), um ponteiro para uma estrutura NO_DISTRIB (NO_DISTRIB* d) e uma posição de próxima distribuição (int prox_pos).
// Retorno: A posição em que a nova distribuição foi inserida.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para escrita. A estrutura d deve conter dados válidos.
// Pós-condição: A nova distribuição é inserida no arquivo de distribuições na posição especificada.
int insertDistribuicao_bin(FILE* fds, NO_DISTRIB* d, int prox_pos);

// Descrição: Insere uma nova distribuição de disciplina no arquivo de distribuições de forma ordenada.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fds), um ponteiro para uma estrutura NO_DISTRIB (NO_DISTRIB* novaDistribuicao) e uma posição no arquivo (int pos).
// Retorno: A posição em que a nova distribuição foi inserida.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para escrita. A estrutura novaDistribuicao deve conter dados válidos.
// Pós-condição: A nova distribuição é inserida no arquivo de distribuições de forma ordenada.
int insertDistribuicao_Ordenado(FILE* fds, NO_DISTRIB* novaDistribuicao, int pos);

// Descrição: Lê dados de distribuições de um arquivo e insere no arquivo de distribuições.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fds) e um ponteiro para um arquivo contendo os dados de distribuições (FILE* f).
// Retorno: Nenhum.
// Pré-condição: Ambos os arquivos devem estar abertos e prontos para leitura.
// Pós-condição: As distribuições lidas do arquivo f são inseridas no arquivo de distribuições fds.
void read_arq_distrib(FILE* fds, FILE* f);

// Descrição: Realiza o cadastro de uma nova distribuição de disciplina.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fb).
// Retorno: Nenhum.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para escrita.
// Pós-condição: Uma nova distribuição é cadastrada no arquivo de distribuições.
void cadastro_distribuicao(FILE* fb);

// Descrição: Verifica se uma distribuição de disciplina já existe no arquivo de distribuições.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fb) e um ponteiro para uma estrutura NO_DISTRIB (NO_DISTRIB* distrib).
// Retorno: 1 se a distribuição já existe, 0 caso contrário.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para leitura. A estrutura distrib deve conter dados válidos.
// Pós-condição: Nenhum.
int RepeatOrNot_Distribuicao(FILE* fb, NO_DISTRIB* distrib);

// Descrição: Função para remover uma distribuição de disciplina com base no código da disciplina e no ano letivo.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fb).
// Retorno: Nenhum.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para escrita.
// Pós-condição: A distribuição de disciplina correspondente é removida do arquivo de distribuições.
void remover_distribuicao(FILE* fb);

// Descrição: Função auxiliar para listar todas as distribuições de disciplina no arquivo, de forma recursiva.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fb), uma posição na lista de distribuições (int pos_aux), e um ponteiro para uma estrutura NO_DISTRIB (NO_DISTRIB* aux).
// Retorno: Nenhum.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para leitura. pos_aux deve ser a posição inicial na lista de distribuições.
// Pós-condição: Todas as distribuições de disciplina são impressas na saída padrão.
void lista_distribuicoes_aux(FILE* fb, int pos_aux, NO_DISTRIB* aux);

// Descrição: Função para listar todas as distribuições de disciplina no arquivo, organizadas por cursos.
// Entrada: Um ponteiro para um arquivo de distribuições (FILE* fb).
// Retorno: Nenhum.
// Pré-condição: O arquivo de distribuições deve estar aberto e pronto para leitura.
// Pós-condição: Todas as distribuições de disciplina são listadas na saída padrão, organizadas por cursos.
void listar_TodasDistribuicoes(FILE *fb);

#endif // DISTRIBUICOES_H