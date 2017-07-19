#include<limits.h>
#include <stdio.h>
#include<stdlib.h>
#include <iostream>

#include "HeapMin.h"

void swap(TipoItem* A , TipoIndice n){
  int i=1;
  TipoItem temp;
  for (i ; i<n-1 ; i=(i*2)-1){
    if(A[i].Chave > A[i+1].Chave && A[i].Indice == A[i+1].Indice){
      temp = A[i+1];
      A[i+1]=A[i];
      A[i]=temp;
      
    }
  }
}

void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ 
  TipoIndice i = Esq;
  int j;
  TipoItem x;
  j = (i * 2);
  x = A[i];
  while (j <= Dir) 
    { 
      if (j < Dir)
      { 
        if (A[j].Chave > A[j+1].Chave)
        j++;
      }
      if (x.Chave <= A[j].Chave){ goto L999;}
      A[i] = A[j];
      i = j; j = i * 2;
    }
  L999: A[i] = x;

} 
void RefazPeloIndice(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ 
  TipoIndice i = Esq;
  int j;
  TipoItem x;
  j = i * 2;
  x = A[i];
  while (j <= Dir) 
    { 
      if (j < Dir)
      { 
        if (A[j].Indice > A[j+1].Indice)
          j++;
      }
      if (x.Indice <= A[j].Indice){ goto L999;}
      A[i] = A[j];
      i = j; j = i * 2;
    }
  L999: A[i] = x;
} 

void Constroi(TipoItem *A, TipoIndice *n)
{ 
  TipoIndice Esq;
  Esq = *n / 2 + 1;
  while (Esq > 1) 
    {
      Esq--;
      Refaz(Esq, *n, A);
    }
} 

void ConstroiPeloIndice(TipoItem *A, TipoIndice *n)
{ 
  TipoIndice Esq;
  Esq = *n /2 + 1 ;

  while (Esq > 1) 
    { Esq--;
      RefazPeloIndice(Esq, *n, A);
    }
} 

TipoItem Min(TipoItem *A)
{ 
  return (A[1]); 
}

TipoItem RetiraMin(TipoItem *A, TipoIndice *n)
{ 
  TipoItem Minimo;
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

void AumentaChave(TipoIndice i, TipoChave ChaveNova, TipoItem *A)
{ 
  TipoItem x;
  if (ChaveNova < A[i].Chave) 
  { printf("Erro: ChaveNova menor que a chave atual\n");
    return;
  }
  A[i].Chave = ChaveNova;
  while (i > 1 && A[i / 2].Chave > A[i].Chave) 
    { 
      x = A[i / 2]; 
      A[i / 2] = A[i];  
      A[i] = x;
      i /= 2;
    }
}

void Insere(TipoItem *x, TipoItem *A, TipoIndice *n)
{
  (*n)++;
  A[*n] = *x;  A[*n].Chave = INT_MIN;
  AumentaChave(*n, x->Chave, A);
  Constroi(A,n);
  ConstroiPeloIndice(A,n);
}

void Imprime(TipoItem *V, TipoIndice *n)
{ 
  int i;
  for (i = 1; i <= *n; i++){
    printf("%f ", V[i].Chave);
  }
  putchar('\n');
}


