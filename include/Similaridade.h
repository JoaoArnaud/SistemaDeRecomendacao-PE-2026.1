#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include "../include/ListaCompras.h"
using namespace std;

typedef int** Matriz;
typedef double** MatrizDouble;

typedef struct {
    int n;
    int m;
    Matriz matriz_compras;
    Matriz matriz_intersecao;
    MatrizDouble matriz_similaridade;
} Similaridade;

void inicializa_similaridade(Similaridade *sim);
void similaridade_libera(Similaridade *sim);
void similaridade_monta_matriz_compras(Similaridade *sim, const ListaCompras *lc);
Matriz similaridade_transposta(Matriz a, int linhas, int colunas);
Matriz similaridade_multiplica_matrizes(Matriz a, int linhas_a, int colunas_a, Matriz b, int colunas_b);
void similaridade_calcula(Similaridade *sim, const ListaCompras *lc);
int similaridade_mais_similar(const Similaridade *sim, int indice_cliente);

#endif
