#include<limits.h>
#include <stdio.h>
#include<stdlib.h>



void preencheVetor(Aluno* vetor,FILE* fileEntrada);
void esvaziarVetor(Aluno* vetor,Aluno* n);
void convertTxtParaBIN(FILE* fileEntrada , FILE* BIN);
void convertToChar(int num);
void sub(Aluno* vetor,int numeroArq,int* n );
void selecaoPorSub();