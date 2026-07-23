#ifndef LISTA_COMPRAS_H
#define LISTA_COMPRAS_H

#include <vector>
#include <list>
#include <map>
#include <string>
using namespace std;

typedef struct {
    vector<string> cod_clientes;
    map<string, int> mapa_clientes;
    vector<string> nomes_produtos;
    map<string, int> mapa_produtos;
    vector<list<int>> compras; // lista de identificadores de produtos comprados por cada cliente
} ListaCompras;

void inicializa_lista_compras(ListaCompras *lista_compras);
bool carregarDados(ListaCompras *lista_compras, const char *caminho_arquivo);
int  lista_compras_indice_cliente(const ListaCompras *lista_compras, const string &cod_cliente);
int  lista_compras_indice_produto(const ListaCompras *lista_compras, const string &cod_produto);
void lista_compras_imprime_compras(const ListaCompras *lista_compras, const string &cod_cliente);

#endif
