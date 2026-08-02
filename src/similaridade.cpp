#include <stdlib.h>
#include <algorithm>
#include <vector>
#include "../include/similaridade.h"

void freeMatrizCSR(MatrizCSR *matriz) {
    free(matriz->values);
    free(matriz->col_index);
    free(matriz->row_ptr);

    matriz->values = nullptr;
    matriz->col_index = nullptr;
    matriz->row_ptr = nullptr;
    matriz->linhas = 0;
    matriz->colunas = 0;
    matriz->quantidade_nao_nulos = 0;
}

void freeSimilaridadeCSR(SimilaridadeCSR *similaridade) {
    freeMatrizCSR(&similaridade->matriz_compras);
    freeMatrizCSR(&similaridade->matriz_intersecao);
    similaridade->linha_matriz = 0;
    similaridade->coluna_matriz = 0;
}

MatrizCSR geraMatrizComprasCSR(const ListaCompras *lista_compras) {
    MatrizCSR matriz_compras;
    matriz_compras.linhas = lista_compras->cod_clientes.size();
    matriz_compras.colunas = lista_compras->nomes_produtos.size();

    std::vector<int> values;
    std::vector<int> col_index;
    matriz_compras.row_ptr = (int *) calloc(matriz_compras.linhas + 1, sizeof(int));

    for (int i = 0; i < matriz_compras.linhas; i++) {
        std::vector<int> produtos(lista_compras->compras[i].begin(), lista_compras->compras[i].end());
        std::sort(produtos.begin(), produtos.end());
        produtos.erase(std::unique(produtos.begin(), produtos.end()), produtos.end());

        for (int j = 0; j < (int) produtos.size(); j++) {
            values.push_back(1);
            col_index.push_back(produtos[j]);
        }

        matriz_compras.row_ptr[i + 1] = values.size();
    }

    matriz_compras.quantidade_nao_nulos = values.size();
    matriz_compras.values = (int *) malloc(matriz_compras.quantidade_nao_nulos * sizeof(int));
    matriz_compras.col_index = (int *) malloc(matriz_compras.quantidade_nao_nulos * sizeof(int));

    for (int i = 0; i < matriz_compras.quantidade_nao_nulos; i++) {
        matriz_compras.values[i] = values[i];
        matriz_compras.col_index[i] = col_index[i];
    }

    return matriz_compras;
}

MatrizCSR getMatrizIntersecaoCSR(const MatrizCSR *matriz_compras) {
    MatrizCSR matriz_intersecao;
    matriz_intersecao.linhas = matriz_compras->linhas;
    matriz_intersecao.colunas = matriz_compras->linhas;
    matriz_intersecao.row_ptr = (int *) calloc(matriz_intersecao.linhas + 1, sizeof(int));

    std::vector<int> values;
    std::vector<int> col_index;
    int cont = 0;

    for (int i = 0; i < matriz_compras->linhas; i++) {
        // Se a linha i estiver vazia, toda a linha i do produto sera zero.
        if (matriz_compras->row_ptr[i] == matriz_compras->row_ptr[i + 1]) {
            matriz_intersecao.row_ptr[i + 1] = cont;
            continue;
        }

        for (int j = 0; j < matriz_compras->linhas; j++) {
            int soma = 0;
            int p = matriz_compras->row_ptr[i];
            int q = matriz_compras->row_ptr[j];
            int fim_i = matriz_compras->row_ptr[i + 1];
            int fim_j = matriz_compras->row_ptr[j + 1];

            while (p < fim_i && q < fim_j) {
                if (matriz_compras->col_index[p] == matriz_compras->col_index[q]) {
                    soma += matriz_compras->values[p] * matriz_compras->values[q];
                    p++;
                    q++;
                } else if (matriz_compras->col_index[p] < matriz_compras->col_index[q]) {
                    p++;
                } else {
                    q++;
                }
            }

            if (soma != 0) {
                values.push_back(soma);
                col_index.push_back(j);
                cont++;
            }
        }

        matriz_intersecao.row_ptr[i + 1] = cont;
    }

    matriz_intersecao.quantidade_nao_nulos = cont;
    matriz_intersecao.values = (int *) malloc(matriz_intersecao.quantidade_nao_nulos * sizeof(int));
    matriz_intersecao.col_index = (int *) malloc(matriz_intersecao.quantidade_nao_nulos * sizeof(int));

    for (int i = 0; i < matriz_intersecao.quantidade_nao_nulos; i++) {
        matriz_intersecao.values[i] = values[i];
        matriz_intersecao.col_index[i] = col_index[i];
    }

    return matriz_intersecao;
}

int getValorMatrizCSR(const MatrizCSR *matriz, int linha, int coluna) {
    for (int k = matriz->row_ptr[linha]; k < matriz->row_ptr[linha + 1]; k++) {

        if (matriz->col_index[k] == coluna) { 
            return matriz->values[k]; 
        }

        if (matriz->col_index[k] > coluna) {
            break;
        }
    }

    return 0;
}

void calculaMatrizSimilaridadeCSR(SimilaridadeCSR *similaridade, const ListaCompras *lista_compras) {
    similaridade->linha_matriz = lista_compras->cod_clientes.size();
    similaridade->coluna_matriz = lista_compras->nomes_produtos.size();
    similaridade->matriz_compras = geraMatrizComprasCSR(lista_compras);
    similaridade->matriz_intersecao = getMatrizIntersecaoCSR(&similaridade->matriz_compras);
}

double getValorSimilaridadeCSR(const SimilaridadeCSR *similaridade, int indice_cliente_i, int indice_cliente_j) {
    int total_produtos_i = getValorMatrizCSR(&similaridade->matriz_intersecao, indice_cliente_i, indice_cliente_i);

    if (total_produtos_i == 0) return 1.0;

    int intersecao = getValorMatrizCSR(
        &similaridade->matriz_intersecao,
        indice_cliente_i,
        indice_cliente_j
    );

    return 1.0 - (double) intersecao / total_produtos_i;
}

int getMaisSimilarCSR(const SimilaridadeCSR *similaridade, int indice_cliente) {
    int melhor = -1;

    for (int k = similaridade->matriz_intersecao.row_ptr[indice_cliente];
         k < similaridade->matriz_intersecao.row_ptr[indice_cliente + 1]; k++) {
        int j = similaridade->matriz_intersecao.col_index[k];
        if (j == indice_cliente) continue;

        if (melhor == -1 ||
            getValorSimilaridadeCSR(similaridade, indice_cliente, j) <
            getValorSimilaridadeCSR(similaridade, indice_cliente, melhor)) {
            melhor = j;
        }
    }

    if (melhor == -1) {
        for (int j = 0; j < similaridade->linha_matriz; j++) {
            if (j != indice_cliente) return j;
        }
    }

    return melhor;
}
