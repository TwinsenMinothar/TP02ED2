#include "stdio.h"
#include "Aluno.h"
#include "Lista.h"

#ifndef FITA_HPP_
#define FITA_HPP_

#define N_FITAS 20 //quantidadade total de fitas

/*
    Estrutua da fita que usa uma lista por array 
    guardar os tamanhos de cada bloco
*/
typedef struct{
   int fitas;
   int contaFitas[10];
   bool estado[10];
}Fita;




void exemplo(int quantidade);
void intercala(int quantidade);
bool compare(Aluno &a, Aluno &b);
#endif
