#include<limits.h>
#include <stdio.h>
#include<stdlib.h>



void preencheVetor(TipoItem* vetor,FILE* fileEntrada);
void esvaziarVetor(TipoItem* vetor,TipoIndice* n);
void convertTxtParaBIN(FILE* fileEntrada , FILE* BIN);
void convertToChar(int num);
void sub(TipoItem* vetor,int numeroArq,TipoIndice* n );
void selecaoPorSub();