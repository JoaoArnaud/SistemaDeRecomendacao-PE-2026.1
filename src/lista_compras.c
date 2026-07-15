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
