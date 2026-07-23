#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "../include/lista_compras.h"
#include "../include/similaridade.h"
using namespace std;

typedef struct {
    int indice_produto;
    double ranqueamento;
} ItemRanking;

int *getListaVizinhos(const Similaridade *similaridade, int indice_cliente, int *total_vizinhos);
ItemRanking *recomendacao_calcula_ranking(const Similaridade *similaridade, const ListaCompras *lista_compras, int indice_cliente);
bool comparaRanking(const ItemRanking &a, const ItemRanking &b);
ItemRanking *recomendacao_top_k(const Similaridade *similaridade, const ListaCompras *lista_compras, int indice_cliente, int k);

#endif
