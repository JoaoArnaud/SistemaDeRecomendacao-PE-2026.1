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
    char cod_cliente[9];
    int indice_interno;
} MapaCliente;

typedef struct {
    MapaCliente *clientes;
    int quantidade;
} MapaClientes;

ListaClientes codigosClientes(DadosCompras dados);
MapaClientes mapaClientes(ListaClientes codigosClientes);

#endif // LISTA_COMPRAS_H
