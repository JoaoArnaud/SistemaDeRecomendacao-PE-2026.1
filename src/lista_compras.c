#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_compras.h"

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
