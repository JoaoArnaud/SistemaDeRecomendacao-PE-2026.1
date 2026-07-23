#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include "../include/lista_compras.h"
using namespace std;

typedef int** Matriz;
typedef double** MatrizDouble;

typedef struct {
    int linha;
    int coluna;
    Matriz matriz_compras;
    Matriz matriz_intersecao;
    MatrizDouble matriz_similaridade;
} Similaridade;

void inicializaSimilaridade(Similaridade *similaridade);
void freeSimilaridade(Similaridade *similaridade);
void similaridade_monta_matriz_compras(Similaridade *similaridade, const ListaCompras *lista_compras);
Matriz similaridade_transposta(Matriz a, int linhas, int colunas);
Matriz similaridade_multiplica_matrizes(Matriz a, int linhas_a, int colunas_a, Matriz b, int colunas_b);
void similaridade_calista_comprasula(Similaridade *similaridade, const ListaCompras *lista_compras);
int similaridade_mais_similar(const Similaridade *similaridade, int indice_cliente);

#endif
