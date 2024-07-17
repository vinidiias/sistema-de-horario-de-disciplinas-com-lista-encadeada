#include<stdio.h>
#include<stdlib.h>

#include "Headers\curso.h"
#include "Headers/disciplina.h"
#include "Headers/menu.h"
#include "Headers/distribuicoes.h"
#include "Headers/professor.h"
#include "Headers/readArq.h"

int main(){
    FILE* f;
    FBIN* fb = open_files();
    char str[30];
    int op, op1;
    do
    {
        imprime_opcoes();
        scanf("%d%*c",&op);
        system("cls");
        switch (op)
        {
            case 1:
                do
                {
                    printar_OpcoesCadastros();
                    scanf("%d%*c",&op1);
                    system("cls");

                    if(op1 == 1) cadastro_curso(fb->fc);
                    else if(op1 == 2) cadastro_disciplina(fb->fd, fb->fc);
                    else if(op1 == 3) cadastro_professor(fb->fp);
                    else if(op1 == 4) cadastro_distribuicao(fb->fds);

                } while (op1 != 5);
                break;
            case 2:
                do
                {
                    printa_OpcoesImprimir();
                    scanf("%d%*c",&op1);
                    system("cls");

                    if(op1 == 1) lista_cursos(fb->fc);
                    else if(op1 == 2) lista_Disciplinas(fb->fd);
                    else if(op1 == 3) lista_professores(fb->fp);
                    else if(op1 == 4) listar_distribuicoes(fb);
                    else if(op1 == 5) listar_TodasDistribuicoes(fb->fds);

                } while (op1 != 6);
                break;
            case 3:
                remover_distribuicao(fb->fds);
                break;
            case 4:
                printf("Digite o nome do arquivo: ");
                scanf("%[^\n]%*c", str);
                printf("\n");

                f = fopen(str, "r");

                if(f == NULL){
                    printf("Arquivo inexistente, retornando ao menu...\n");
                    break;
                }

                read_arq_curso(fb->fc, f);
                read_arq_disciplina(fb->fd, f);
                read_arq_prof(fb->fp, f);
                read_arq_distrib(fb->fds, f);

                fclose(f);
                break;
        default:
            break;
    }
    } while (op != 5);
    fclose_bins(fb);


    return 0;
}
