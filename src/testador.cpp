#include <iostream>

#include "../include/menu.h"

int main() {
    const char *caminhoArquivo = "data/dados_venda_cluster_17.csv";
    int opcao;
    
    do {
        std::cout << "\n========== MENU ==========\n";
        std::cout << "1 - Executar entrega 1\n";
        std::cout << "2 - Executar entrega 2\n";
        std::cout << "3 - Executar entrega 3\n";
        std::cout << "0 - Sair\n";
        std::cout << "==========================\n";
        std::cout << "Escolha uma opção: ";

        std::cin >> opcao;

        switch (opcao) {
            case 1:
                executarEntrega1(caminhoArquivo);
                break;

            case 2:
                executarEntrega2(caminhoArquivo);
                break;

            case 3:
                executarEntrega3(caminhoArquivo);
                break;

            case 0:
                std::cout << "Programa encerrado.\n";
                break;

            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }

    } while (opcao != 0);

    return 0;
}