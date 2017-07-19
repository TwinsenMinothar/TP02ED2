#include<limits.h>
#include <stdio.h>
#include<stdlib.h>
#include "Aluno.h"

#define MAXTAM 20

void Refaz(int Esq, int Dir, Aluno *A);
void RefazPeloIndice(int Esq, int Dir, Aluno *A);
void Constroi(Aluno *A, int  *n);
void ConstroiPeloIndice(Aluno *A, int *n);
Aluno Min(Aluno *A);
Aluno RetiraMin(Aluno *A, int *n);
void AumentaChave(int i, double ChaveNova, Aluno *A);
void Insere(Aluno *x, Aluno *A, int *n);
void Imprime(Aluno *V, int *n);

