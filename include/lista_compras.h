#ifndef LISTA_COMPRAS_H
#define LISTA_COMPRAS_H

#include <vector>
#include <list>
#include <map>
#include <string>
using namespace std;

typedef struct {
    vector<string> clientes;
    map<string, int> mapa_clientes;
    vector<string> produtos;
    map<string, int> mapa_produtos;
    vector<list<int>> compras;
} ListaCompras;

void inicializa_lista_compras(ListaCompras *lc);
bool lista_compras_carrega(ListaCompras *lc, const char *caminho_arquivo);
int  lista_compras_indice_cliente(const ListaCompras *lc, const string &cod_cliente);
int  lista_compras_indice_produto(const ListaCompras *lc, const string &cod_produto);
void lista_compras_imprime_compras(const ListaCompras *lc, const string &cod_cliente);

#endif
