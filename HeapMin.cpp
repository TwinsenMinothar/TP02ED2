#include<limits.h>
#include <stdio.h>
#include<stdlib.h>
#include <iostream>

#include "HeapMin.h"

void swap(Aluno* A , int n){
  int i=1;
  Aluno temp;
  for (i ; i<n-1 ; i=(i*2)-1){
    if(A[i].nota > A[i+1].nota && A[i].fita == A[i+1].fita){
      temp = A[i+1];
      A[i+1]=A[i];
      A[i]=temp;
      
    }
  }
}

void Refaz(int Esq, int Dir, Aluno *A)
{ 
  int i = Esq;
  int j;
  Aluno x;
  j = (i * 2);
  x = A[i];
  while (j <= Dir) 
    { 
      if (j < Dir)
      { 
        if (A[j].nota > A[j+1].nota)
        j++;
      }
      if (x.nota <= A[j].nota){ goto L999;}
      A[i] = A[j];
      i = j; j = i * 2;
    }
  L999: A[i] = x;

} 
void RefazPeloIndice(int Esq, int Dir, Aluno *A)
{ 
  int i = Esq;
  int j;
  Aluno x;
  j = i * 2;
  x = A[i];
  while (j <= Dir) 
    { 
      if (j < Dir)
      { 
        if (A[j].fita > A[j+1].fita)
          j++;
      }
      if (x.fita <= A[j].fita){ goto L999;}
      A[i] = A[j];
      i = j; j = i * 2;
    }
  L999: A[i] = x;
} 

void Constroi(Aluno *A, int *n)
{ 
  int Esq;
  Esq = *n / 2 + 1;
  while (Esq > 1) 
    {
      Esq--;
      Refaz(Esq, *n, A);
    }
} 

void ConstroiPeloIndice(Aluno *A, int *n)
{ 
  int Esq;
  Esq = *n /2 + 1 ;

  while (Esq > 1) 
    { Esq--;
      RefazPeloIndice(Esq, *n, A);
    }
} 

Aluno Min(Aluno *A)
{ 
  return (A[1]); 
}

Aluno RetiraMin(Aluno *A, int *n)
{ 
  Aluno Minimo;
  if (*n < 1) 
  printf("Erro: heap vazio\n");
  else { Minimo = A[1];  A[1] = A[*n];  (*n)--;
        //  Refaz(1, *n, A);
        //  RefazPeloIndice(1,*n,A);
       }
  Constroi(A,n);
  ConstroiPeloIndice(A,n);
  return Minimo;
}

void AumentaChave(int i, double ChaveNova, Aluno *A)
{ 
  Aluno x;
  if (ChaveNova < A[i].nota) 
  { printf("Erro: ChaveNova menor que a chave atual\n");
    return;
  }
  A[i].nota = ChaveNova;
  while (i > 1 && A[i / 2].nota > A[i].nota) 
    { 
      x = A[i / 2]; 
      A[i / 2] = A[i];  
      A[i] = x;
      i /= 2;
    }
}

void Insere(Aluno *x, Aluno *A, int *n)
{
  (*n)++;
  A[*n] = *x;  A[*n].nota = INT_MIN;
  AumentaChave(*n, x->nota, A);
  Constroi(A,n);
  ConstroiPeloIndice(A,n);
}

void Imprime(Aluno *V, int *n)
{ 
  int i;
  for (i = 1; i <= *n; i++){
    printf("%f ", V[i].nota);
  }
  putchar('\n');
}


