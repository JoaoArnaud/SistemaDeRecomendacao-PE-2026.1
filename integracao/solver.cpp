#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <list>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>

#include "../include/lista_compras.h"
#include "../include/similaridade.h"
#include "../include/recomendacao.h"

namespace py = pybind11;

std::vector<int> recomendarProdutos(
    const std::vector<std::string> &cod_clientes,
    const std::map<std::string, int> &mapa_clientes,
    const std::vector<std::string> &nomes_produtos,
    const std::map<std::string, int> &mapa_produtos,
    const std::vector<std::list<int>> &compras,
    int indice_cliente,
    int k
) {
    ListaCompras lista_compras;

    lista_compras.cod_clientes = cod_clientes;
    lista_compras.mapa_clientes = mapa_clientes;
    lista_compras.nomes_produtos = nomes_produtos;
    lista_compras.mapa_produtos = mapa_produtos;
    lista_compras.compras = compras;

    if (k < 0) {
        k = 0;
    }

    if (k > (int) nomes_produtos.size()) {
        k = nomes_produtos.size();
    }

    SimilaridadeCSR similaridade;
    calculaMatrizSimilaridadeCSR(&similaridade, &lista_compras);

    ItemRanking *topk = getTopKRecomendacoes(
        &similaridade,
        &lista_compras,
        indice_cliente,
        k
    );

    std::vector<int> recomendacoes;
    recomendacoes.reserve(k);

    for (int i = 0; i < k; i++) {
        recomendacoes.push_back(topk[i].indice_produto);
    }

    free(topk);
    freeSimilaridadeCSR(&similaridade);

    return recomendacoes;
}

PYBIND11_MODULE(solver, m) {
    m.doc() = "Modulo de integracao do sistema de recomendacao";

    m.def(
        "recomendar_produtos",
        &recomendarProdutos,
        "Retorna os produtos recomendados para um cliente",
        py::arg("cod_clientes"),
        py::arg("mapa_clientes"),
        py::arg("nomes_produtos"),
        py::arg("mapa_produtos"),
        py::arg("compras"),
        py::arg("indice_cliente"),
        py::arg("k")
    );
}