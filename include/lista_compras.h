#ifndef LISTA_COMPRAS_H
#define LISTA_COMPRAS_H

#include "ler_dados.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ListaCompras ListaCompras;

ListaCompras *criaListaCompras(DadosCompras dados);

void exibeComprasCliente(
    ListaCompras *lista,
    const char *codigoCliente
);

void liberaListaCompras(ListaCompras *lista);

#ifdef __cplusplus
}
#endif

#endif