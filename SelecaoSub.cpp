#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include "HeapMin.h"
#include "SelecaoSub.h"

using namespace std;
#define TAM 10 // Tamanho do meu heap
#define NUM_BLOCK 20 // numero de blocos ordenados que serao gerados

int N = TAM;

void convertTxtParaBIN(FILE* fileEntrada , FILE* BIN){// funcao que converte um arquivo TXT para binario
    Aluno Item;
    char enter ; 
    rewind(fileEntrada);
    while (fscanf(fileEntrada,"%ld %f %2s %50[^\n] %30[^\n] %[\n]",&Item.inscricao,&Item.nota,Item.estado,Item.cidade,Item.curso,enter)!=EOF){
        fwrite(&Item,sizeof(Item),1,BIN);
    }
    fclose(fileEntrada);

} 
void preencheVetor(Aluno* vetor,FILE* fileEntrada){// inicializa meu heap , preenchendo com os dados do arquivo
    int i=1;
    for(i;i<=TAM;i++){
        fread(&vetor[i],sizeof(*vetor),1,fileEntrada);
    }
    
    Constroi(vetor,&N);
    Imprime(vetor,&N);
}

void convertToChar(int num,char* buff){// funcao que converte um numero inteiro para char 
    snprintf(buff, sizeof(buff), "%d", num);
    
}

void esvaziarVetor(Aluno* vetor,int* n){//esvazia meu heap
    
    char block[50],bin[5],num[33];
    Aluno Minimo;
    
    strcpy(block,"Bloco");
    strcpy(bin,".bin");
    FILE* fileSaida;

    int i,tamanho = *n;

    for(i;i<tamanho;i++){
        
        Minimo = RetiraMin(vetor,n);
        Imprime(vetor,n);
        convertToChar(Minimo.nota,num);
        strcat(block,num);
        strcat(block,bin);
        fileSaida = fopen(block, "ab");
        strcpy(block,"Bloco");
        fwrite(&Minimo,sizeof(Minimo),1,fileSaida);
        fflush(stdout);
        fclose(fileSaida);
    }

}

void sub(Aluno* vetor,int numeroArq,int* n ){ // executa a selecao por substituicao 
    int fita = 1;
    Aluno Minimo;
    Aluno Item;
    Item.fita = fita;

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
        
         if(Item.nota < Minimo.nota){
            if(fita == NUM_BLOCK){
                fita = 1;
            }
            Item.fita = fita + 1;
            Insere(&Item,vetor,n);
          
         }

         if(Item.nota >= Minimo.nota){
            Item.fita = fita;
            Insere(&Item,vetor,n);
            
         }
        
         if(Min(vetor).fita > fita){
             fita++;
         }
         
         Minimo = RetiraMin(vetor,n);
         convertToChar(Minimo.fita,num);
    
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
void selecaoPorSub(){// delega as funcoes 
    Aluno vetor[TAM+1];
    sub(vetor,NUM_BLOCK,&N );
}