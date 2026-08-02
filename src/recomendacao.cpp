#include <algorithm>
#include <stdlib.h>
#include "../include/recomendacao.h"
using namespace std;

int *getListaVizinhos(const SimilaridadeCSR *similaridade, int indice_cliente, int *total_vizinhos) {
    int *lista_vizinhos = (int *) malloc(similaridade->linha_matriz * sizeof(int));
    *total_vizinhos = 0;

    int inicio = similaridade->matriz_intersecao.row_ptr[indice_cliente];
    int fim = similaridade->matriz_intersecao.row_ptr[indice_cliente + 1];

    for (int k = inicio; k < fim; k++) {
        int j = similaridade->matriz_intersecao.col_index[k];
        if (j == indice_cliente) continue;

        lista_vizinhos[*total_vizinhos] = j;
        (*total_vizinhos)++;
    }

    return lista_vizinhos;
}

ItemRanking *recomendacao_calcula_ranking(const SimilaridadeCSR *similaridade, const ListaCompras *lista_compras, int indice_cliente) {
    int m = lista_compras->nomes_produtos.size();
    ItemRanking *r = (ItemRanking *) malloc(m * sizeof(ItemRanking));
    for (int p = 0; p < m; p++) {
        r[p].indice_produto = p;
        r[p].ranqueamento = 1.0;
    }

    int total_vizinhos = 0;
    int *vizinhos = getListaVizinhos(similaridade, indice_cliente, &total_vizinhos);
    for (int i = 0; i < total_vizinhos; i++) {
        int s = vizinhos[i];
        double valor_similaridade = getValorSimilaridadeCSR(similaridade, indice_cliente, s);

        int inicio = similaridade->matriz_compras.row_ptr[s];
        int fim = similaridade->matriz_compras.row_ptr[s + 1];

        for (int k = inicio; k < fim; k++) {
            int p = similaridade->matriz_compras.col_index[k];
            bool cliente_nao_comprou = getValorMatrizCSR(
                &similaridade->matriz_compras,
                indice_cliente,
                p
            ) == 0;

            if (cliente_nao_comprou) {
                r[p].ranqueamento *= valor_similaridade;
            }
        }
    }
    free(vizinhos);
    return r;
}

bool comparaRanking(const ItemRanking &a, const ItemRanking &b) {
    if (a.ranqueamento != b.ranqueamento) {
        return a.ranqueamento < b.ranqueamento;
    }
    
    return a.indice_produto < b.indice_produto;
}

ItemRanking *getTopKRecomendacoes(const SimilaridadeCSR *similaridade, const ListaCompras *lista_compras, int indice_cliente, int k) {
    int m = lista_compras->nomes_produtos.size();
    ItemRanking *r = recomendacao_calcula_ranking(similaridade, lista_compras, indice_cliente);
    sort(r, r + m, comparaRanking);

    if (k < 0) k = 0;
    if (k > m) k = m;
    ItemRanking *topk = (ItemRanking *) malloc(k * sizeof(ItemRanking));
    for (int j = 0; j < k; j++) topk[j] = r[j];
    free(r);
    return topk;
}
