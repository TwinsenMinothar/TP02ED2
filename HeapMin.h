#include<limits.h>
#include <stdio.h>
#include<stdlib.h>

#define MAXTAM 20


typedef float TipoChave;
typedef struct TipoItem {
  TipoChave Chave;
  TipoChave Indice;
  long int  Inscricao;
  char Estado [3];
  char Cidade [51];
  char Curso [31];
} TipoItem;
typedef int TipoIndice;
typedef TipoItem TipoVetor[MAXTAM + 1];

void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
void RefazPeloIndice(TipoIndice Esq, TipoIndice Dir, TipoItem *A);
void Constroi(TipoItem *A, TipoIndice *n);
void ConstroiPeloIndice(TipoItem *A, TipoIndice *n);
TipoItem Min(TipoItem *A);
TipoItem RetiraMin(TipoItem *A, TipoIndice *n);
void AumentaChave(TipoIndice i, TipoChave ChaveNova, TipoItem *A);
void Insere(TipoItem *x, TipoItem *A, TipoIndice *n);
void Imprime(TipoItem *V, TipoIndice *n);

