#include <stdlib.h>
#include "../include/similaridade.h"

void freeSimilaridade(Similaridade *similaridade) {

    for (int i = 0; i < similaridade->linha_matriz; i++) free(similaridade->matriz_compras[i]);
    free(similaridade->matriz_compras);

    for (int i = 0; i < similaridade->linha_matriz; i++) free(similaridade->matriz_intersecao[i]);
    free(similaridade->matriz_intersecao);

    for (int i = 0; i < similaridade->linha_matriz; i++) free(similaridade->matriz_similaridade[i]);
    free(similaridade->matriz_similaridade);
}

void geraMatrizCompras(Similaridade *similaridade, const ListaCompras *lista_compras) {
    similaridade->linha_matriz = lista_compras->cod_clientes.size();
    similaridade->coluna_matriz = lista_compras->nomes_produtos.size();

    similaridade->matriz_compras = (Matriz) malloc(similaridade->linha_matriz * sizeof(int *));
    for (int i = 0; i < similaridade->linha_matriz; i++) {
        similaridade->matriz_compras[i] = (int *) calloc(similaridade->coluna_matriz, sizeof(int));
    }

    for (int i = 0; i < similaridade->linha_matriz; i++) {
        std::list<int>::const_iterator it;
        for (it = lista_compras->compras[i].begin(); it != lista_compras->compras[i].end(); it++) {
            similaridade->matriz_compras[i][*it] = 1;
        }
    }
}

Matriz getTransposta(Matriz a, int linhas, int colunas) {
    Matriz transposta = (Matriz) malloc(colunas * sizeof(int *)); // todo: otimizar alocação da matriz transposta
    for (int j = 0; j < colunas; j++) {
        transposta[j] = (int *) calloc(linhas, sizeof(int));
    }

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            transposta[j][i] = a[i][j];
    return transposta;
}

Matriz getProdutoMatrizes(Matriz a, int linhas_a, int colunas_a, Matriz b, int colunas_b) {
    Matriz matriz_interesecao = (Matriz) malloc(linhas_a * sizeof(int *));
    for (int i = 0; i < linhas_a; i++) {
        matriz_interesecao[i] = (int *) calloc(colunas_b, sizeof(int));
    }

    for (int i = 0; i < linhas_a; i++)
        for (int j = 0; j < colunas_b; j++)
            for (int k = 0; k < colunas_a; k++)
                matriz_interesecao[i][j] += a[i][k] * b[k][j];
    return matriz_interesecao;
}

void calculaMatrizSimilaridade(Similaridade *similaridade, const ListaCompras *lista_compras) {
    geraMatrizCompras(similaridade, lista_compras);

    Matriz transposta = getTransposta(similaridade->matriz_compras, similaridade->linha_matriz, similaridade->coluna_matriz);
    similaridade->matriz_intersecao = getProdutoMatrizes(similaridade->matriz_compras, similaridade->linha_matriz, similaridade->coluna_matriz, transposta, similaridade->linha_matriz);

    for (int i = 0; i < similaridade->coluna_matriz; i++) free(transposta[i]);
    free(transposta);

    similaridade->matriz_similaridade = (MatrizDouble) malloc(similaridade->linha_matriz * sizeof(double *));
    for (int i = 0; i < similaridade->linha_matriz; i++) {
        similaridade->matriz_similaridade[i] = (double *) calloc(similaridade->linha_matriz, sizeof(double));
    }

    for (int i = 0; i < similaridade->linha_matriz; i++) {
        int total_produtos_i = similaridade->matriz_intersecao[i][i];
        for (int j = 0; j < similaridade->linha_matriz; j++) {
            similaridade->matriz_similaridade[i][j] = 1.0 - (double) similaridade->matriz_intersecao[i][j] / total_produtos_i;
        }
    }
}

int getMaisSimilar(const Similaridade *similaridade, int indice_cliente) {
    int melhor = -1;
    for (int j = 0; j < similaridade->linha_matriz; j++) {
        if (j == indice_cliente) continue;
        if (melhor == -1 || similaridade->matriz_similaridade[indice_cliente][j] < similaridade->matriz_similaridade[indice_cliente][melhor]) {
            melhor = j;
        }
    }
    return melhor;
}
