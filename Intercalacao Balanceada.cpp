//
// Created by camillo on 06/07/17.
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define TAMAREA 100
#define F 20

using std::cout;
using std::cin;
using std::endl;

typedef int TipoApontador;
typedef int TipoChave;
typedef struct TipoItem {
    TipoChave Chave;
    /* Outros Componentes */
} TipoItem;
typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox, Ant;
} TipoCelula;
typedef struct TipoArea {
    TipoCelula Itens[TAMAREA];
    TipoApontador CelulasDisp, Primeiro, Ultimo;
    int NumCelOcupadas;
} TipoArea;
typedef TipoItem TipoRegistro;
typedef struct Aluno {
    char inscricao[9];
    char nota[6];
    double notaf;
    char estado[3];
    char cidade[51];
    char curso[30];
} Aluno;
// Memoria para 19 registros

int iniciaFitas();

int preencheMemoriaPrincipal();

int ordenarMemoriaPrincipal();

void imprimeMemoriaPrincipal();

int salvaNaFita();

FILE **fitas = new FILE *[F];
FILE *arq;
Aluno *memPrincipal = new Aluno[19];

int main() {
    arq = fopen("PROVAO.TXT", "r");
    iniciaFitas();
    preencheMemoriaPrincipal();
    ordenarMemoriaPrincipal();
    salvaNaFita();

    return 0;
}

int iniciaFitas() {
    char nome[15];
    for (int i = 1; i < F + 1; i++) {
        sprintf(nome, "fita%d.txt", i);
        fitas[i] = fopen(nome, "w");
    }
}

int preencheMemoriaPrincipal() {
    for (int i = 0; i < F-1; i++) {
        fscanf(arq, "%s %s %s %51c %30c", memPrincipal[i].inscricao, memPrincipal[i].nota, memPrincipal[i].estado,
               memPrincipal[i].cidade, memPrincipal[i].curso);
        memPrincipal[i].notaf = atof(memPrincipal[i].nota);
    }
    return 0;
}

bool compare(Aluno const &a, Aluno const &b) {
    return a.notaf > b.notaf;
}

int ordenarMemoriaPrincipal() {
    std::sort(memPrincipal,memPrincipal + 19,compare);
    return 0;
}

void imprimeMemoriaPrincipal(){
    for(int i = 0; i < F-1;i++){
        cout << memPrincipal[i].notaf << " ";
    }
}

int salvaNaFita(){
    FILE *fita;
    char nome[15];
    for(int i = 0;i<F-1;i++) {
        sprintf(nome, "fita%d.txt", i+1);
        fita = fopen(nome, "a");
        fprintf(fita,"%s %s %s %.50s %.30s\n", memPrincipal[i].inscricao, memPrincipal[i].nota, memPrincipal[i].estado,
                memPrincipal[i].cidade, memPrincipal[i].curso);
    }
}