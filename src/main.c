#include <stdio.h>
#include <stdlib.h>

#include "../include/ler_dados.h"
#include "../include/lista_compras.h"

int main(void) {
    DadosCompras dados;
    ListaCompras *lista;
    char codigoCliente[9];

    dados = lerArquivo("data/dados_venda_cluster_0.csv");

    if (dados.registros == NULL) {
        return 1;
    }

    lista = criaListaCompras(dados);

    for (int i = 0; i < 3; i++) {
        printf("\nDigite o codigo do cliente: ");
        scanf("%8s", codigoCliente);

        exibeComprasCliente(
            lista,
            codigoCliente
        );
    }

    liberaListaCompras(lista);
    free(dados.registros);

    return 0;
}