#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include "../include/lista_compras.h"
using namespace std;

typedef int** Matriz;
typedef double** MatrizDouble;

typedef struct {
    int linha_matriz;
    int coluna_matriz;
    Matriz matriz_compras;
    Matriz matriz_intersecao;
    MatrizDouble matriz_similaridade;
} Similaridade;

void inicializaSimilaridade(Similaridade *similaridade);
void freeSimilaridade(Similaridade *similaridade);
void geraMatrizCompras(Similaridade *similaridade, const ListaCompras *lista_compras);
Matriz getTransposta(Matriz a, int linhas, int colunas);
Matriz getProdutoMatrizes(Matriz a, int linhas_a, int colunas_a, Matriz b, int colunas_b);
void similaridade_calista_comprasula(Similaridade *similaridade, const ListaCompras *lista_compras);
int getMaisSimilar(const Similaridade *similaridade, int indice_cliente);

#endif
