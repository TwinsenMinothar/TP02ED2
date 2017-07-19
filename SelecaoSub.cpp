#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include "HeapMin.h"
#include "SelecaoSub.h"

using namespace std;
#define TAM 10
#define NUM_BLOCK 20

TipoIndice N = TAM;

void convertTxtParaBIN(FILE* fileEntrada , FILE* BIN){
    TipoItem Item;
    char enter ; 
    rewind(fileEntrada);
    while (fscanf(fileEntrada,"%ld %f %2s %50[^\n] %30[^\n] %[\n]",&Item.Inscricao,&Item.Chave,Item.Estado,Item.Cidade,Item.Curso,enter)!=EOF){
        fwrite(&Item,sizeof(Item),1,BIN);
    }
    fclose(fileEntrada);

} 
void preencheVetor(TipoItem* vetor,FILE* fileEntrada){
    int i=1;
    for(i;i<=TAM;i++){
        fread(&vetor[i],sizeof(*vetor),1,fileEntrada);
    }
    
    Constroi(vetor,&N);
    Imprime(vetor,&N);
}

void convertToChar(int num,char* buff){
    snprintf(buff, sizeof(buff), "%d", num);
    
}

void esvaziarVetor(TipoItem* vetor,TipoIndice* n){
    
    char block[50],bin[5],num[33];
    TipoItem Minimo;
    
    strcpy(block,"Bloco");
    strcpy(bin,".bin");
    FILE* fileSaida;

    int i,tamanho = *n;

    for(i;i<tamanho;i++){
        
        Minimo = RetiraMin(vetor,n);
        Imprime(vetor,n);
        convertToChar(Minimo.Indice,num);
        strcat(block,num);
        strcat(block,bin);
        fileSaida = fopen(block, "ab");
        strcpy(block,"Bloco");
        fwrite(&Minimo,sizeof(Minimo),1,fileSaida);
        fflush(stdout);
        fclose(fileSaida);
    }

}

void sub(TipoItem* vetor,int numeroArq,TipoIndice* n ){
    int indice = 1;
    TipoItem Minimo;
    TipoItem Item;
    Item.Indice = indice;

    char block[50];
    char txt[5];
    char num[33];
    
    strcpy(block,"Bloco");
    strcpy(txt,".bin");

    FILE* fileEntrada = fopen("PROVAO.bin","rb");
    preencheVetor(vetor,fileEntrada);

    FILE* fileSaida = fopen("Bloco1.bin","ab");
    Minimo = RetiraMin(vetor,n);
    fwrite(&Minimo,sizeof(Minimo),1,fileSaida);
    fclose(fileSaida);

    while (fread(&Item,sizeof(Item),1,fileEntrada)==1){
        
         if(Item.Chave < Minimo.Chave){
            if(indice == NUM_BLOCK){
                indice = 1;
            }
            Item.Indice = indice + 1;
            Insere(&Item,vetor,n);
          
         }

         if(Item.Chave >= Minimo.Chave){
            Item.Indice = indice;
            Insere(&Item,vetor,n);
            
         }
        
         if(Min(vetor).Indice > indice){
             indice++;
         }
         
         Minimo = RetiraMin(vetor,n);
         convertToChar(Minimo.Indice,num);
    
         strcat(block,num);
         strcat(block,txt);
         fileSaida = fopen(block, "ab");
         strcpy(block,"Bloco");
         fwrite(&Minimo,sizeof(Minimo),1,fileSaida);
         fflush(stdout);
         fclose(fileSaida);
    }
    esvaziarVetor(vetor,&N);
    fclose(fileEntrada);
}
void selecaoPorSub(){
    TipoVetor vetor;
    sub(vetor,NUM_BLOCK,&N );
}