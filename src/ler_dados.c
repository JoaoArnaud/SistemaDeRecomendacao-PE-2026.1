#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char data_compra[9];
    char cod_cliente[9];
    char cod_produto[6];
    char nome_produto[100];
} RegistroCompra;

int ler() {
    FILE *arquivo;
    RegistroCompra registro;

    // Abre arquivo CSV para leitura
    //TODO: loop para abrir todos os arquivos de dados
    arquivo = fopen("data/dados_venda_cluster_0.csv", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ignora a primeira linha (cabeçalho)
    fscanf(arquivo, "%*[^\n]\n");

    // Lê cada linha do arquivo CSV
    while (fscanf(arquivo, "%8[^;];%8[^;];%5[^;];%99[^\n]\n",
        registro.data_compra, 
        registro.cod_cliente, 
        registro.cod_produto, 
        registro.nome_produto) == 4) {
        // Imprime os dados lidos
        printf("%s | %s | %s | %s\n", 
            registro.data_compra, 
            registro.cod_cliente, 
            registro.cod_produto, 
            registro.nome_produto);
    }

    // Fecha o arquivo
    fclose(arquivo);
    return 0;
}