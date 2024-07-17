#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include<stdio.h>

typedef struct{
    char nome[51];
    int cod_curso;
    int serie;
    int cod_disciplina;
}DISCIPLINA;

typedef struct{
    DISCIPLINA disciplina;
    int prox;
} NO_DISC;

// Descrição: Lê uma estrutura NO_DISC de uma posição específica em um arquivo binário.
// Entrada: Um ponteiro para um arquivo (FILE* fd) e uma posição no arquivo (int pos).
// Retorno: Um ponteiro para a estrutura NO_DISC lida do arquivo.
// Pré-condição: O arquivo deve estar aberto e pronto para leitura.
// Pós-condição: A estrutura NO_DISC é lida do arquivo e um ponteiro para ela é retornado.

void read_arq_disciplina(FILE* fb, FILE* f);

// Descrição: Escreve uma estrutura NO_DISC em uma posição específica em um arquivo binário.
// Entrada: Um ponteiro para um arquivo (FILE* fd), um ponteiro para a estrutura NO_DISC (NO_DISC* disc) e uma posição no arquivo (int pos).
// Retorno: Nenhum.
// Pré-condição: O arquivo deve estar aberto e pronto para escrita.
// Pós-condição: A estrutura NO_DISC é escrita na posição especificada do arquivo.
void write_no_disc(FILE* fd, NO_DISC* disc, int pos);

// Descrição: Lê informações de disciplinas de um arquivo de texto e as insere no arquivo binário se não existirem previamente.
// Entrada: Ponteiros para um arquivo binário (FILE* fb) e um arquivo de texto (FILE* f).
// Retorno: Nenhum.
// Pré-condição: Ambos os arquivos devem estar abertos e prontos para leitura/escrita.
// Pós-condição: As disciplinas do arquivo de texto são inseridas no arquivo binário se não existirem previamente.
NO_DISC* read_no_disc(FILE* fd, int pos);

// Descrição: Insere uma disciplina ordenadamente no arquivo binário.
// Entrada: Um ponteiro para um arquivo (FILE* fc) e um ponteiro para a estrutura NO_DISC (NO_DISC* x).
// Retorno: Nenhum.
// Pré-condição: O arquivo deve estar aberto e pronto para escrita.
// Pós-condição: A disciplina é inserida no arquivo de forma ordenada.

void insertDisciplina(FILE* fc, NO_DISC* x);

// Descrição: Insere uma nova disciplina no início do arquivo, se ela não existir previamente.
// Entrada: Um ponteiro para um arquivo (FILE* fd), código da disciplina (int cod_disc), código do curso (int codCurso), série da disciplina (int serie) e nome da disciplina (char* nome).
// Retorno: Nenhum.
// Pré-condição: O arquivo deve estar aberto e pronto para escrita.
// Pós-condição: A disciplina é inserida no início do arquivo se ela não existir previamente.
void insertHead_disc(FILE* fd, int cod_disc, int cod_curso, int serie, char* nome);

// Descrição: Insere uma disciplina no arquivo binário.
// Entrada: Um ponteiro para um arquivo (FILE* fc), um ponteiro para a estrutura NO_DISC (NO_DISC* m) e uma posição (int prox_pos).
// Retorno: A posição onde a disciplina foi inserida.
// Pré-condição: O arquivo deve estar aberto e pronto para escrita.
// Pós-condição: A disciplina é inserida no arquivo e a posição de inserção é retornada.
int insertDisciplina_bin(FILE* fc, NO_DISC* m, int prox_pos);

// Descrição: Insere uma disciplina de forma ordenada no arquivo binário.
// Entrada: Um ponteiro para um arquivo (FILE* fc), um ponteiro para a estrutura NO_DISC (NO_DISC* novaDisciplina) e uma posição (int pos).
// Retorno: A posição onde a disciplina foi inserida.
// Pré-condição: O arquivo deve estar aberto e pronto para escrita.
// Pós-condição: A disciplina é inserida no arquivo de forma ordenada e a posição de inserção é retornada.
int insertDisciplina_Ordenado(FILE* fc, NO_DISC* novaDisciplina, int pos);

// Descrição: Solicita ao usuário informações para cadastrar uma nova disciplina e a insere no arquivo binário se não existir previamente.
// Entrada: Um ponteiro para um arquivo (FILE* fb).
// Retorno: Nenhum.
// Pré-condição: O arquivo deve estar aberto e pronto para escrita.
// Pós-condição: A disciplina fornecida pelo usuário é inserida no arquivo se não existir previamente.
void cadastro_disciplina(FILE *fb, FILE* fc);

// Descrição: Verifica se uma disciplina já existe no arquivo.
// Entrada: Um ponteiro para um arquivo (FILE* fb) e um ponteiro para a estrutura NO_DISC (NO_DISC* disc).
// Retorno: 1 se a disciplina não existe, 0 se a disciplina já existe.
// Pré-condição: O arquivo deve estar aberto e pronto para leitura.
// Pós-condição: O status de existência da disciplina é retornado.
int RepetOrNot_Disciplina(FILE* fb, NO_DISC* curso);

// Descrição: Lista todas as disciplinas no arquivo.
// Entrada: Um ponteiro para um arquivo (FILE* fb).
// Retorno: Nenhum.
// Pré-condição: O arquivo deve estar aberto e pronto para leitura.
// Pós-condição: As disciplinas são listadas na saída padrão usando a função lista_disciplinas_aux.
void lista_Disciplinas(FILE* fb);

// Descrição: Função auxiliar para listar as disciplinas no arquivo de forma recursiva.
// Entrada: Um ponteiro para um arquivo (FILE* fb), uma posição auxiliar (int pos_aux) e um ponteiro para a estrutura NO_DISC (NO_DISC* aux).
// Retorno: Nenhum.
// Pré-condição: O arquivo deve estar aberto e pronto para leitura. pos_aux deve ser a posição inicial para começar a lista.
// Pós-condição: As disciplinas são listadas na saída padrão.
void lista_disciplinas_aux(FILE* fb, int pos_aux, NO_DISC* aux);

// Descrição: Busca uma disciplina no arquivo com base no código da disciplina.
// Entrada: Um ponteiro para um arquivo (FILE* fd) e o código da disciplina (int cod_disciplina).
// Retorno: A estrutura NO_DISC da disciplina encontrada.
// Pré-condição: O arquivo deve estar aberto e pronto para leitura.
// Pós-condição: A estrutura da disciplina é retornada.
NO_DISC buscaDisciplina(FILE* fd, int cod_disciplina);

#endif // DISCIPLINA_H