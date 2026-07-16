#include <stdio.h>
#include <stdlib.h>
#include "../include/ler_dados.h"

DadosCompras lerArquivo(char *caminho) {
    FILE *arquivo;
    RegistroCompra registro;
    DadosCompras dados;
    int capacidade = 10;

    dados.registros = malloc(capacidade * sizeof(RegistroCompra));
    dados.quantidade = 0;

    if (dados.registros == NULL) {
        perror("Erro ao alocar memoria");
        return dados;
    }

    // Abre arquivo CSV para leitura
    arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        free(dados.registros);
        dados.registros = NULL;
        return dados;
    }

    // Ignora a primeira linha (cabeçalho)
    fscanf(arquivo, "%*[^\n]\n");

    // Lê cada linha do arquivo CSV
    while (fscanf(arquivo, "%8[^;];%8[^;];%6[^;];%99[^\n]\n",
        registro.data_compra, 
        registro.cod_cliente, 
        registro.cod_produto, 
        registro.nome_produto) == 4) {
        if (dados.quantidade == capacidade) {
            capacidade *= 2;
            RegistroCompra *novo = realloc(dados.registros, capacidade * sizeof(RegistroCompra));

            if (novo == NULL) {
                perror("Erro ao realocar memoria");
                free(dados.registros);
                dados.registros = NULL;
                dados.quantidade = 0;
                fclose(arquivo);
                return dados;
            }

            dados.registros = novo;
        }

        dados.registros[dados.quantidade] = registro;
        dados.quantidade++;
    }

    // Fecha o arquivo
    fclose(arquivo);
    return dados;
}
