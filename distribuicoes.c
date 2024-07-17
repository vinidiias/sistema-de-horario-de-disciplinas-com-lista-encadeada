#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "readArq.h"
#include "professor.h"
#include "disciplina.h"
#include "curso.h"
#include "distribuicoes.h"
#include "cabecalho.h"

void write_no_distrib(FILE *fd, NO_DISTRIB* distrib, int pos){
    fseek(fd, sizeof(cabecalho) + pos*sizeof(NO_DISTRIB), SEEK_SET);
    fwrite(distrib, sizeof(NO_DISTRIB), 1, fd);
}

NO_DISTRIB* read_no_distrib(FILE* fd, int pos){
    NO_DISTRIB* x = malloc(sizeof(NO_DISTRIB));
    fseek(fd, sizeof(cabecalho) + pos*sizeof(NO_DISTRIB), SEEK_SET);
    fread(x, sizeof(NO_DISTRIB), 1, fd);

    return x;
}

void insertDistribuicao(FILE* fds, NO_DISTRIB* x){
    cabecalho* cab = le_cabecalho(fds);

    insertDistribuicao_Ordenado(fds, x, cab->pos_cabeca);
    
    free(cab);
}

int insertDistribuicao_bin(FILE* fds, NO_DISTRIB* d, int prox_pos){
    cabecalho* cab = le_cabecalho(fds);
    int insert_pos;

    d->prox = prox_pos;

    if(cab->pos_livre == -1){
        insert_pos = cab->pos_topo;
        write_no_distrib(fds, d, cab->pos_topo);
        cab->pos_topo++;
    }
    else{
        insert_pos = cab->pos_livre;
        NO_DISTRIB* aux = read_no_distrib(fds, cab->pos_livre);
        write_no_distrib(fds, d, cab->pos_livre);    
        cab->pos_livre = aux->prox;
        free(aux);
    }

    if(cab->pos_cabeca == prox_pos) cab->pos_cabeca = insert_pos;
    escreve_cabecalho(fds, cab);
    free(cab);

    return insert_pos;
}

int insertDistribuicao_Ordenado(FILE* fds, NO_DISTRIB* novaDistribuicao, int pos){
    if(pos == -1){
        int insert_pos = insertDistribuicao_bin(fds, novaDistribuicao, pos);
        return insert_pos;
    }
    else{
        NO_DISTRIB* d = read_no_distrib(fds, pos);

        if(d->prof_disciplina.ano_letivo > novaDistribuicao->prof_disciplina.ano_letivo
        || ((d->prof_disciplina.ano_letivo == novaDistribuicao->prof_disciplina.ano_letivo)
        && (d->prof_disciplina.cod_disciplina > novaDistribuicao->prof_disciplina.cod_disciplina))){
            int insert_pos = insertDistribuicao_bin(fds, novaDistribuicao, pos);
            free(d);
            return insert_pos;
        }
        else{
            d->prox = insertDistribuicao_Ordenado(fds, novaDistribuicao, d->prox);
            write_no_distrib(fds, d, pos);
            free(d);
            return pos;
        }
    }
}

int RepeatOrNot_Distribuicao(FILE* fb, NO_DISTRIB* distrib){
    NO_DISTRIB* aux = NULL;
    cabecalho* cab = le_cabecalho(fb);
    int pos_aux = cab->pos_cabeca;

    while(pos_aux != -1 && ((aux = read_no_distrib(fb, pos_aux)) != NULL)
         && (((aux->prof_disciplina.ano_letivo == distrib->prof_disciplina.ano_letivo)
         && (aux->prof_disciplina.cod_prof == distrib->prof_disciplina.cod_prof || aux->prof_disciplina.cod_prof != distrib->prof_disciplina.cod_prof)
         && (aux->prof_disciplina.cod_disciplina != distrib->prof_disciplina.cod_disciplina))
         || (((aux->prof_disciplina.cod_disciplina == distrib->prof_disciplina.cod_disciplina)
         || (aux->prof_disciplina.cod_disciplina != distrib->prof_disciplina.cod_disciplina))
         && (aux->prof_disciplina.ano_letivo != distrib->prof_disciplina.ano_letivo)))){
            pos_aux = aux->prox;
            free(aux);
            aux = NULL;
         }
    free(aux);
    free(cab);
    return (pos_aux == -1);
}

void insertHead_distrib(FILE* fd, int cod_disciplina, int ano_letivo, int cod_prof){
    cabecalho* cab = le_cabecalho(fd);
    NO_DISTRIB x;

    x.prof_disciplina.cod_disciplina = cod_disciplina;
    x.prof_disciplina.ano_letivo = ano_letivo;
    x.prof_disciplina.cod_prof = cod_prof;
    x.prox = cab->pos_cabeca;

    if(RepeatOrNot_Distribuicao(fd, &x)){
        if(cab->pos_livre == -1){ //insere no topo
            write_no_distrib(fd, &x, cab->pos_topo);
            cab->pos_cabeca = cab->pos_topo;
            cab->pos_topo++;
        }
        else { // insere nas posicoes livres
            NO_DISTRIB* aux = read_no_distrib(fd, cab->pos_livre);
            write_no_distrib(fd, &x, cab->pos_livre);
            cab->pos_cabeca = cab->pos_livre;
            cab->pos_livre = aux->prox;
            free(aux);
        }
        escreve_cabecalho(fd, cab);
    }else printf("Nao eh possivel realizar essa distruibuicao!\n");
    
    free(cab);
}

void read_arq_distrib(FILE* fds, FILE* f){
    char aux;
    NO_DISTRIB prof;

    fscanf(f, "%d;%d;%d%*c", &prof.prof_disciplina.cod_disciplina, &prof.prof_disciplina.ano_letivo, &prof.prof_disciplina.cod_prof);
    if(RepeatOrNot_Distribuicao(fds, &prof)) insertDistribuicao(fds, &prof);
    else printf("Distribuicao invalida!\n");
    while(fscanf(f, "%c;", &aux) != EOF && aux == 'M'){
        fscanf(f, "%d;%d;%d%*c", &prof.prof_disciplina.cod_disciplina, &prof.prof_disciplina.ano_letivo, &prof.prof_disciplina.cod_prof);
        if(RepeatOrNot_Distribuicao(fds, &prof)) insertDistribuicao(fds, &prof);
            else printf("Distribuicao invalida!\n");
    }
}

void cadastro_distribuicao(FILE* fb){
    int cod_disciplina, ano_letivo, cod_prof;

    NO_DISTRIB *x = (NO_DISTRIB *) malloc(sizeof(NO_DISTRIB));

    printf("            **CADASTRO DE DISTRIBUICAO**            \n");
    printf("Digite o codigo da disciplina: ");
    scanf("%d%*c", &cod_disciplina);
    printf("\n");

    printf("Digite o ano letivo: ");
    scanf("%d%*c", &ano_letivo);
    printf("\n");

    printf("Digite o codigo do professor que ministrara a disciplina: ");
    scanf("%d%*c", &cod_prof);
    printf("\n");

    x->prof_disciplina.cod_disciplina = cod_disciplina;
    x->prof_disciplina.ano_letivo = ano_letivo;
    x->prof_disciplina.cod_prof = cod_prof;

    if(RepeatOrNot_Distribuicao(fb, x)) insertDistribuicao(fb, x);
    else printf("Distribuicao invalida!\n");
}

void remover_distribuicao_aux(FILE* fd, int cod_disciplina, int ano_letivo){
    cabecalho* cab = le_cabecalho(fd);
    int pos_aux = cab->pos_cabeca;
    int pos_ant = cab->pos_cabeca;
    NO_DISTRIB* aux = NULL;

    while(pos_aux != -1 && ((aux = read_no_distrib(fd, pos_aux)) != NULL)
         && (aux->prof_disciplina.cod_disciplina != cod_disciplina
         || ((aux->prof_disciplina.cod_disciplina == cod_disciplina) && aux->prof_disciplina.ano_letivo != ano_letivo))){
            pos_ant = pos_aux;
            pos_aux = aux->prox;
            free(aux);
            aux = NULL;
         }
    if(pos_aux != -1){
        if(pos_ant == pos_aux){
            cab->pos_cabeca = aux->prox;
        }
        else{
            NO_DISTRIB* ant = read_no_distrib(fd, pos_ant);
            ant->prox = aux->prox;
            write_no_distrib(fd, ant, pos_ant);
            free(ant);
        }
        aux->prox = cab->pos_livre;
        cab->pos_livre = pos_aux;
        write_no_distrib(fd, aux, pos_aux);
        escreve_cabecalho(fd, cab);
        free(aux);
    } else if(pos_aux == -1) printf("Disciplina nao encontrada!\n");
    free(cab);
}

void remover_distribuicao(FILE* fb){
    int cod_disciplina, ano_letivo;

    printf("            **REMOVER DISTRIBUICAO**            \n");
    printf("Digite o codigo da disciplina a ser removida: ");
    scanf("%d%*c", &cod_disciplina);
    printf("\n");

    printf("Digite o ano letivo correspondente: ");
    scanf("%d%*c", &ano_letivo);
    printf("\n");

    remover_distribuicao_aux(fb, cod_disciplina, ano_letivo);
}

void lista_distribuicoes_aux(FILE* fb, int pos_aux, NO_DISTRIB* aux){
    if(pos_aux != -1 && ((aux = read_no_distrib(fb, pos_aux)) != NULL)){
        printf("%-35d%-25d%-20d\n", aux->prof_disciplina.cod_disciplina, aux->prof_disciplina.cod_prof, aux->prof_disciplina.ano_letivo);
        lista_distribuicoes_aux(fb, aux->prox, aux);
        free(aux);
        aux = NULL;
    }
}

void listar_TodasDistribuicoes(FILE *fb){
    NO_DISTRIB* aux = NULL;
    cabecalho* cab = le_cabecalho(fb);
    int pos_aux = cab->pos_cabeca;
    printf("          **LISTA DE DISTRIBUICOES**         \n");
    printf("%-30s%-27s%-20s\n", "CODIGO DISCIPLINA", "PROFESSOR", "ANO LETIVO");

    lista_distribuicoes_aux(fb, pos_aux, aux);
    /*while(pos_aux != -1 && ((aux = read_no_curso(fp, pos_aux)) != NULL)){
        printf("%-30s%-21c%-10d\n", aux->curso.nome, aux->curso.area_curso, aux->curso.cod);
        pos_aux = aux->prox;
        free(aux);
        aux = NULL;
    }*/
    printf("\n");
    free(cab);
    free(aux);
}

void imprimeDistribuicoes(NO_DISTRIB* distrib, NO_CURSO curso, NO_DISC disciplina,  NO_PROF prof){
    printf("      %-27d%-35s%-12d%-43s%-20d%-15d%-20s\n", curso.curso.cod, curso.curso.nome, distrib->prof_disciplina.cod_disciplina,
                                                disciplina.disciplina.nome, distrib->prof_disciplina.ano_letivo, distrib->prof_disciplina.cod_prof, prof.prof.nome);
}

void listar_distribuicoes(FBIN *fb) {
    cabecalho* cab = le_cabecalho(fb->fds);
    NO_DISTRIB* aux;
    NO_DISC no_disc;
    NO_CURSO no_curso;
    NO_PROF no_professor;

    if (cab->pos_cabeca != -1) {
        fseek(fb->fc, sizeof(cabecalho), SEEK_SET);
        printf("          **LISTA DE DISTRIBUICOES ORGANIZADAS POR CURSOS**         \n");
        printf("%-40s%-20s%-20s%-40s%-15s%-23s%-20s\n", "CODIGO CURSO", "CURSO", "CODIGO DISCIPLINA", "DISCIPLINA", "ANO LETIVO", "CODIGO PROFESSOR", "PROFESSOR MINISTRANTE");

        while (fread(&no_curso, sizeof(NO_CURSO), 1, fb->fc) == 1) {
            aux = read_no_distrib(fb->fds, cab->pos_cabeca);
            while (aux != NULL) {
                no_disc = buscaDisciplina(fb->fd, aux->prof_disciplina.cod_disciplina);
                no_professor = buscaProfessor(fb->fp, aux->prof_disciplina.cod_prof);

                if (no_disc.disciplina.cod_curso == no_curso.curso.cod)
                    imprimeDistribuicoes(aux, no_curso, no_disc, no_professor);
                if (aux->prox != -1)
                    aux = read_no_distrib(fb->fds, aux->prox);
                else
                    aux = NULL; // Para sair do loop interno se aux->prox for -1
            }
        }
    } else {
        printf("Nao ha distribuicoes registradas!\n");
    }
    free(aux);  // Libera a última estrutura lida no arquivo fb->fds
}

