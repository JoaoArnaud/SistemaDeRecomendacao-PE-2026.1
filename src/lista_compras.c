#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_compras.h"

static int buscarIndiceCliente(MapaClientes mapa, char cod_cliente[9]) {
    for (int i = 0; i < mapa.quantidade; i++) {
        if (strcmp(mapa.clientes[i].cod_cliente, cod_cliente) == 0) {
            return mapa.clientes[i].indice_interno;
        }
    }

    return -1;
}

static int buscarIndiceProduto(MapaProdutos mapa, char cod_produto[6]) {
    for (int i = 0; i < mapa.quantidade; i++) {
        if (strcmp(mapa.produtos[i].cod_produto, cod_produto) == 0) {
            return mapa.produtos[i].indice_interno;
        }
    }

    return -1;
}

ListaClientes codigosClientes(DadosCompras dados) {
    ListaClientes lista;

    lista.clientes = malloc(dados.quantidade * sizeof(CodigoCliente));
    lista.quantidade = 0;

    if (lista.clientes == NULL) {
        perror("Erro ao alocar memoria");
        return lista;
    }

    for (int i = 0; i < dados.quantidade; i++) {
        int repetido = 0;

        for (int j = 0; j < lista.quantidade; j++) {
            if (strcmp(lista.clientes[j].cod_cliente, dados.registros[i].cod_cliente) == 0) {
                repetido = 1;
                break;
            }
        }

        if (repetido) {
            continue;
        }

        strcpy(lista.clientes[lista.quantidade].cod_cliente, dados.registros[i].cod_cliente);
        lista.quantidade++;
    }

    return lista;
}

ListaCodigosProdutos codigosProdutos(DadosCompras dados) {
    ListaCodigosProdutos lista;

    lista.produtos = malloc(dados.quantidade * sizeof(CodigoProduto));
    lista.quantidade = 0;

    if (lista.produtos == NULL) {
        perror("Erro ao alocar memoria");
        return lista;
    }

    for (int i = 0; i < dados.quantidade; i++) {
        int repetido = 0;

        for (int j = 0; j < lista.quantidade; j++) {
            if (strcmp(lista.produtos[j].cod_produto, dados.registros[i].cod_produto) == 0) {
                repetido = 1;
                break;
            }
        }

        if (repetido) {
            continue;
        }

        strcpy(lista.produtos[lista.quantidade].cod_produto, dados.registros[i].cod_produto);
        lista.quantidade++;
    }

    return lista;
}

ListaProdutos nomesProdutos(DadosCompras dados) {
    ListaProdutos lista;

    lista.produtos = malloc(dados.quantidade * sizeof(NomeProduto));
    lista.quantidade = 0;

    if (lista.produtos == NULL) {
        perror("Erro ao alocar memoria");
        return lista;
    }

    for (int i = 0; i < dados.quantidade; i++) {
        int repetido = 0;

        for (int j = 0; j < lista.quantidade; j++) {
            if (strcmp(lista.produtos[j].nome_produto, dados.registros[i].nome_produto) == 0) {
                repetido = 1;
                break;
            }
        }

        if (repetido) {
            continue;
        }

        strcpy(lista.produtos[lista.quantidade].nome_produto, dados.registros[i].nome_produto);
        lista.quantidade++;
    }

    return lista;
}

MapaClientes mapaClientes(ListaClientes codigosClientes) {
    MapaClientes mapa;

    mapa.clientes = malloc(codigosClientes.quantidade * sizeof(MapaCliente));
    mapa.quantidade = 0;

    if (mapa.clientes == NULL) {
        perror("Erro ao alocar memoria");
        return mapa;
    }

    for (int i = 0; i < codigosClientes.quantidade; i++) {
        strcpy(mapa.clientes[i].cod_cliente, codigosClientes.clientes[i].cod_cliente);
        mapa.clientes[i].indice_interno = i;
        mapa.quantidade++;
    }

    return mapa;
}

ComprasPorCliente comprasPorCliente(DadosCompras dados, MapaClientes mapaClientes, MapaProdutos mapaProdutos) {
    ComprasPorCliente compras;

    compras.clientes = malloc(mapaClientes.quantidade * sizeof(ProdutosComprados));
    compras.quantidade = mapaClientes.quantidade;

    if (compras.clientes == NULL) {
        perror("Erro ao alocar memoria");
        compras.quantidade = 0;
        return compras;
    }

    for (int i = 0; i < compras.quantidade; i++) {
        compras.clientes[i].produtos = NULL;
        compras.clientes[i].quantidade = 0;
        compras.clientes[i].capacidade = 0;
    }

    for (int i = 0; i < dados.quantidade; i++) {
        int indice_cliente = buscarIndiceCliente(mapaClientes, dados.registros[i].cod_cliente);
        int indice_produto = buscarIndiceProduto(mapaProdutos, dados.registros[i].cod_produto);

        if (indice_cliente == -1 || indice_produto == -1) {
            continue;
        }

        ProdutosComprados *produtos_cliente = &compras.clientes[indice_cliente];

        if (produtos_cliente->quantidade == produtos_cliente->capacidade) {
            int nova_capacidade = produtos_cliente->capacidade == 0 ? 4 : produtos_cliente->capacidade * 2;
            int *novo = realloc(produtos_cliente->produtos, nova_capacidade * sizeof(int));

            if (novo == NULL) {
                perror("Erro ao realocar memoria");
                liberarComprasPorCliente(compras);
                compras.clientes = NULL;
                compras.quantidade = 0;
                return compras;
            }

            produtos_cliente->produtos = novo;
            produtos_cliente->capacidade = nova_capacidade;
        }

        produtos_cliente->produtos[produtos_cliente->quantidade] = indice_produto;
        produtos_cliente->quantidade++;
    }

    return compras;
}

void liberarComprasPorCliente(ComprasPorCliente compras) {
    for (int i = 0; i < compras.quantidade; i++) {
        free(compras.clientes[i].produtos);
    }

    free(compras.clientes);
}

MapaProdutos mapaProdutos(ListaCodigosProdutos codigosProdutos) {
    MapaProdutos mapa;

    mapa.produtos = malloc(codigosProdutos.quantidade * sizeof(MapaProduto));
    mapa.quantidade = 0;

    if (mapa.produtos == NULL) {
        perror("Erro ao alocar memoria");
        return mapa;
    }

    for (int i = 0; i < codigosProdutos.quantidade; i++) {
        strcpy(mapa.produtos[i].cod_produto, codigosProdutos.produtos[i].cod_produto);
        mapa.produtos[i].indice_interno = i;
        mapa.quantidade++;
    }

    return mapa;
}
