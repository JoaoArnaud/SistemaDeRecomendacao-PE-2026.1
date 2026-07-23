#include <stdio.h>
#include <iostream>
#include "../include/lista_compras.h"

void inicializa_lista_compras(ListaCompras *lista_compras) {
    lista_compras->cod_clientes.clear(); // inicializa apagando todos os elementos do vetor
    lista_compras->mapa_clientes.clear();
    lista_compras->nomes_produtos.clear();
    lista_compras->mapa_produtos.clear();
    lista_compras->compras.clear();
}

bool carregarDados(ListaCompras *lista_compras, const char *caminho_arquivo) {
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror(caminho_arquivo);
        return false;
    }

    char cod_produto[9];
    char cod_cliente[9];
    char nome_produto[63];
    char cabecalho[128];

    char *ignora_cabecalho = fgets(cabecalho, sizeof(cabecalho), arquivo); // le o cabeçalho
    (void) ignora_cabecalho; // ignora o valor retornado

    while (fscanf(arquivo, "%*[^,],%9[^,],%9[^,],%63[^\n]\n", 
        cod_cliente, 
        cod_produto, 
        nome_produto) == 3) 
        {

        // adiciona cliente e produto no mapa (cliente -> índice, produto -> índice) caso ainda não existam
        if (lista_compras->mapa_clientes.find(cod_cliente) == lista_compras->mapa_clientes.end()) {
            int indice = lista_compras->cod_clientes.size();
            lista_compras->cod_clientes.push_back(cod_cliente);
            lista_compras->mapa_clientes[cod_cliente] = indice;
        }
        if (lista_compras->mapa_produtos.find(cod_produto) == lista_compras->mapa_produtos.end()) {
            int indice = lista_compras->nomes_produtos.size();
            lista_compras->nomes_produtos.push_back(nome_produto);
            lista_compras->mapa_produtos[cod_produto] = indice;
        }
    }

    // redimensiona o vetor de compras para ter uma posição para cada cliente
    lista_compras->compras.resize(lista_compras->cod_clientes.size());

    fclose(arquivo);

    // reabre o arquivo para ler novamente e preencher as compras
    arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror(caminho_arquivo);
        return false;
    }

    ignora_cabecalho = fgets(cabecalho, sizeof(cabecalho), arquivo);
    (void) ignora_cabecalho;

    while (fscanf(arquivo, "%*[^,],%9[^,],%9[^,],%63[^\n]\n", 
        cod_cliente, 
        cod_produto, 
        nome_produto) == 3) 
        {

        int indice_cliente = lista_compras->mapa_clientes[cod_cliente];
        int indice_produto = lista_compras->mapa_produtos[cod_produto];
        lista_compras->compras[indice_cliente].push_back(indice_produto);
    }

    fclose(arquivo);

    return true;
}

// Retorna o índice do cliente no vetor mapa_clientes, ou -1 caso não exista
int lista_compras_indice_cliente(const ListaCompras *lista_compras, const string &cod_cliente) {
    map<string, int>::const_iterator i = lista_compras->mapa_clientes.find(cod_cliente);
    if (i == lista_compras->mapa_clientes.end()) return -1;
    return i->second;
}

// Retorna o índice do produto no vetor mapa_produtos, ou -1 caso não exista
int lista_compras_indice_produto(const ListaCompras *lista_compras, const string &cod_produto) {
    map<string, int>::const_iterator i = lista_compras->mapa_produtos.find(cod_produto);
    if (i == lista_compras->mapa_produtos.end()) return -1;
    return i->second;
}


void lista_compras_imprime_compras(const ListaCompras *lista_compras, const string &cod_cliente) {
    int indice = lista_compras_indice_cliente(lista_compras, cod_cliente);
    if (indice == -1) return;

    cout << "compras de " << cod_cliente << ":" << endl;
    list<int>::const_iterator it;
    for (it = lista_compras->compras[indice].begin(); it != lista_compras->compras[indice].end(); it++) {
        cout << lista_compras->nomes_produtos[*it] << endl;
    }
}
