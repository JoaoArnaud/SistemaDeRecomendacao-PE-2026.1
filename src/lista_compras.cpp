#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

#include "../include/lista_compras.h"

struct ListaCompras {
    std::vector<std::string> codigosClientes;
    std::map<std::string, int> indicesClientes;

    std::vector<std::string> nomesProdutos;
    std::map<std::string, int> indicesProdutos;

    std::vector<std::list<int>> comprasClientes;
};

ListaCompras *criaListaCompras(DadosCompras dados) {
    ListaCompras *lista = new ListaCompras;

    /*
     * Primeira fase:
     * cadastra os clientes e produtos.
     */
    for (int i = 0; i < dados.quantidade; i++) {
        std::string codigoCliente =
            dados.registros[i].cod_cliente;

        std::string codigoProduto =
            dados.registros[i].cod_produto;

        std::string nomeProduto =
            dados.registros[i].nome_produto;

        if (
            lista->indicesClientes.find(codigoCliente) ==
            lista->indicesClientes.end()
        ) {
            int indiceCliente =
                lista->codigosClientes.size();

            lista->codigosClientes.push_back(
                codigoCliente
            );

            lista->indicesClientes[codigoCliente] =
                indiceCliente;
        }

        if (
            lista->indicesProdutos.find(codigoProduto) ==
            lista->indicesProdutos.end()
        ) {
            int indiceProduto =
                lista->nomesProdutos.size();

            lista->nomesProdutos.push_back(
                nomeProduto
            );

            lista->indicesProdutos[codigoProduto] =
                indiceProduto;
        }
    }

    /*
     * Cria uma lista de compras para cada cliente.
     */
    lista->comprasClientes.resize(
        lista->codigosClientes.size()
    );

    /*
     * Segunda fase:
     * adiciona os produtos comprados por cada cliente.
     */
    for (int i = 0; i < dados.quantidade; i++) {
        std::string codigoCliente =
            dados.registros[i].cod_cliente;

        std::string codigoProduto =
            dados.registros[i].cod_produto;

        int indiceCliente =
            lista->indicesClientes[codigoCliente];

        int indiceProduto =
            lista->indicesProdutos[codigoProduto];

        lista->comprasClientes[indiceCliente].push_back(
            indiceProduto
        );
    }

    return lista;
}

void exibeComprasCliente(
    ListaCompras *lista,
    const char *codigoCliente
) {
    std::map<std::string, int>::iterator cliente;

    cliente = lista->indicesClientes.find(
        codigoCliente
    );

    if (cliente == lista->indicesClientes.end()) {
        std::cout << "Cliente nao encontrado.\n";
        return;
    }

    int indiceCliente = cliente->second;

    std::cout << "\nCompras do cliente "
              << codigoCliente
              << ":\n";

    for (
        int indiceProduto :
        lista->comprasClientes[indiceCliente]
    ) {
        std::cout
            << lista->nomesProdutos[indiceProduto]
            << "\n";
    }
}

void liberaListaCompras(ListaCompras *lista) {
    delete lista;
}