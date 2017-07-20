#ifndef ALUNOS_HPP_
#define ALUNOS_HPP_

#define TAMAREA 10

typedef struct{
    char inscricao[9];
    float nota;
    char notaf[6];
    char estado[3];
    char cidade[51];
    char curso[31];
    int fita;
    int tamanho;
}Aluno;

void insertion (Aluno*,int);

#endif
