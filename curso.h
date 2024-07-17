#ifndef CURSO_H
#define CURSO_

typedef struct no1{
    char nome[51];
    int area_curso;
    int cod;
}CURSO;

typedef struct{
    CURSO curso;
    int prox;
}NO_CURSO;

// Descrição: escreve informacoes de um NOCURSO contendo informacoes de um curso no arquivo binario
// Entrada: Um ponteiro para arquivo binario (FILE* fb), um ponteiro com a informacao do curso (NO_CURSO* course) e um posicao da insercao (int pos)
// pre condicao: arquivo binario deve ser um arquivo binario nao nulo e course
//               deve conter as informacoes do curso
// pos condicao: informacoes do curso escritos no arquivo
void write_no_curso(FILE *fb, NO_CURSO* course, int pos);

// le uma informacao de um curso no arquivo binario
// pre condiccao: arquivo binario nao nulo e pos ser uma posicao valida no arq bin
// pos condicao: NO_CURSO contendo as informacoes lidas no arq binario
NO_CURSO* read_no_curso(FILE *fb, int pos);

// Descrição: Esta função insere um novo curso no início do arquivo.
// Entrada: Um ponteiro para um arquivo binário (FILE *fb), uma string contendo o nome do curso (char* nome), um caractere representando a área do curso (char area), e um número de código para o curso (int cod).
// Retorno: Sem retorno.
// Pré-condição: O ponteiro do arquivo (fb) não deve ser nulo. Os parâmetros nome, area, e cod devem representar valores válidos.
// Pós-condição: O novo curso é inserido no início do arquivo de cursos.
void insertHead_curso(FILE *fb, char*nome, char area, int cod);

// Descrição: Esta função lê um registro de curso de uma posição específica em um arquivo binário.
// Entrada: Um ponteiro para um arquivo binário (FILE *fb) e uma posição no arquivo (int pos).
// Retorno: Um ponteiro para um novo registro de curso lido do arquivo.
// Pré-condição: O ponteiro do arquivo (fb) não deve ser nulo.
// Pós-condição: Um novo registro de curso é alocado e preenchido com os dados lidos do arquivo e retornado.
void read_arq_curso(FILE* fb, FILE* f);

// Descrição: Esta função permite o usuário cadastrar um novo curso e o insere no arquivo de cursos, verificando se o curso já existe no arquivo.
// Entrada: Um ponteiro para um arquivo binário (FILE *fb).
// Retorno: Sem retorno.
// Pré-condição: O ponteiro do arquivo (fb) não deve ser nulo.
// Pós-condição: Um novo curso é cadastrado no arquivo de cursos, se ele não existir previamente no arquivo. 
//               Se o curso já existir, uma mensagem informando sobre a duplicidade é exibida, e nenhum novo 
//               curso é inserido no arquivo.
void cadastro_curso(FILE* fb);

// Descrição: Esta função imprime a lista de todos os cursos no arquivo.
// Entrada: Um ponteiro para um arquivo binário (FILE *fb).
// Retorno: Sem retorno.
// Pré-condição: O ponteiro do arquivo (fb) não deve ser nulo.
// Pós-condição: Lista os cursos contidos no arquivo.
void lista_cursos(FILE* fb);

// Descrição: Esta função auxiliar imprime a lista de cursos a partir de uma posição específica no arquivo.
// Entrada: Um ponteiro para um arquivo binário (FILE *fb), uma posição no arquivo (int pos_aux), e um ponteiro para um registro de curso (NO_CURSO* aux).
// Retorno: Sem retorno.
// Pré-condição: O ponteiro do arquivo (fb) não deve ser nulo. A posição pos_aux deve ser válida.
// Pós-condição: Lista os cursos a partir da posição especificada no arquivo.
void lista_cursos_aux(FILE* fb, int pos_aux, NO_CURSO* aux);

// Descrição: Esta função insere um novo curso no arquivo binário de forma ordenada.
// Entrada: Um ponteiro para um arquivo binário (FILE *fc) e um ponteiro para um novo registro de curso (NO_CURSO* x).
// Retorno: Sem retorno.
// Pré-condição: O ponteiro do arquivo (fc) não deve ser nulo. O ponteiro para o registro de curso (x) deve apontar para uma estrutura de curso válida.
// Pós-condição: O novo curso é inserido no arquivo de forma ordenada.
void insertCurso(FILE* fc, NO_CURSO* x);

// Descrição: Esta função insere um novo curso de forma binária em uma posição específica no arquivo.
// Entrada: Um ponteiro para um arquivo binário (FILE *fc), um ponteiro para um registro de curso (NO_CURSO* m), e a próxima posição no arquivo (int prox_pos).
// Retorno: A posição onde o novo curso foi inserido.
// Pré-condição: O ponteiro do arquivo (fc) não deve ser nulo. O ponteiro para o registro de curso (m) deve apontar para uma estrutura de curso válida.
// Pós-condição: O novo curso é inserido no arquivo na posição especificada e a posição de inserção é retornada.
int insertCurso_bin(FILE* fc, NO_CURSO* m, int next_pos);

// Descrição: Esta função insere um novo curso de forma ordenada no arquivo.
// Entrada: Um ponteiro para um arquivo binário (FILE *fc), um ponteiro para um novo registro de curso (NO_CURSO* novoCurso), e uma posição no arquivo (int pos).
// Retorno: A posição onde o novo curso foi inserido.
// Pré-condição: O ponteiro do arquivo (fc) não deve ser nulo. O ponteiro para o registro de curso (novoCurso) deve apontar para uma estrutura de curso válida.
// Pós-condição: O novo curso é inserido de forma ordenada no arquivo e a posição de inserção é retornada.
int insertCurso_Ordenado(FILE* fc, NO_CURSO* novoCurso, int pos);

// Descrição: Esta função verifica se um curso já existe no arquivo.
// Entrada: Um ponteiro para um arquivo binário (FILE *fb) e um ponteiro para um registro de curso (NO_CURSO* curso).
// Retorno: Retorna 1 se o curso já existe, 0 caso contrário.
// Pré-condição: O ponteiro do arquivo (fb) não deve ser nulo. O ponteiro para o registro de curso (curso) deve apontar para uma estrutura de curso válida.
// Pós-condição: Nenhuma.
int RepetOrNot_Curso(FILE* fb, NO_CURSO* curso);

// Descrição: Esta função verifica se existe um curso com o codigo do paramentro e o retorna.
// Entrada: Um ponteiro para um arq bin (FILE* fc) e um codigo de referencia (int cod_curso).
// Retorno: Retorna o curso encontrado caso exista.
// Pré-condição: O ponteiro do arquivo (fc) não deve ser nulo.
// Pós-condição: Nenhuma.
NO_CURSO buscaCurso(FILE* fc, int cod_curso);

// Descrição: Esta função verifica se existe um curso com o codigo de referencia (int cod_curso).
// Entrada: Um ponteiro para um arq bin (FILE* fc) e um codigo de referencia (int cod_curso).
// Retorno: Retorna 1 caso exista o curso com o codigo senao 0.
// Pré-condição: O ponteiro do arquivo (fc) não deve ser nulo.
// Pós-condição: Nenhuma.
int CursoDisponivel(FILE* fc, int cod_curso);


#endif // CURSO_H