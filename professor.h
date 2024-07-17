#ifndef PROFESSOR_H
#define PROFESSOR_H

#include<stdio.h>

typedef struct no3{
    char nome[51];
    int cod;
}PROFESSOR;

typedef struct{
    PROFESSOR prof;
    int prox;
}NO_PROF;

// Descrição: Escreve um registro de professor no arquivo binário na posição especificada.
// Entrada: FILE *fp - ponteiro para o arquivo binário, NO_PROF* prof - ponteiro para o registro de professor, int pos - posição no arquivo.
// Retorno: Nenhum.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: O registro de professor é escrito no arquivo na posição especificada.
void write_no_prof(FILE *fp, NO_PROF* prof, int pos);

// Descrição: Lê um registro de professor do arquivo binário na posição especificada.
// Entrada: FILE *fp - ponteiro para o arquivo binário, int pos - posição no arquivo.
// Retorno: Ponteiro para o registro de professor lido do arquivo binário.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Nenhuma.
NO_PROF* read_no_prof(FILE *fp, int pos);

// Descrição: Insere um novo registro de professor no arquivo binário.
// Entrada: FILE* fp - ponteiro para o arquivo binário, NO_PROF* x - ponteiro para o registro de professor.
// Retorno: Nenhum.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Um novo registro de professor é inserido no arquivo binário.
void insertProfessor(FILE* fp, NO_PROF* x);

// Descrição: Insere um novo registro de professor no arquivo binário de forma ordenada.
// Entrada: FILE* fp - ponteiro para o arquivo binário, NO_PROF* p - ponteiro para o registro de professor, int prox_pos - posição no arquivo do próximo registro.
// Retorno: Posição no arquivo onde o novo registro foi inserido.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Um novo registro de professor é inserido no arquivo binário na posição ordenada.
int insertProfessor_bin(FILE* fp, NO_PROF* p, int prox_pos);

// Descrição: Insere um registro de professor no arquivo binário de forma ordenada.
// Entrada: FILE *fp - ponteiro para o arquivo binário, NO_PROF* novoProf - ponteiro para o registro de professor, int pos - posição atual no arquivo.
// Retorno: Posição em que o registro de professor foi inserido.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: O registro de professor é inserido no arquivo, mantendo a ordem dos registros.

int insertProfessor_Ordenado(FILE* fp, NO_PROF* novoProf, int pos);

// Descrição: Insere um registro de professor no início do arquivo binário.
// Entrada: FILE *fp - ponteiro para o arquivo binário, char* nome - nome do professor, int cod - código do professor.
// Retorno: Nenhum.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: O registro de professor é inserido no início do arquivo, mantendo a ordem dos registros.
void insertHead_prof(FILE *fp, char* nome, int cod);

// Descrição: Verifica se um registro de professor já existe no arquivo binário.
// Entrada: FILE *fb - ponteiro para o arquivo binário, NO_PROF* disc - ponteiro para o registro de professor.
// Retorno: 1 se o registro não existe, 0 se o registro já existe.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Nenhuma.
int RepetOrNot_Professor(FILE* fb, NO_PROF* disc);

// Descrição: Lê um arquivo de texto contendo dados de professores e insere esses dados no arquivo binário.
// Entrada: FILE* fb - ponteiro para o arquivo binário, FILE* f - ponteiro para o arquivo de texto.
// Retorno: Nenhum.
// Pré-condição: O arquivo binário deve estar aberto e ser válido. O arquivo de texto deve estar aberto e ser válido.
// Pós-condição: Os registros de professores do arquivo de texto são inseridos no arquivo binário.
void read_arq_prof(FILE* fb, FILE* f);

// Descrição: Realiza o cadastro de um novo professor no arquivo binário.
// Entrada: FILE* fb - ponteiro para o arquivo binário.
// Retorno: Nenhum.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Um novo registro de professor é inserido no arquivo binário.
void cadastro_professor(FILE* fb);

// Descrição: Lista todos os professores presentes no arquivo binário.
// Entrada: FILE* fp - ponteiro para o arquivo binário.
// Retorno: Nenhum.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Nenhuma.
void lista_professores(FILE* fp);

// Descrição: Função auxiliar para listar os professores no arquivo binário de forma recursiva.
// Entrada: FILE* fp - ponteiro para o arquivo binário, int pos_aux - posição atual no arquivo, NO_PROF* aux - ponteiro para o registro de professor.
// Retorno: Nenhum.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Nenhuma.
void lista_professores_aux(FILE* fp, int pos_aux, NO_PROF* aux);

// Descrição: Busca um registro de professor no arquivo binário pelo código do professor.
// Entrada: FILE *fp - ponteiro para o arquivo binário, int cod_professor - código do professor a ser buscado.
// Retorno: Registro de professor encontrado no arquivo.
// Pré-condição: O arquivo binário deve estar aberto e ser válido.
// Pós-condição: Nenhuma.
NO_PROF buscaProfessor(FILE* fp, int cod_professor);

#endif // PROFESSOR_H