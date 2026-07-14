#include <stdio.h>
#include <stdlib.h>
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
        for (int j = 0; j < 9; j++) {
            lista.clientes[i].cod_cliente[j] = dados.registros[i].cod_cliente[j];
        }

        lista.quantidade++;
    }

    return lista;
}
