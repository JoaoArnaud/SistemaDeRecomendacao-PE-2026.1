#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include "../include/lista_compras.h"

typedef int** Matriz;
typedef double** MatrizDouble;

typedef struct {
    int linha_matriz = 0;
    int coluna_matriz = 0;
    Matriz matriz_compras = nullptr;
    Matriz matriz_intersecao = nullptr;
    MatrizDouble matriz_similaridade = nullptr;
} Similaridade;

void freeSimilaridade(Similaridade *similaridade);
void geraMatrizCompras(Similaridade *similaridade, const ListaCompras *lista_compras);
Matriz getTransposta(Matriz a, int linhas, int colunas);
Matriz getProdutoMatrizes(Matriz a, int linhas_a, int colunas_a, Matriz b, int colunas_b);
void calculaMatrizSimilaridade(Similaridade *similaridade, const ListaCompras *lista_compras);
int getMaisSimilar(const Similaridade *similaridade, int indice_cliente);

#endif
