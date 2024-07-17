#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "professor.h"
#include "cabecalho.h"

void write_no_prof(FILE *fp, NO_PROF* prof, int pos){
    fseek(fp, sizeof(cabecalho) + pos*sizeof(NO_PROF), SEEK_SET);
    fwrite(prof, sizeof(NO_PROF), 1, fp);
}

NO_PROF* read_no_prof(FILE *fp, int pos){
    NO_PROF* x = malloc(sizeof(NO_PROF));
    fseek(fp, sizeof(cabecalho) + pos*sizeof(NO_PROF), SEEK_SET);
    fread(x, sizeof(NO_PROF), 1, fp);

    return x;
}

void insertProfessor(FILE* fp, NO_PROF* x){
    cabecalho* cab = le_cabecalho(fp);

    insertProfessor_Ordenado(fp, x, cab->pos_cabeca);
    
    free(cab);
}

int insertProfessor_bin(FILE* fp, NO_PROF* p, int prox_pos){
    cabecalho* cab = le_cabecalho(fp);
    int insert_pos;

    p->prox = prox_pos;

    if(cab->pos_livre == -1){
        insert_pos = cab->pos_topo;
        write_no_prof(fp, p, cab->pos_topo);
        cab->pos_topo++;
    }
    else{
        insert_pos = cab->pos_livre;
        NO_PROF* aux = read_no_prof(fp, cab->pos_livre);
        write_no_prof(fp, p, cab->pos_livre);    
        cab->pos_livre = aux->prox;
        free(aux);
    }

    if(cab->pos_cabeca == prox_pos) cab->pos_cabeca = insert_pos;
    escreve_cabecalho(fp, cab);
    free(cab);

    return insert_pos;
}

int insertProfessor_Ordenado(FILE* fp, NO_PROF* novoProf, int pos){
    if(pos == -1){
        int insert_pos = insertProfessor_bin(fp, novoProf, pos);
        return insert_pos;
    }
    else{
        NO_PROF* p = read_no_prof(fp, pos);

        if(p->prof.cod > novoProf->prof.cod){
            int insert_pos = insertProfessor_bin(fp, novoProf, pos);
            free(p);
            return insert_pos;
        }
        else{
            p->prox = insertProfessor_Ordenado(fp, novoProf, p->prox);
            write_no_prof(fp, p, pos);
            free(p);
            return pos;
        }
    }
}

void insertHead_prof(FILE *fp, char* nome, int cod){
    cabecalho* cab = le_cabecalho(fp);
    NO_PROF x;

    strcpy(x.prof.nome, nome);
    x.prof.cod = cod;
    x.prox = cab->pos_cabeca;
    
    if(RepetOrNot_Professor(fp, &x)){
        if(cab->pos_livre == -1){ //insere no topo
            write_no_prof(fp, &x, cab->pos_topo);
            cab->pos_cabeca = cab->pos_topo;
            cab->pos_topo++;
        }
        else { // insere nas posicoes livres
            NO_PROF* aux = read_no_prof(fp, cab->pos_livre);
            write_no_prof(fp, &x, cab->pos_livre);
            cab->pos_cabeca = cab->pos_livre;
            cab->pos_livre = aux->prox;
            free(aux);
        }
        escreve_cabecalho(fp, cab);
    }else printf("Professor ja existente\n");
    
    free(cab);
}

int RepetOrNot_Professor(FILE* fb, NO_PROF* disc){
    NO_PROF* aux = NULL;
    cabecalho* cab = le_cabecalho(fb);
    int pos_aux = cab->pos_cabeca;

    while(pos_aux != -1 && ((aux = read_no_prof(fb, pos_aux)) != NULL)
         && ((strcmp(aux->prof.nome, disc->prof.nome) != 0) && (aux->prof.cod != disc->prof.cod))){
            pos_aux = aux->prox;
            free(aux);
            aux = NULL;
         }
    free(aux);
    free(cab);
    return (pos_aux == -1);
}

NO_PROF buscaProfessor(FILE* fp, int cod_professor){
    NO_PROF aux;
    cabecalho* cab = le_cabecalho(fp);

    if(!(cab->pos_topo == 0)){
        fseek(fp, sizeof(cabecalho), SEEK_SET);
        
        while(fread(&aux, sizeof(NO_PROF), 1, fp) == 1){
            if(aux.prof.cod == cod_professor)
                return aux;
        }
    }
    
    free(cab);

    return aux;
}

void read_arq_prof(FILE* fb, FILE* f){
    char aux;
    NO_PROF prof;
    
    fscanf(f, "%d;%[^\n]%*c", &prof.prof.cod, prof.prof.nome);
    if(RepetOrNot_Professor(fb, &prof)) insertProfessor(fb, &prof);
    else printf("Professor ja cadastrado!\n");
    while(fscanf(f, "%c;", &aux) != EOF && aux == 'P'){
        fscanf(f, "%d;%[^\n]%*c", &prof.prof.cod, prof.prof.nome);
        if(RepetOrNot_Professor(fb, &prof)) insertProfessor(fb, &prof);
        else printf("Professor ja cadastrado!\n");
    }
}

void cadastro_professor(FILE* fb){
    int cod_prof;
    char nome[50];
    NO_PROF* x = (NO_PROF*) malloc(sizeof(NO_PROF));

    printf("            **CADASTRO DE PROFESSOR**            \n");
    printf("Digite o nome do professor: ");
    scanf("%[^\n]%*c", nome);
    printf("\n");

    printf("Digite o codigo do professor: ");
    scanf("%d%*c", &cod_prof);
    printf("\n");
    system("cls");

    strcpy(x->prof.nome, nome);
    x->prof.cod = cod_prof;

    if(RepetOrNot_Professor(fb, x)) insertProfessor(fb, x);
    else printf("Professor ja cadastrado!\n");
}

void lista_professores_aux(FILE* fp, int pos_aux, NO_PROF* aux){
    if(pos_aux != -1 && ((aux = read_no_prof(fp, pos_aux)) != NULL)){
        printf("%-30s%-21d\n", aux->prof.nome, aux->prof.cod);
        lista_professores_aux(fp, aux->prox, aux);
        free(aux);
        aux = NULL;
    }
}

void lista_professores(FILE* fp){
    NO_PROF* aux = NULL;
    cabecalho* cab = le_cabecalho(fp);
    int pos_aux = cab->pos_cabeca;
    printf("          **LISTA DE PROFESSORES**         \n");
    printf("%-28s%-20s\n", "NOME", "CODIGO");

    lista_professores_aux(fp, pos_aux, aux);
    /*while(pos_aux != -1 && ((aux = read_no_curso(fp, pos_aux)) != NULL)){
        printf("%-30s%-21c%-10d\n", aux->curso.nome, aux->curso.area_curso, aux->curso.cod);
        pos_aux = aux->prox;
        free(aux);
        aux = NULL;
    }*/
    printf("\n");
    free(aux);
}
