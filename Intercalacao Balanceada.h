//
// Created by camillo on 19/07/17.
//

#ifndef IBVCF1_INTERCALACAO_BALANCEADA_H
#define IBVCF1_INTERCALACAO_BALANCEADA_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <chrono>

int iniciaFitas();

int preencheMemoriaPrincipal(FILE *arq);

int ordenarMemoriaPrincipal(int fitasAbertas);

void imprimeMemoriaPrincipal();

int salvaNaFita(int indice);

int passaFitaSaida();

int fechaFitas();

bool fitaChegouAoFimDaLinha(int fitaUsada);

int fitaAindaTemLinha();

bool fitasEOF();

int lePrimeiroElementoDeCadaLinha();

int printNaFita(int fita, int inicio, int final);

int redistribuirBlocos(int fitaOrigem);

int fitasAbertas();

int iniciaf1(int quantidade,char flag[]);

void resetaMemoriaPrincipal();

void imprimeArquivo(int indice);


#endif //IBVCF1_INTERCALACAO_BALANCEADA_H
