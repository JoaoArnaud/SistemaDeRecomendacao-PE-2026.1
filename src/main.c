#include <stdio.h>
#include <stdlib.h>
#include "../include/ler_dados.h"
#include "../include/lista_compras.h"

int main() {
    DadosCompras dados = lerArquivo("data/dados_venda_cluster_0.csv");
    ListaClientes clientes = codigosClientes(dados);
    ListaProdutos produtos = nomesProdutos(dados);
    MapaClientes mapa = mapaClientes(clientes);

    printf("Quantidade de clientes na lista: %d\n", clientes.quantidade);

    for (int i = 0; i < clientes.quantidade; i++) {
        printf("%s\n", clientes.clientes[i].cod_cliente);
    }

    printf("\nQuantidade de produtos na lista: %d\n", produtos.quantidade);
    for (int i = 0; i < produtos.quantidade; i++) {
        printf("%s\n", produtos.produtos[i].nome_produto);
    }

    printf("\nMapa de clientes:\n");
    for (int i = 0; i < mapa.quantidade; i++) {
        printf("%s -> %d\n", mapa.clientes[i].cod_cliente, mapa.clientes[i].indice_interno);
    }

    free(mapa.clientes);
    free(produtos.produtos);
    free(clientes.clientes);
    free(dados.registros);

    return 0;
}
