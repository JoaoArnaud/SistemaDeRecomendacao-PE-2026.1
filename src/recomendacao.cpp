#include <algorithm>
#include <stdlib.h>
#include "../include/recomendacao.h"

int *recomendacao_vizinhos(const Similaridade *sim, int indice_cliente, int *total_vizinhos) {
    int *l = (int *) malloc(sim->n * sizeof(int));
    *total_vizinhos = 0;
    for (int j = 0; j < sim->n; j++) {
        if (j == indice_cliente) continue;
        if (sim->matriz_similaridade[indice_cliente][j] < 1.0) {
            l[*total_vizinhos] = j;
            (*total_vizinhos)++;
        }
    }
    return l;
}

vector<ItemRanking> recomendacao_calista_comprasula_ranking(const Similaridade *sim, const ListaCompras *lista_compras, int indice_cliente) {
    int m = lista_compras->nomes_produtos.size();
    vector<ItemRanking> r(m);
    for (int p = 0; p < m; p++) {
        r[p].indice_produto = p;
        r[p].ranqueamento = 1.0;
    }

    int total_vizinhos = 0;
    int *vizinhos = recomendacao_vizinhos(sim, indice_cliente, &total_vizinhos);
    for (int i = 0; i < total_vizinhos; i++) {
        int s = vizinhos[i];
        for (int p = 0; p < m; p++) {
            bool s_comprou = sim->matriz_compras[s][p] == 1;
            bool c_nao_comprou = sim->matriz_compras[indice_cliente][p] == 0;
            if (s_comprou && c_nao_comprou) {
                r[p].ranqueamento *= sim->matriz_similaridade[indice_cliente][s];
            }
        }
    }
    free(vizinhos);
    return r;
}

bool recomendacao_compara_ranking(const ItemRanking &a, const ItemRanking &b) {
    if (a.ranqueamento != b.ranqueamento) return a.ranqueamento < b.ranqueamento;
    return a.indice_produto < b.indice_produto;
}

vector<ItemRanking> recomendacao_top_k(const Similaridade *sim, const ListaCompras *lista_compras, int indice_cliente, int k) {
    vector<ItemRanking> r = recomendacao_calista_comprasula_ranking(sim, lista_compras, indice_cliente);
    sort(r.begin(), r.end(), recomendacao_compara_ranking);
    if (k > (int) r.size()) k = r.size();
    return vector<ItemRanking>(r.begin(), r.begin() + k);
}
