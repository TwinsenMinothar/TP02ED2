#include<limits.h>
#include <stdio.h>
#include<stdlib.h>
#include <iostream>
#include  <time.h>

#include "HeapMin.h"
#include "SelecaoSub.h"
#include "QuickExterno.hpp"


using namespace std;

void readProvao(FILE* fileProvao){

    Aluno A;;

    fseek(fileProvao,0,SEEK_SET);

    string white = " ";

    while (fread(&A,sizeof(Aluno),1,fileProvao)){
       cout<<A.inscricao<<endl;
       cout<<A.nota<<white;
       cout<<A.estado<<white;
       cout<<A.cidade<<white;
       cout<<A.curso<<white;
    }

}
    
int metodo = 0 , quantidade =0 , situacao =0 , op =0;
clock_t c1, c2;
double tempo = 0;

int main(int argc, char* argv[]){
    
    //inicializando as variaveis globais 
    if(argc == 4){
        metodo = atoi(argv [1]);
        quantidade = atoi(argv [3]);
        situacao = atoi(argv [2]);
    }

    else if (argc == 5){
        metodo = atoi(argv [1]);
        quantidade =atoi(argv[3]);
        situacao = atoi(argv[2]);
        op = atoi(argv [4]);
    }

    else{
		cout << "ERRO. Entrada: ./Pesquisa <método> <quantidade> <situação> <chave> -P" << endl;
	}


    //INTERCALACAO BALANCEADA DE VARIOS CAMINHOS - 2F FITAS 
    if(metodo == 1)
    {
        cout <<"INTERCALACAO BALANCEADA DE VARIOS CAMINHOS"<<endl;
        if(situacao ==1){
            cout<<"open arq 1"<<endl;
        }
        else if(situacao ==2){
            cout<<"open arq 2"<<endl;
        }
        else if(situacao ==3){
            cout<<"open arq 3"<<endl;
        }
        else{
            cout<<"Arquivo nao encontrado"<<endl;
            return 0;
        }


    }
    
    //INTERCALACAO BALANCEADA DE VARIOS CAMINHOS - 2F FITAS - SELECAO POR SUB.
    if(metodo == 2)
    {
        cout <<"INTERCALACAO BALANCEADA DE VARIOS CAMINHOS - SELECAO POR SUB"<<endl;

        if(situacao ==1){
            cout<<"open arq 1"<<endl;
        }
        else if(situacao ==2){
            cout<<"open arq 2"<<endl;
        }
        else if(situacao ==3){
            cout<<"open arq 3"<<endl;
        }
        else{
            cout<<"Arquivo nao encontrado"<<endl;
            return 0;
        }
    }

    //INTERCALACAO BALANCEADA DE VARIOS CAMINHOS - F + 1 FITAS - SELECAO POR SUB.
    if(metodo == 3)
    {
        cout <<"INTERCALACAO BALANCEADA DE VARIOS CAMINHOS - F + 1 FITAS - SELECAO POR SUB."<<endl;

        if(situacao ==1){
            cout<<"open arq 1"<<endl;
        }
        else if(situacao ==2){
            cout<<"open arq 2"<<endl;
        }
        else if(situacao ==3){
            cout<<"open arq 3"<<endl;
        }
        else{
            cout<<"Arquivo nao encontrado"<<endl;
            return 0;
        }
    }

    //QUICK SORT EXTERNO
    if(metodo == 4)
    {
        FILE*  ArqLi;
        FILE* ArqEi;
        FILE* ArqLEs;

        if(situacao == 1){
            ArqLi = fopen("PROVAO.bin","r+b");
            ArqEi = fopen("PROVAO.bin","r+b");
            ArqLEs = fopen("PROVAO.bin","r+b");
            
        }
        else if (situacao == 2){
            ArqLi = fopen("PROVAO.bin","r+b");
            ArqEi = fopen("PROVAO.bin","r+b");
            ArqLEs = fopen("PROVAO.bin","r+b");

        }
        else if (situacao == 3){
            ArqLi = fopen("PROVAO.bin","r+b");
            ArqEi = fopen("PROVAO.bin","r+b");
            ArqLEs = fopen("PROVAO.bin","r+b");

        }

        else{
            cout<<"Arquivo nao encontrado"<<endl;
            return 0;
        }
    
        Aluno A;
        c1 = clock();

        QuicksortExterno(&ArqLi, &ArqEi, &ArqLEs, 1 , quantidade);

        c2 = clock();
        tempo = (1.0*(c2 - c1)) / CLOCKS_PER_SEC;
        fflush(ArqLi);
        fclose(ArqEi);
        fclose(ArqLEs);
        fseek(ArqLi,0,SEEK_SET);

        while (fread(&A,sizeof(Aluno),1,ArqLi)){
            cout<<A.nota<<endl;
         }

        fclose(ArqLi);
        
    }

    return 0;  
}
