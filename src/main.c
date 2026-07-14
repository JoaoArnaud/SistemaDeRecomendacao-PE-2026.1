#include <stdio.h>
#include <stdlib.h>
#include "../include/ler_dados.h"
#include "../include/lista_compras.h"

int main() {
    DadosCompras dados = lerArquivo("data/dados_venda_cluster_0.csv");
    ListaClientes clientes = codigosClientes(dados);

    printf("Quantidade de clientes na lista: %d\n", clientes.quantidade);

    for (int i = 0; i < clientes.quantidade; i++) {
        printf("%s\n", clientes.clientes[i].cod_cliente);
    }

    free(clientes.clientes);
    free(dados.registros);

    return 0;
}