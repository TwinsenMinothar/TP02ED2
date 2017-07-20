//
// Created by camillo on 06/07/17.
// Last Version

#include "Intercalacao Balanceada.h"

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
    int fita;
} Aluno;

FILE **fitas = new FILE *[F - 1];

typedef struct f {
    FILE *fita;
    int cont;
} Fita;

FILE *arq;
Aluno *memPrincipal = new Aluno[19];
unsigned int comparacoesf, escritasf, leiturasf;

int iniciaf1(int quantidade, char flag[]) {
    auto started = std::chrono::high_resolution_clock::now();
    int indice = 0;
    comparacoesf = 0;
    escritasf = 0;
    leiturasf = 0;
    int qt = 0;
    arq = fopen("PROVAO.TXT", "r");
    iniciaFitas();
    while (preencheMemoriaPrincipal(arq)) {
        ordenarMemoriaPrincipal(19);
        salvaNaFita(indice++);
        if (indice == 19)
            indice = 0;
        if (quantidade != -1) {
            qt += 19;
            if (qt >= quantidade)
                break;
        }
    }
    fclose(arq);
    fechaFitas();
    passaFitaSaida();
    fechaFitas();
    redistribuirBlocos(19);
    fechaFitas();
    passaFitaSaida();
    fechaFitas();
    redistribuirBlocos(19);
    fechaFitas();
    passaFitaSaida();
    fechaFitas();
    redistribuirBlocos(19);
    fechaFitas();
    passaFitaSaida();
    fechaFitas();
    auto done = std::chrono::high_resolution_clock::now();
    float tempo = std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
    if (strcmp(flag, "-P") == 0)
        imprimeArquivo(19);
    cout << "Comparacoes: " << comparacoesf << " Escritas: " << escritasf << " Leituras: " << leiturasf << " Tempo: "
         << tempo << endl;
    return 0;
}

int iniciaFitas() {
    char nome[15];
    for (int i = 0; i < F; i++) {
        sprintf(nome, "fita%d.txt", i + 1);
        fitas[i] = fopen(nome, "w");
    }
    return 0;
}

int fechaFitas() {
    for (int i = 0; i < F; i++)
        fclose(fitas[i]);
    return 0;
}

int preencheMemoriaPrincipal(FILE *arq) {
    for (int i = 0; i < F - 1; i++) {
        if (feof(arq) && arq != NULL) {
            return 0;
        }
        leiturasf++;
        fscanf(arq, "%s %s %s %51c %30c", memPrincipal[i].inscricao, memPrincipal[i].nota, memPrincipal[i].estado,
               memPrincipal[i].cidade, memPrincipal[i].curso);
        memPrincipal[i].notaf = atof(memPrincipal[i].nota);
    }
    return 1;
}

bool compare(Aluno const &a, Aluno const &b) {
    comparacoesf++;
    return a.notaf > b.notaf;
}

int ordenarMemoriaPrincipal(int fitasAbertas) {
    //int tamanho = sizeof(memPrincipal) / sizeof(memPrincipal[0]);
    std::sort(memPrincipal, memPrincipal + fitasAbertas, compare);
    return 0;
}

void imprimeMemoriaPrincipal() {
    for (int i = 0; i < F - 1; i++) {
        cout << memPrincipal[i].inscricao << memPrincipal[i].nota << memPrincipal[i].estado << memPrincipal[i].cidade
             << memPrincipal[i].curso << endl;
    }
}

int salvaNaFita(int indice) {
    for (int i = 0; i < F - 1; i++) {
        escritasf++;
        fprintf(fitas[indice], "%s %s %s %.50s %.30s", memPrincipal[i].inscricao, memPrincipal[i].nota,
                memPrincipal[i].estado,
                memPrincipal[i].cidade, memPrincipal[i].curso);
    }
    fputc('\n', fitas[indice]);
    return 0;
}

int passaFitaSaida() {
    // Ler o primeiro registro de cada fita retira o registor com a menor chave e o armazena na fita de saida
    // Acho que vou ordenar a primeira linha de todas as fitas na primeira linha da fita de saida e assim por diante

    for (int i = 0; i < F - 1; i++) {
        char nome[15];
        sprintf(nome, "fita%d.txt", i + 1);
        fitas[i] = fopen(nome, "r");
    }
    resetaMemoriaPrincipal();
    int fitasAbertasi = fitasAbertas();
    lePrimeiroElementoDeCadaLinha();
    fitas[19] = fopen("fita20.txt", "w");
    while (!fitasEOF()) {
        ordenarMemoriaPrincipal(fitasAbertasi);
        int fitaUsada = printNaFita(19, 0, 1);
        if (fitaChegouAoFimDaLinha(fitaUsada)) {
            fitaUsada = fitaAindaTemLinha();
            if (fitaUsada == -1) {
                ordenarMemoriaPrincipal(fitasAbertasi);
                printNaFita(19, 1, fitasAbertasi);
                fputc('\n', fitas[19]);
                lePrimeiroElementoDeCadaLinha();
                ordenarMemoriaPrincipal(fitasAbertasi);
                fitaUsada = printNaFita(19, 0, 1);
            }
        }
        fscanf(fitas[fitaUsada], "%s %s %s %51c %30c", memPrincipal[0].inscricao, memPrincipal[0].nota,
               memPrincipal[0].estado,
               memPrincipal[0].cidade, memPrincipal[0].curso);
        memPrincipal[0].notaf = atof(memPrincipal[0].nota);
        memPrincipal[0].fita = fitaUsada;
        leiturasf++;
    }
    ordenarMemoriaPrincipal(fitasAbertasi);
    printNaFita(19, 0, fitasAbertasi);
}

bool fitaChegouAoFimDaLinha(int fitaUsada) {
    int curPos = ftell(fitas[fitaUsada]);
    char check = fgetc(fitas[fitaUsada]);
    fseek(fitas[fitaUsada], curPos, SEEK_SET);
    return check == '\n';
}

int fitaAindaTemLinha() {
    int fita = 0;
    while (fitaChegouAoFimDaLinha(fita++)) {
        if (fita == 19)
            return -1;
    }
    return fita - 1;
}

bool fitasEOF() {
    for (int i = 0; i < F - 1; i++) {
        if (feof(fitas[i]))
            return true;
    }
    return false;
}

int lePrimeiroElementoDeCadaLinha() {
    int fitasAbertasi = fitasAbertas();
    for (int i = 0; i < fitasAbertasi; i++) {
        fscanf(fitas[i], "%s %s %s %51c %30c", memPrincipal[i].inscricao, memPrincipal[i].nota,
               memPrincipal[i].estado,
               memPrincipal[i].cidade, memPrincipal[i].curso);
        memPrincipal[i].notaf = atof(memPrincipal[i].nota);
        memPrincipal[i].fita = i;
        leiturasf++;
    }
}

int printNaFita(int fita, int inicio, int final) {
    int i = inicio;
    for (; i < final; i++) {
        fprintf(fitas[fita], "%s %s %s %.50s %.30s", memPrincipal[i].inscricao, memPrincipal[i].nota,
                memPrincipal[i].estado,
                memPrincipal[i].cidade, memPrincipal[i].curso);
        escritasf++;
    }
    return memPrincipal[i - 1].fita;
}

int redistribuirBlocos(int fitaOrigem) {
    char nome[15];
    sprintf(nome, "fita%d.txt", fitaOrigem + 1);
    fitas[fitaOrigem] = fopen(nome, "r");
    for (int i = 0; i < 19; i++) {
        if (i == fitaOrigem)i++;
        sprintf(nome, "fita%d.txt", i + 1);
        fitas[i] = fopen(nome, "w");
    }
    int indice = 0;
    while (preencheMemoriaPrincipal(fitas[fitaOrigem])) {
        printNaFita(indice, 0, 19);
        if (fitaChegouAoFimDaLinha(fitaOrigem)) {
            //printNaFita(indice, 0, 19);
            fputc('\n', fitas[indice++]);
            if (indice == fitaOrigem)indice++;
            if (indice == 20)indice = 0;
        }
    }
    return 0;
}

int fitasAbertas() {
    int fitasFechadas = 0;
    for (int i = 0; i < F - 1; i++) {
        int curPos = ftell(fitas[i]);
        char check = fgetc(fitas[i]);
        if (feof(fitas[i])) {
            fitasFechadas++;
        }
        fseek(fitas[i], curPos, SEEK_SET);
    }
    return F - 1 - fitasFechadas;
}

void resetaMemoriaPrincipal() {
    for (int i = 0; i < F - 1; i++) {
        memPrincipal[i].notaf = -1;
    }
}

void imprimeArquivo(int indice) {
    char nome[15];
    sprintf(nome, "fita%d.txt", indice + 1);
    int i = 0;
    int qt = 1;
    char *file_contents;
    long input_file_size;
    FILE *input_file = fopen(nome, "rb");
    fseek(input_file, 0, SEEK_END);
    input_file_size = ftell(input_file);
    rewind(input_file);
    file_contents = (char*)malloc(input_file_size * (sizeof(char)));
    fread(file_contents, sizeof(char), input_file_size, input_file);
    fclose(input_file);
    cout << file_contents;
}
