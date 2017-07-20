#include <cstring>
#include <iostream>
#include "limits.h"
#include "stdio.h"
#include <stdlib.h>
#include <algorithm>
#include <string>
#include "VariosCaminhos.h"
#include "AlunoFita.h"
//#include "contaDados.h"
using namespace std;

void criaBlocos(int quantidade, string nomeArq)
{
   FILE* arq;
   FILE** fitaEntrada = new FILE*[10];
   FILE** fitaSaida = new FILE*[10];
   string temp;
   int cont1 = 0, cont2 = 0, controle = 0;

   Aluno* aluno = new Aluno[quantidade];
   Aluno a;

   if ((arq = fopen(nomeArq.c_str(), "r")) == NULL)
   {
      cout << "Erro na abertura do arquivo" << endl;
      return;
   }
   
   for (int i = 0; i < 10; ++i)
   {
      temp = "FitaEntrada" + to_string(i) + ".bin";
      if ((fitaEntrada[i] = fopen(temp.c_str(), "wb")) == NULL)
      {
         cout << "Erro na abertura do arquivo" << endl;
         return;
      }
   }

   while(controle < quantidade)
   {
      fscanf(arq, "%s %s %s %51c %30c", a.inscricao, a.notaf, a.estado, a.cidade, a.curso);
      if(cont2 != 10)
      {
         strcpy(aluno[cont2].inscricao, a.inscricao);
         aluno[cont2].nota =  atof(a.notaf);
         strcpy(aluno[cont2].estado, a.estado);
         strcpy(aluno[cont2].cidade, a.cidade);
         strcpy(aluno[cont2].curso, a.curso);
         aluno[cont2].fita = cont1;
         cont2++;
      }
   // se cont2 chegar a 10 quer dizer que o vetor de alunos esta cheio
   // hora de gravar no arquivo de entrada
      else
      {
         insertion (aluno, 10);
      // as 10 fitas foram preenchidas, comeca entao o prreenchimento
      // da proxima coluna de blocos nos arquivos
         if(cont1 > 9)
         {
            cont1 = 0;
         }
         fwrite(&aluno, sizeof(aluno), 1, fitaEntrada[cont1]);
         cont2 = 0;
         cont1++;
      }
      controle++;    
   }
// fechar arquivo
   for (int i = 0; i < 10; ++i)
   {
      fclose(fitaEntrada[i]);
   }
   intercala(quantidade);
}

void intercala(int quantidade)
{
   FILE** fitaEntrada = new FILE*[10];
   FILE** fitaSaida = new FILE*[10];
   string nomeArq, temp;

   Fita f;
   Aluno* aluno = new Aluno[quantidade];
   Aluno* aux = new Aluno[quantidade];
   Aluno a;
   int controle = 0, cont = 0, contAux = 9;

   for (int i = 0; i < 10; ++i)
   {
      temp = "FitaEntrada" + to_string(i) + ".bin";
      if ((fitaEntrada[i] = fopen(temp.c_str(), "rb")) == NULL)
      {
         cout << "Erro na abertura do arquivo" << endl;
         return;
      }
      temp = "FitaSaida" + to_string(i) + ".bin";
      if ((fitaSaida[i] = fopen(temp.c_str(), "w+b")) == NULL)
      {
         cout << "Erro na abertura do arquivo" << endl;
         return;
      }
   }

   while(controle < quantidade)
   {
   // refazer arquivos de saida
      if(controle != 0)
      {
         for (int i = 0; i < 10; ++i)
         {
            temp = "FitaSaida" + to_string(i) + ".bin";
            if ((fitaSaida[i] = fopen(temp.c_str(), "w+b")) == NULL)
            {
               cout << "Erro na abertura do arquivo" << endl;
               return;
            }
         }
      }

   // pegando 10 primeiros valores
      for (int j = 0; j < 10; j++)
      {
      // le do arquivo
         fread(aluno, sizeof(aluno), 1, fitaEntrada[j]);
      // recebe a primeira posicao dos 10 blocos
         aux[j] = aluno[0];
         cout << aux[j].fita << aux[j].nota << endl;
         controle++;
      }

   // intercalando
      for (int i = 0; i < 10; i++)
      {     
      // ordena o bloco
         sort(aluno, aluno + 10, compare);
      // recebe as informacoes do menor elemento
         a = aux[0];
      // recebe a informacao de qual arquivo o elemento veio
         f.fitas = a.fita;
      // incrementa o vetor de posicoes
         f.contaFitas[f.fitas]++;
      // atualiza a informacao passando o numero de qual arquivo o elemento ira
         a.fita = i;
      // escreve as novas informacoes no arquivo de saida
         fwrite(&a, sizeof(a), 1, fitaSaida[i]);
      // se o bloco de onde o numero veio for menor que 9, faz uma nova leitura neste bloco
         if(f.contaFitas[f.fitas] <= cont)
         {
            fread(&a, sizeof(a), 1, fitaEntrada[f.fitas]);
         // obter o tamanho dos blocos
            contAux++;
         }
      // se todos os elementos do bloco foram lidos, o bloco recebe o estado falso e os programas nao voltaram nele
         else
         {
            f.estado[f.fitas] = false;
            f.contaFitas[f.fitas] = 0;
         }
         controle ++;
      }
      cont = contAux;
      contAux = 0;

   // refazer arquivos de entrada
      for (int i = 0; i < 10; ++i)
      {
         temp = "FitaEntrada" + to_string(i) + ".bin";
         if ((fitaEntrada[i] = fopen(temp.c_str(), "w+b")) == NULL)
         {
            cout << "Erro na abertura do arquivo" << endl;
            return;
         }
      }

   // fazer todos os valores de f.estado serem true
      for (int i = 0; i < cont; i++)
      {
         f.estado[i] = true;
      }

   // pegando 10 primeiros valores
      for (int j = 0; j < 10; j++)
      {
      // le do arquivo
         fread(aluno, sizeof(aluno), 1, fitaEntrada[j]);
      // recebe a primeira posicao dos 10 blocos
         aux[j] = aluno[0];
         controle++;
      }

   // intercalando
      for (int i = 0; i < 10; i++)
      {     
      // ordena o bloco
         sort(aluno, aluno + 10, compare);
      // recebe as informacoes do menor elemento
         a = aux[0];
      // recebe a informacao de qual arquivo o elemento veio
         f.fitas = a.fita;
      // incrementa o vetor de posicoes
         f.contaFitas[f.fitas]++;
      // atualiza a informacao passando o numero de qual arquivo o elemento ira
         a.fita = i;
      // escreve as novas informacoes no arquivo de saida
         fwrite(&a, sizeof(a), 1, fitaEntrada[i]);
      // se o bloco de onde o numero veio for menor que 9, faz uma nova leitura neste bloco
         if(f.contaFitas[f.fitas] <= cont)
         {
            fread(&a, sizeof(a), 1, fitaSaida[f.fitas]);
            contAux++;
         }
      // se todos os elementos do bloco foram lidos, o bloco recebe o estado falso e os programas nao voltaram nele
         else
         {
            f.estado[f.fitas] = false;
         }
         controle ++;
      }
      cont = contAux;
      contAux = 0;
   // fazer todos os valores de f.estado serem true
      for (int i = 0; i < cont; i++)
      {
         f.estado[i] = true;
      }
   }
// fechar fitas
   for (int i = 0; i < 10; ++i)
   {
      fclose(fitaEntrada[i]);
      fclose(fitaSaida[i]);
   }
}

bool compare(Aluno &a, Aluno &b)
{
   return a.nota > b.nota;
}