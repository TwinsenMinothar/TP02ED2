#ifndef ALUNOS_HPP_
#define ALUNOS_HPP_

#define TAMAREA 50

typedef struct{
    long inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
    int fita;
}Aluno;

void insertion (Aluno*,int);

#endif
