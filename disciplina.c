#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "disciplina.h"
#include "curso.h"
#include "cabecalho.h"

void write_no_disc(FILE* fd, NO_DISC* disc, int pos){
    fseek(fd, sizeof(cabecalho) + pos*sizeof(NO_DISC), SEEK_SET);
    fwrite(disc, sizeof(NO_DISC), 1, fd);
}

NO_DISC* read_no_disc(FILE* fd, int pos){
    NO_DISC* x = malloc(sizeof(NO_DISC));
    fseek(fd, sizeof(cabecalho) + pos*sizeof(NO_DISC), SEEK_SET);
    fread(x, sizeof(NO_DISC), 1, fd);
    return x;
}

void insertDisciplina(FILE* fc, NO_DISC* x){
    cabecalho* cab = le_cabecalho(fc);

    insertDisciplina_Ordenado(fc, x, cab->pos_cabeca);
    
    free(cab);
}

int insertDisciplina_bin(FILE* fc, NO_DISC* m, int prox_pos){
    cabecalho*cab = le_cabecalho(fc);
    int insert_pos;

    m->prox = prox_pos;

    if(cab->pos_livre == -1){
        insert_pos =cab->pos_topo;
        write_no_disc(fc, m,cab->pos_topo);
        cab->pos_topo++;
    }
    else{
        insert_pos =cab->pos_livre;
        NO_DISC* aux = read_no_disc(fc,cab->pos_livre);
        write_no_disc(fc, m,cab->pos_livre);    
        cab->pos_livre = aux->prox;
        free(aux);
    }

    if(cab->pos_cabeca == prox_pos) cab->pos_cabeca = insert_pos;
    escreve_cabecalho(fc,cab);
    free(cab);

    return insert_pos;
}

int insertDisciplina_Ordenado(FILE* fc, NO_DISC* novaDisciplina, int pos){
    if(pos == -1){
        int insert_pos = insertDisciplina_bin(fc, novaDisciplina, pos);
        return insert_pos;
    }
    else{
        NO_DISC* c = read_no_disc(fc, pos);

        if(c->disciplina.cod_curso > novaDisciplina->disciplina.cod_curso ||
            ((c->disciplina.cod_curso == novaDisciplina->disciplina.cod_curso) &&
            (c->disciplina.cod_disciplina > novaDisciplina->disciplina.cod_disciplina))){
                int insert_pos = insertDisciplina_bin(fc, novaDisciplina, pos);
                free(c);
                return insert_pos;
        }
        else{
            c->prox = insertDisciplina_Ordenado(fc, novaDisciplina, c->prox);
            write_no_disc(fc, c, pos);
            free(c);
            return pos;
        }
    }
}

/*int insertCourse_inOrder(FILE* fbCourse, FILE* fbMajor, Course* new_c, int pos){
        if(pos == -1){
            int insert_pos = insertCourse_bin(fbCourse, new_c, pos);
            return insert_pos;
        }
        else{
            Course* c = readCourse(fbCourse, pos);

            if(c->data_course.major_code > new_c->data_course.major_code ||
            ((c->data_course.major_code == new_c->data_course.major_code) &&
            (c->code > new_c->code))){
                int insert_pos = insertCourse_bin(fbCourse, new_c, pos);
                free(c);
                return insert_pos;
            }
            else{
                c->next = insertCourse_inOrder(fbCourse, fbMajor, new_c, c->next);
                writeCourse(fbCourse, c, pos);
                free(c);
                return pos;
            }
        }
}*/

void insertHead_disc(FILE* fd, int cod_disc, int codCurso, int serie, char* nome){
    cabecalho* cab = le_cabecalho(fd);
    NO_DISC x;

    strcpy(x.disciplina.nome, nome);
    x.disciplina.cod_disciplina = cod_disc;
    x.disciplina.cod_curso = codCurso;
    x.disciplina.serie = serie;
    x.prox = cab->pos_cabeca;

    if(RepetOrNot_Disciplina(fd, &x)){
        if(cab->pos_livre == -1){ //insere no topo
            write_no_disc(fd, &x, cab->pos_topo);
            cab->pos_cabeca = cab->pos_topo;
            cab->pos_topo++;
        }
        else { // insere nas posicoes livres
            NO_DISC* aux = read_no_disc(fd, cab->pos_livre);
            write_no_disc(fd, &x, cab->pos_livre);
            cab->pos_cabeca = cab->pos_livre;
            cab->pos_livre = aux->prox;
            free(aux);
        }
        escreve_cabecalho(fd, cab);
   } else printf("Disciplina ja existente\n");
    
    free(cab);
}

int RepetOrNot_Disciplina(FILE* fb, NO_DISC* disc){
    NO_DISC* aux = NULL;
    cabecalho* cab = le_cabecalho(fb);
    int pos_aux = cab->pos_cabeca;

    while(pos_aux != -1 && ((aux = read_no_disc(fb, pos_aux)) != NULL)
         && ((strcmp(aux->disciplina.nome, disc->disciplina.nome) != 0) && (aux->disciplina.cod_disciplina != disc->disciplina.cod_disciplina))){
            pos_aux = aux->prox;
            free(aux);
            aux = NULL;
         }
    free(aux);
    free(cab);
    return (pos_aux == -1);
}

void read_arq_disciplina(FILE* fb, FILE* f){
    char aux;
    NO_DISC disc; 

    fscanf(f, "%d;%[^;]%*c%d;%d%*c", &disc.disciplina.cod_disciplina, disc.disciplina.nome, &disc.disciplina.cod_curso, &disc.disciplina.serie);
    if(RepetOrNot_Disciplina(fb, &disc)) insertDisciplina(fb, &disc);
    else printf("Disciplina ja existente!\n");
    while(fscanf(f, "%c;", &aux) != EOF && aux == 'D'){
        fscanf(f, "%d;%[^;]%*c%d;%d%*c", &disc.disciplina.cod_disciplina, disc.disciplina.nome, &disc.disciplina.cod_curso, &disc.disciplina.serie);
         if(RepetOrNot_Disciplina(fb, &disc)) insertDisciplina(fb, &disc);
         else printf("Disciplina ja existente!\n");
    }
}

void cadastro_disciplina(FILE *fb, FILE* fc){
    int cod_disciplina, cod_curso, serie;
    char nome[50];
    NO_DISC* x = (NO_DISC*) malloc(sizeof(NO_DISC));

    printf("            **CADASTRO DE DISCIPLINA**            \n");
    printf("Digite o nome da disciplina: ");
    scanf("%[^\n]%*c", nome);
    printf("\n");

    printf("Digite o codigo da disciplina: ");
    scanf("%d%*c", &cod_disciplina);
    printf("\n");

    printf("Digite o codigo do curso ao qual a disciplina pertence: ");
    scanf("%d%*c", &cod_curso);
    printf("\n");

    if(!CursoDisponivel(fc, cod_curso)){
        printf("Curso nao existente para esta disciplina!\n");
        free(x);
        return;
    }

    printf("Digite a serie da disciplina: ");
    scanf("%d%*c", &serie);
    printf("\n");
    system("cls");

    strcpy(x->disciplina.nome, nome);
    x->disciplina.cod_disciplina = cod_disciplina;
    x->disciplina.cod_curso = cod_curso;
    x->disciplina.serie = serie;

    if(RepetOrNot_Disciplina(fb, x))
        insertDisciplina(fb, x);
    else printf("Disciplina ja existente!\n");
    free(x);
}

NO_DISC buscaDisciplina(FILE* fd, int cod_disciplina){
    NO_DISC aux;
    cabecalho* cab = le_cabecalho(fd);

    if(!(cab->pos_topo == 0)){
        fseek(fd, sizeof(cabecalho), SEEK_SET);
        while(fread(&aux, sizeof(NO_DISC), 1, fd) == 1){
            if(aux.disciplina.cod_disciplina == cod_disciplina)
                return aux;
        }
    }

    free(cab);

    return aux;
}

void lista_disciplinas_aux(FILE* fb, int pos_aux, NO_DISC* aux){
    if(pos_aux != -1 && ((aux = read_no_disc(fb, pos_aux)) != NULL)){
        printf("%-43s%-22d%-17d%-10d\n", aux->disciplina.nome, aux->disciplina.cod_disciplina, aux->disciplina.cod_curso, aux->disciplina.serie);
        lista_disciplinas_aux(fb, aux->prox, aux);
        free(aux);
        aux = NULL;
    }
}

void lista_Disciplinas(FILE* fb){
    NO_DISC* aux = NULL;
    cabecalho* cab = le_cabecalho(fb);
    int pos_aux = cab->pos_cabeca;

    printf("          **LISTA DE DISCIPLINAS DISPONIVEIS**         \n");
    printf("%-40s%-20s%-20s%-10s\n", "DISCIPLINA", "CODIGO", "CODIGO CURSO", "SERIE");

    lista_disciplinas_aux(fb, pos_aux, aux);
    /*while(pos_aux != -1 && ((aux = read_no_disc(fb, pos_aux)) != NULL)){
        printf("%-30s%-21d%-20d%-10s\n", aux->disciplina.nome, aux->disciplina.cod_disciplina, aux->disciplina.cod_curso, aux->disciplina.serie);
        pos_aux = aux->prox;
        free(aux);
        aux = NULL;
    }*/
    printf("\n");
    free(cab);
    free(aux);
}