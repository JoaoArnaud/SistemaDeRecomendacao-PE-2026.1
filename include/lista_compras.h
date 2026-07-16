#ifndef LISTA_COMPRAS_H
#define LISTA_COMPRAS_H

#include "ler_dados.h"

typedef struct {
    char cod_cliente[9];
} CodigoCliente;

typedef struct {
    CodigoCliente *clientes;
    int quantidade;
} ListaClientes;

typedef struct {
    char cod_produto[6];
} CodigoProduto;

typedef struct {
    CodigoProduto *produtos;
    int quantidade;
} ListaCodigosProdutos;

typedef struct {
    char nome_produto[100];
} NomeProduto;

typedef struct {
    NomeProduto *produtos;
    int quantidade;
} ListaProdutos;

typedef struct {
    char cod_cliente[9];
    int indice_interno;
} MapaCliente;

typedef struct {
    MapaCliente *clientes;
    int quantidade;
} MapaClientes;

typedef struct {
    char cod_produto[6];
    int indice_interno;
} MapaProduto;

typedef struct {
    MapaProduto *produtos;
    int quantidade;
} MapaProdutos;

ListaClientes codigosClientes(DadosCompras dados);
ListaCodigosProdutos codigosProdutos(DadosCompras dados);
ListaProdutos nomesProdutos(DadosCompras dados);
MapaClientes mapaClientes(ListaClientes codigosClientes);
MapaProdutos mapaProdutos(ListaCodigosProdutos codigosProdutos);

#endif // LISTA_COMPRAS_H
