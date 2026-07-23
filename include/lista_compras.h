#ifndef LISTA_COMPRAS_H
#define LISTA_COMPRAS_H

#include <vector>
#include <list>
#include <map>
#include <string>

typedef struct {
    std::vector<std::string> cod_clientes;
    std::map<std::string, int> mapa_clientes;
    std::vector<std::string> nomes_produtos;
    std::map<std::string, int> mapa_produtos;
    std::vector<std::list<int>> compras; // lista de identificadores de produtos comprados por cada cliente
} ListaCompras;

void inicializaListaCompras(ListaCompras *lista_compras);
bool carregarDados(ListaCompras *lista_compras, const char *caminho_arquivo);
int  getIndexCliente(const ListaCompras *lista_compras, const std::string &cod_cliente);
int  getIndexProduto(const ListaCompras *lista_compras, const std::string &cod_produto);
void exibirCompras(const ListaCompras *lista_compras, const std::string &cod_cliente);

#endif
