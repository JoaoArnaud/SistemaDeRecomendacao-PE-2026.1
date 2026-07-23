#include <iostream>
#include <stdlib.h>
#include "../include/lista_compras.h"
#include "../include/similaridade.h"
#include "../include/recomendacao.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "uso: " << argv[0] << " entrega1 CSV/CSV'S" << endl << "     OU" << endl;
        cout << "     " << argv[0] << " entrega2 id_cliente1 id_cliente2 CSV/CSV'S" << endl << "     OU" << endl;
        cout << "     " << argv[0] << " entrega3 cod_cliente1 cod_cliente2 cod_cliente3 k(recomendacoes) CSV/CSV'S" << endl;
        cout << "entregas disponiveis: entrega1, entrega2, entrega3" << endl;
        cout << "para cada entrega, existem valores default para os parametros caso nao sejam passados" << endl;
        return 1;
    }

    string entrega = argv[1];

    if (entrega != "entrega1" && entrega != "entrega2" && entrega != "entrega3") {
        cout << "entrega desconhecida: " << entrega << endl;
        cout << "entregas disponiveis: entrega1, entrega2, entrega3" << endl;
        return 1;
    }

    if (entrega == "entrega1") {
        int total_csvs = argc - 2;
        for (int i = 0; i < (total_csvs > 0 ? total_csvs : 1); i++) {
            const char *caminho = (total_csvs > 0) ? argv[i + 2] : "data/dados_venda_cluster_17.csv";

            ListaCompras lista_compras;
            inicializaListaCompras(&lista_compras);
            if (!carregarDados(&lista_compras, caminho)) continue;

            cout << caminho << endl;
            cout << "numero de clientes registrados: " << lista_compras.cod_clientes.size() << endl;
            cout << "numero de produtos registrados: " << lista_compras.nomes_produtos.size() << endl;

            for (int j = 0; j < 3 && j < (int)lista_compras.cod_clientes.size(); j++) {
                exibirCompras(&lista_compras, lista_compras.cod_clientes[j]);
            }
        }
    }

    if (entrega == "entrega2") {
        int indice1 = (argc > 2) ? atoi(argv[2]) : 0;
        int indice2 = (argc > 3) ? atoi(argv[3]) : 1;
        int total_csvs = argc - 4;
        for (int i = 0; i < (total_csvs > 0 ? total_csvs : 1); i++) {
            const char *caminho = (total_csvs > 0) ? argv[i + 4] : "data/dados_venda_cluster_17.csv";

            ListaCompras lista_compras;
            inicializaListaCompras(&lista_compras);
            if (!carregarDados(&lista_compras, caminho)) continue;

            Similaridade similaridade;
            inicializaSimilaridade(&similaridade);
            calculaMatrizSimilaridade(&similaridade, &lista_compras);

            cout << caminho << endl;
            for (int par = 0; par < 2; par++) {
                int a = (par == 0) ? indice1 : indice2;
                int b = (par == 0) ? indice2 : indice1;
                cout << "cliente " << a << " (" << lista_compras.cod_clientes[a] << "): "
                     << "produtos=" << similaridade.matriz_intersecao[a][a]
                     << ", intersecao[" << a << "][" << b << "]=" << similaridade.matriz_intersecao[a][b]
                     << ", similaridade[" << a << "][" << b << "]=" << similaridade.matriz_similaridade[a][b]
                     << endl;
                int mais_similar = getMaisSimilar(&similaridade, a);
                cout << "mais similar a " << a << ": " << mais_similar
                     << " (" << lista_compras.cod_clientes[mais_similar] << "), similaridade="
                     << similaridade.matriz_similaridade[a][mais_similar]
                     << " I[" << a << "][" << mais_similar << "]=" << similaridade.matriz_intersecao[a][mais_similar] 
                     << " P[" << a << "][" << a << "]=" << similaridade.matriz_intersecao[a][a] 
                     << endl;
            }
            freeSimilaridade(&similaridade);
        }
    }

    if (entrega == "entrega3") {
        bool usa_defaults = (argc < 5);
        const char *caminho = (!usa_defaults && argc > 6) ? argv[6] : "data/dados_venda_cluster_17.csv";

        ListaCompras lista_compras;
        inicializaListaCompras(&lista_compras);
        if (!carregarDados(&lista_compras, caminho)) return 1;

        Similaridade similaridade;
        inicializaSimilaridade(&similaridade);
        calculaMatrizSimilaridade(&similaridade, &lista_compras);

        string codigos[3];
        if (usa_defaults) {
            codigos[0] = lista_compras.cod_clientes[0];
            codigos[1] = lista_compras.cod_clientes[1];
            codigos[2] = lista_compras.cod_clientes[2];
        } else {
            codigos[0] = argv[2];
            codigos[1] = argv[3];
            codigos[2] = argv[4];
        }
        int k = (!usa_defaults && argc > 5) ? atoi(argv[5]) : 3;

        cout << caminho << endl;
        for (int i = 0; i < 3; i++) {
            int indice = getIndexCliente(&lista_compras, codigos[i]);
            cout << "recomendacoes para " << codigos[i] << " (indice interno " << indice << "):" << endl;
            vector<ItemRanking> topk = recomendacao_top_k(&similaridade, &lista_compras, indice, k);
            for (int j = 0; j < (int) topk.size(); j++) {
                cout << lista_compras.nomes_produtos[topk[j].indice_produto] << " (Rank=" << topk[j].ranqueamento << ")" << endl;
            }
        }
        freeSimilaridade(&similaridade);
    }

    return 0;
}
