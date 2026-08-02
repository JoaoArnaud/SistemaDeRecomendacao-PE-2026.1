#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "../include/lista_compras.h"
#include "../include/similaridade.h"

typedef struct {
    int indice_produto;
    double ranqueamento;
} ItemRanking;

int *getListaVizinhos(const SimilaridadeCSR *similaridade, int indice_cliente, int *total_vizinhos);
ItemRanking *recomendacao_calcula_ranking(const SimilaridadeCSR *similaridade, const ListaCompras *lista_compras, int indice_cliente);
bool comparaRanking(const ItemRanking &a, const ItemRanking &b);
ItemRanking *getTopKRecomendacoes(const SimilaridadeCSR *similaridade, const ListaCompras *lista_compras, int indice_cliente, int k);

#endif
