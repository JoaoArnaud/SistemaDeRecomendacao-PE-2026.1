#include <iostream>
#include <stdlib.h>
#include "../include/ListaCompras.h"
#include "../include/Similaridade.h"
#include "../include/Recomendacao.h"

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

            ListaCompras lc;
            inicializa_lista_compras(&lc);
            if (!lista_compras_carrega(&lc, caminho)) continue;

            cout << caminho << endl;
            cout << "numero de clientes registrados: " << lc.clientes.size() << endl;
            cout << "numero de produtos registrados: " << lc.produtos.size() << endl;

            for (int j = 0; j < 3 && j < (int)lc.clientes.size(); j++) {
                lista_compras_imprime_compras(&lc, lc.clientes[j]);
            }
        }
    }

    if (entrega == "entrega2") {
        int indice1 = (argc > 2) ? atoi(argv[2]) : 0;
        int indice2 = (argc > 3) ? atoi(argv[3]) : 1;
        int total_csvs = argc - 4;
        for (int i = 0; i < (total_csvs > 0 ? total_csvs : 1); i++) {
            const char *caminho = (total_csvs > 0) ? argv[i + 4] : "data/dados_venda_cluster_17.csv";

            ListaCompras lc;
            inicializa_lista_compras(&lc);
            if (!lista_compras_carrega(&lc, caminho)) continue;

            Similaridade sim;
            inicializa_similaridade(&sim);
            similaridade_calcula(&sim, &lc);

            cout << caminho << endl;
            for (int par = 0; par < 2; par++) {
                int a = (par == 0) ? indice1 : indice2;
                int b = (par == 0) ? indice2 : indice1;
                cout << "cliente " << a << " (" << lc.clientes[a] << "): "
                     << "produtos=" << sim.matriz_intersecao[a][a]
                     << ", intersecao[" << a << "][" << b << "]=" << sim.matriz_intersecao[a][b]
                     << ", similaridade[" << a << "][" << b << "]=" << sim.matriz_similaridade[a][b]
                     << endl;
                int mais_similar = similaridade_mais_similar(&sim, a);
                cout << "mais similar a " << a << ": " << mais_similar
                     << " (" << lc.clientes[mais_similar] << "), similaridade="
                     << sim.matriz_similaridade[a][mais_similar]
                     << " I[" << a << "][" << mais_similar << "]=" << sim.matriz_intersecao[a][mais_similar] 
                     << " P[" << a << "][" << a << "]=" << sim.matriz_intersecao[a][a] 
                     << endl;
            }
            similaridade_libera(&sim);
        }
    }

    if (entrega == "entrega3") {
        bool usa_defaults = (argc < 5);
        const char *caminho = (!usa_defaults && argc > 6) ? argv[6] : "data/dados_venda_cluster_17.csv";

        ListaCompras lc;
        inicializa_lista_compras(&lc);
        if (!lista_compras_carrega(&lc, caminho)) return 1;

        Similaridade sim;
        inicializa_similaridade(&sim);
        similaridade_calcula(&sim, &lc);

        string codigos[3];
        if (usa_defaults) {
            codigos[0] = lc.clientes[0];
            codigos[1] = lc.clientes[1];
            codigos[2] = lc.clientes[2];
        } else {
            codigos[0] = argv[2];
            codigos[1] = argv[3];
            codigos[2] = argv[4];
        }
        int k = (!usa_defaults && argc > 5) ? atoi(argv[5]) : 3;

        cout << caminho << endl;
        for (int i = 0; i < 3; i++) {
            int indice = lista_compras_indice_cliente(&lc, codigos[i]);
            cout << "recomendacoes para " << codigos[i] << " (indice interno " << indice << "):" << endl;
            vector<ItemRanking> topk = recomendacao_top_k(&sim, &lc, indice, k);
            for (int j = 0; j < (int) topk.size(); j++) {
                cout << lc.produtos[topk[j].indice_produto] << " (Rank=" << topk[j].ranqueamento << ")" << endl;
            }
        }
        similaridade_libera(&sim);
    }

    return 0;
}
