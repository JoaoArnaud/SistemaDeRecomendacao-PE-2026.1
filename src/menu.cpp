#include <iostream>
#include <stdlib.h>

#include "../include/menu.h"
#include "../include/lista_compras.h"
#include "../include/similaridade.h"
#include "../include/recomendacao.h"

void executarEntrega1(const char *caminhoArquivo) {
    ListaCompras listaCompras;
    inicializaListaCompras(&listaCompras);

    if (!carregarDados(&listaCompras, caminhoArquivo)) {
        std::cout << "Erro ao carregar o arquivo.\n";
        return;
    }

    std::cout << "\nArquivo: " << caminhoArquivo << '\n';
    std::cout << "Número de clientes registrados: " << listaCompras.cod_clientes.size() << '\n';
    std::cout << "Número de produtos registrados: " << listaCompras.nomes_produtos.size() << '\n';

    // loop para solicitar o código do cliente e exibir suas compras pelo menos 3 vezes:
    for (int i = 0; i < 3 ; i++) {
        std::string codigoCliente;

        std::cout << "\nDigite o código do cliente: ";
        std::cin >> codigoCliente;

        int indiceCliente = getIndexCliente(&listaCompras, codigoCliente);

        if (indiceCliente == -1) {
            std::cout << "Cliente não encontrado: " << codigoCliente << '\n';
            return;
        }

        exibirCompras(&listaCompras, codigoCliente);
    }
}

void executarEntrega2(const char *caminhoArquivo) {
    ListaCompras listaCompras;
    inicializaListaCompras(&listaCompras);

    if (!carregarDados(&listaCompras, caminhoArquivo)) {
        std::cout << "Erro ao carregar o arquivo.\n";
        return;
    }

    int indiceCliente1;
    int indiceCliente2;

    std::cout << "\nExistem " << listaCompras.cod_clientes.size()<< " clientes.\n";

    std::cout << "Digite o índice do primeiro cliente: ";
    std::cin >> indiceCliente1;

    std::cout << "Digite o índice do segundo cliente: ";
    std::cin >> indiceCliente2;

    Similaridade similaridade;
    calculaMatrizSimilaridade(&similaridade, &listaCompras);

    std::cout << "\nCliente " << indiceCliente1 << " (" << listaCompras.cod_clientes[indiceCliente1] << "):\n";
    std::cout << "Quantidade de produtos: " << similaridade.matriz_intersecao[indiceCliente1][indiceCliente1] << '\n';
    std::cout << "Interseção com o cliente " << indiceCliente2 << ": " << similaridade.matriz_intersecao[indiceCliente1][indiceCliente2] << '\n';

    std::cout << "Similaridade: " << similaridade.matriz_similaridade[indiceCliente1][indiceCliente2] << '\n';

    int indiceMaisSimilar = getMaisSimilar(&similaridade, indiceCliente1);

    std::cout << "Cliente mais similar: " << indiceMaisSimilar << " (" << listaCompras.cod_clientes[indiceMaisSimilar] << ")\n";
    std::cout << "Valor da similaridade: " << similaridade.matriz_similaridade[indiceCliente1][indiceMaisSimilar]<< '\n';

    freeSimilaridade(&similaridade);
}

void executarEntrega3(const char *caminhoArquivo) {
    ListaCompras listaCompras;
    inicializaListaCompras(&listaCompras);

    if (!carregarDados(&listaCompras, caminhoArquivo)) {
        std::cout << "Erro ao carregar o arquivo.\n";
        return;
    }

    Similaridade similaridade;
    calculaMatrizSimilaridade(&similaridade,&listaCompras);

    std::string codigosClientes[3];
    int quantidadeRecomendacoes;

    std::cout << "\nDigite o código do primeiro cliente: ";
    std::cin >> codigosClientes[0];

    std::cout << "Digite o código do segundo cliente: ";
    std::cin >> codigosClientes[1];

    std::cout << "Digite o código do terceiro cliente: ";
    std::cin >> codigosClientes[2];

    std::cout << "Digite a quantidade de recomendações: ";
    std::cin >> quantidadeRecomendacoes;

    if (quantidadeRecomendacoes <= 0) {
        std::cout << "A quantidade de recomendações deve ser positiva.\n";
        freeSimilaridade(&similaridade);
        return;
    }

    for (int i = 0; i < 3; i++) {
        int indiceCliente = getIndexCliente(&listaCompras, codigosClientes[i]);

        if (indiceCliente == -1) {
            std::cout << "\nCliente não encontrado: " << codigosClientes[i] << '\n';
            continue;
        }

        std::cout << "\nRecomendações para " << codigosClientes[i] << " (índice interno " << indiceCliente << "):\n";

        ItemRanking *recomendacoes = getTopKRecomendacoes(&similaridade, &listaCompras, indiceCliente, quantidadeRecomendacoes);

        for (int indiceRecomendacao = 0; indiceRecomendacao < quantidadeRecomendacoes; indiceRecomendacao++) {
            ItemRanking item = recomendacoes[indiceRecomendacao];
            std::cout << listaCompras.nomes_produtos[item.indice_produto] << " (ranking = " << item.ranqueamento << ")\n";
        }

        free(recomendacoes);
    }

    freeSimilaridade(&similaridade);
}