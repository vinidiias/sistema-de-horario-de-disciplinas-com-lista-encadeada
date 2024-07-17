#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "curso.h"
#include "cabecalho.h"

void write_no_curso(FILE *fb, NO_CURSO* course, int pos){
    fseek(fb, sizeof(cabecalho) + pos*sizeof(NO_CURSO), SEEK_SET);
    fwrite(course, sizeof(NO_CURSO), 1, fb);
}

NO_CURSO* read_no_curso(FILE *fb, int pos){
    NO_CURSO* x = malloc(sizeof(NO_CURSO));
    fseek(fb, sizeof(cabecalho) + pos*sizeof(NO_CURSO), SEEK_SET);
    fread(x, sizeof(NO_CURSO), 1, fb);
    return x;
}

void insertCurso(FILE* fc, NO_CURSO* x){
    cabecalho* cab = le_cabecalho(fc);

    insertCurso_Ordenado(fc, x, cab->pos_cabeca);
    
    free(cab);
}

int insertCurso_bin(FILE* fc, NO_CURSO* m, int prox_pos){
    cabecalho* cab = le_cabecalho(fc);
    int insert_pos;

    m->prox = prox_pos;

    if(cab->pos_livre == -1){
        insert_pos = cab->pos_topo;
        write_no_curso(fc, m, cab->pos_topo);
        cab->pos_topo++;
    }
    else{
        insert_pos = cab->pos_livre;
        NO_CURSO* aux = read_no_curso(fc, cab->pos_livre);
        write_no_curso(fc, m, cab->pos_livre);    
        cab->pos_livre = aux->prox;
        free(aux);
    }

    if(cab->pos_cabeca == prox_pos) cab->pos_cabeca = insert_pos;
    escreve_cabecalho(fc, cab);
    free(cab);

    return insert_pos;
}

int insertCurso_Ordenado(FILE* fc, NO_CURSO* novoCurso, int pos){
    if(pos == -1){
        int insert_pos = insertCurso_bin(fc, novoCurso, pos);
        return insert_pos;
    }
    else{
        NO_CURSO* m = read_no_curso(fc, pos);

        if(m->curso.cod > novoCurso->curso.cod){
            int insert_pos = insertCurso_bin(fc, novoCurso, pos);
            free(m);
            return insert_pos;
        }
        else{
            m->prox = insertCurso_Ordenado(fc, novoCurso, m->prox);
            write_no_curso(fc, m, pos);
            free(m);
            return pos;
        }
    }
}

void insertHead_curso(FILE *fb, char*nome, char area, int cod){
    cabecalho* cab = le_cabecalho(fb);
    NO_CURSO x;

    strcpy(x.curso.nome, nome);
    x.curso.area_curso = area;
    x.curso.cod = cod;
    x.prox = cab->pos_cabeca;

    if(RepetOrNot_Curso(fb, &x)){
        if(cab->pos_livre == -1){ //insere no topo
            write_no_curso(fb, &x, cab->pos_topo);
            cab->pos_cabeca = cab->pos_topo;
            cab->pos_topo++;
        }
        else { // insere nas posicoes livres
            NO_CURSO* aux = read_no_curso(fb, cab->pos_livre);
            write_no_curso(fb, &x, cab->pos_livre);
            cab->pos_cabeca = cab->pos_livre;
            cab->pos_livre = aux->prox;
            free(aux);
        }
        escreve_cabecalho(fb, cab);
    } else printf("Curso ja existente\n");
    
    free(cab);
}

int CursoDisponivel(FILE* fc, int cod_curso){
    NO_CURSO aux;
    cabecalho* cab = le_cabecalho(fc);

    if(!(cab->pos_topo == 0)){
        fseek(fc, sizeof(cabecalho), SEEK_SET);
        while(fread(&aux, sizeof(NO_CURSO), 1, fc) == 1){
            if(aux.curso.cod == cod_curso){
                free(cab);
                return 1;
            }
                
        }
    }

    free(cab);
    
    return 0;
}

NO_CURSO buscaCurso(FILE* fc, int cod_curso){
    NO_CURSO aux;
    cabecalho* cab = le_cabecalho(fc);

    if(!(cab->pos_topo == 0)){
        fseek(fc, sizeof(cabecalho), SEEK_SET);
        while(fread(&aux, sizeof(NO_CURSO), 1, fc) == 1){
            if(aux.curso.cod == cod_curso)
                return aux;
        }
    }

    free(cab);
    
    return aux;
}

int RepetOrNot_Curso(FILE* fb, NO_CURSO* curso){
    NO_CURSO* aux = NULL;
    cabecalho* cab = le_cabecalho(fb);
    int pos_aux = cab->pos_cabeca;

    while(pos_aux != -1 && ((aux = read_no_curso(fb, pos_aux)) != NULL)
         && ((strcmp(aux->curso.nome, curso->curso.nome) != 0) && (aux->curso.cod != curso->curso.cod))){
            pos_aux = aux->prox;
            free(aux);
            aux = NULL;
         }
    free(aux);
    free(cab);
    return (pos_aux == -1);
}

void lista_cursos_aux(FILE* fb, int pos_aux, NO_CURSO* aux){
    if(pos_aux != -1 && ((aux = read_no_curso(fb, pos_aux)) != NULL)){
        printf("%-30s%-21c%-10d\n", aux->curso.nome, aux->curso.area_curso, aux->curso.cod);
        lista_cursos_aux(fb, aux->prox, aux);
        free(aux);
        aux = NULL;
    }
}

void lista_cursos(FILE* fb){
    NO_CURSO* aux = NULL;
    cabecalho* cab = le_cabecalho(fb);
    int pos_aux = cab->pos_cabeca;
    printf("          **LISTA DE CURSOS DISPONIVEIS**         \n");
    printf("%-28s%-20s%-10s\n", "CURSO", "AREA", "CODIGO");

    lista_cursos_aux(fb, pos_aux, aux);
    /*while(pos_aux != -1 && ((aux = read_no_curso(fb, pos_aux)) != NULL)){
        printf("%-30s%-21c%-10d\n", aux->curso.nome, aux->curso.area_curso, aux->curso.cod);
        pos_aux = aux->prox;
        free(aux);
        aux = NULL;
    }*/
    printf("\n");
    free(cab);
    free(aux);
}

void read_arq_curso(FILE* fb, FILE* f){
    char aux;
    NO_CURSO curso;

    while(fscanf(f, "%c;", &aux) != EOF && aux == 'C'){
        fscanf(f, "%d;%[^;]%*c%c%*c", &curso.curso.cod, curso.curso.nome, &curso.curso.area_curso);
        if(RepetOrNot_Curso(fb, &curso)) insertCurso(fb, &curso);
        else printf("Curso ja existente\n");
    }
}

void cadastro_curso(FILE* fb){
    int cod;
    char nome[50], area;
    NO_CURSO* x = (NO_CURSO*) malloc(sizeof(NO_CURSO));

    printf("            **CADASTRO DE CURSO**            \n");
    printf("Digite o nome do curso: ");
    scanf("%[^\n]%*c", nome);
    printf("\n");

    printf("Digite a area do curso (E -> Exatas, H -> Humanas, B -> Biologicas): ");
    scanf("%c%*c", &area);
    printf("\n");

    printf("Digite o codigo do curso: ");
    scanf("%d%*c", &cod);
    printf("\n");
    system("cls");

    strcpy(x->curso.nome, nome);
    x->curso.area_curso = area;
    x->curso.cod = cod;

    if(RepetOrNot_Curso(fb, x)) insertCurso(fb, x);
    else printf("Curso ja existente\n");
    
    free(x);
}