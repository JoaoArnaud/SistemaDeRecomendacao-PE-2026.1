#include <stdio.h>
#include <stdlib.h>
#include "../include/ler_dados.h"
#include "../include/lista_compras.h"

int main() {
    DadosCompras dados = lerArquivo("data/dados_venda_cluster_0.csv");
    ListaClientes clientes = codigosClientes(dados);
    ListaCodigosProdutos codigos_produtos = codigosProdutos(dados);
    ListaProdutos produtos = nomesProdutos(dados);
    MapaClientes mapa = mapaClientes(clientes);
    MapaProdutos mapa_produtos = mapaProdutos(codigos_produtos);
    ComprasPorCliente compras = comprasPorCliente(dados, mapa, mapa_produtos);

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

    printf("\nMapa de produtos:\n");
    for (int i = 0; i < mapa_produtos.quantidade; i++) {
        printf("%s -> %d\n", mapa_produtos.produtos[i].cod_produto, mapa_produtos.produtos[i].indice_interno);
    }

    printf("\nCompras por cliente:\n");
    for (int i = 0; i < compras.quantidade; i++) {
        printf("Cliente %d: ", i);

        for (int j = 0; j < compras.clientes[i].quantidade; j++) {
            printf("%d", compras.clientes[i].produtos[j]);

            if (j < compras.clientes[i].quantidade - 1) {
                printf(", ");
            }
        }

        printf("\n");
    }

    liberarComprasPorCliente(compras);
    free(mapa_produtos.produtos);
    free(mapa.clientes);
    free(produtos.produtos);
    free(codigos_produtos.produtos);
    free(clientes.clientes);
    free(dados.registros);

    return 0;
}
