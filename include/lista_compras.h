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

ListaClientes codigosClientes(DadosCompras dados);

#endif // LISTA_COMPRAS_H