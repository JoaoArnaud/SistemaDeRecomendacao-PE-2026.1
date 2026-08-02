#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include "../include/lista_compras.h"
#include <stddef.h>

typedef struct MatrizCSR {
    int linhas = 0;
    int colunas = 0;
    int quantidade_nao_nulos = 0;
    int *values = nullptr;
    int *col_index = nullptr;
    int *row_ptr = nullptr;
} MatrizCSR;

typedef struct SimilaridadeCSR {
    int linha_matriz = 0;
    int coluna_matriz = 0;
    MatrizCSR matriz_compras;
    MatrizCSR matriz_intersecao;
} SimilaridadeCSR;

void freeMatrizCSR(MatrizCSR *matriz);
void freeSimilaridadeCSR(SimilaridadeCSR *similaridade);
MatrizCSR geraMatrizComprasCSR(const ListaCompras *lista_compras);
MatrizCSR getMatrizIntersecaoCSR(const MatrizCSR *matriz_compras);
int getValorMatrizCSR(const MatrizCSR *matriz, int linha, int coluna);
void calculaMatrizSimilaridadeCSR(SimilaridadeCSR *similaridade, const ListaCompras *lista_compras);
double getValorSimilaridadeCSR(const SimilaridadeCSR *similaridade, int indice_cliente_i, int indice_cliente_j);
int getMaisSimilarCSR(const SimilaridadeCSR *similaridade, int indice_cliente);
size_t getMemoriaMatrizCSR(const MatrizCSR *matriz);

#endif
