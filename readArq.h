#ifndef READARQ_H
#define READARQ_H

typedef struct{
    FILE* fc;
    FILE* fd;
    FILE* fp;
    FILE* fds;
}FBIN;

// Descrição: Abre os arquivos binários necessários para o programa, criando-os se não existirem.
// Entrada: Nenhuma.
// Retorno: Ponteiro para uma estrutura FBIN que contém os ponteiros para os arquivos abertos.
// Pré-condição: Nenhuma.
// Pós-condição: Os arquivos binários são abertos e a estrutura FBIN é retornada.
FBIN* open_files();

// Descrição: Fecha os arquivos binários abertos.
// Entrada: Ponteiro para a estrutura FBIN que contém os ponteiros para os arquivos abertos.
// Retorno: Nenhum.
// Pré-condição: Os arquivos binários devem estar abertos.
// Pós-condição: Todos os arquivos binários são fechados.
void fclose_bins(FBIN* fb);

#endif // READARQ_H