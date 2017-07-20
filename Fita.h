#include "stdio.h"
#include "AlunoFita.h"
#include <string>

using namespace std;

#ifndef FITA_H
#define FITA_H

typedef struct{
   int fitas;
   int contaFitas[10];
   bool estado[10];
}Fita;

void criaBlocos(int quantidade, string nomeArq);
void intercala(int quantidade);
bool compare(Aluno &a, Aluno &b);
#endif
