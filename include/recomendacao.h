#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include <vector>
#include "../include/lista_compras.h"
#include "../include/similaridade.h"
using namespace std;

typedef struct {
    int indice_produto;
    double ranqueamento;
} ItemRanking;

int *recomendacao_vizinhos(const Similaridade *sim, int indice_cliente, int *total_vizinhos);
vector<ItemRanking> recomendacao_calista_comprasula_ranking(const Similaridade *sim, const ListaCompras *lista_compras, int indice_cliente);
bool recomendacao_compara_ranking(const ItemRanking &a, const ItemRanking &b);
vector<ItemRanking> recomendacao_top_k(const Similaridade *sim, const ListaCompras *lista_compras, int indice_cliente, int k);

#endif
