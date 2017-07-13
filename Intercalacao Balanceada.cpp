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

int salvaNaFita(int indice);

int passaFitaSaida();

FILE **fitas = new FILE *[F];

typedef struct f {
    FILE *fita;
    int cont;
} Fita;

FILE *arq;
Aluno *memPrincipal = new Aluno[19];

int main() {
    int indice = 1;
    arq = fopen("PROVAO.TXT", "r");
    iniciaFitas();
    while (preencheMemoriaPrincipal()) {
        ordenarMemoriaPrincipal();
        salvaNaFita(indice++);
        if (indice == 20)
            indice = 1;
    }
    fclose(arq);
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
    for (int i = 0; i < F - 1; i++) {
        if (feof(arq)) {
            cout << "EOF" << endl;
            return 0;
        }
        fscanf(arq, "%s %s %s %51c %30c", memPrincipal[i].inscricao, memPrincipal[i].nota, memPrincipal[i].estado,
               memPrincipal[i].cidade, memPrincipal[i].curso);
        memPrincipal[i].notaf = atof(memPrincipal[i].nota);
    }
    return 1;
}

bool compare(Aluno const &a, Aluno const &b) {
    return a.notaf > b.notaf;
}

int ordenarMemoriaPrincipal() {
    std::sort(memPrincipal, memPrincipal + 19, compare);
    return 0;
}

void imprimeMemoriaPrincipal() {
    for (int i = 0; i < F - 1; i++) {
        cout << memPrincipal[i].notaf << " ";
    }
}

int salvaNaFita(int indice) {
    FILE *fita;
    char nome[15];
    sprintf(nome, "fita%d.txt", indice);
    fita = fopen(nome, "a");
    for (int i = 0; i < F - 1; i++) {
        fprintf(fita, "%s %s %s %.50s %.30s", memPrincipal[i].inscricao, memPrincipal[i].nota, memPrincipal[i].estado,
                memPrincipal[i].cidade, memPrincipal[i].curso);
    }
    fputc('\n', fita);
    fclose(fita);
    return 0;
}

int passaFitaSaida() {

}