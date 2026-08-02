#include <iostream>
#include <stdlib.h>

#include "../include/lista_compras.h"
#include "../include/similaridade.h"
#include "../include/recomendacao.h"

int main(const char *caminho_arquivo) {
    const char *caminho_arquivo = "data/dados_venda_cluster_17.csv";
    ListaCompras lista_compras;
    inicializaListaCompras(&lista_compras);

    if (!carregarDados(&lista_compras, caminho_arquivo)) {
        std::cerr << "Erro ao carregar os dados do arquivo: " << caminho_arquivo << std::endl;
        return;
    }

    SimilaridadeCSR similaridade;
    calculaMatrizSimilaridadeCSR(&similaridade, &lista_compras);

    int indice_cliente = 0;
    int k = 5;
    if (k > (int) lista_compras.nomes_produtos.size()) {
        k = lista_compras.nomes_produtos.size();
    }

    ItemRanking *topk_recomendacoes = getTopKRecomendacoes(&similaridade, &lista_compras, indice_cliente, k);

    std::cout << "Top " << k << " recomendacoes para o cliente "
              << lista_compras.cod_clientes[indice_cliente] << ":\n";

    for (int i = 0; i < k; i++) {
        int indice_produto = topk_recomendacoes[i].indice_produto;
        double ranqueamento = topk_recomendacoes[i].ranqueamento;

        std::cout << "Produto: " << lista_compras.nomes_produtos[indice_produto] << ", ranqueamento: " << ranqueamento << '\n';
    }

    free(topk_recomendacoes);
    freeSimilaridadeCSR(&similaridade);
    return 0;
}
