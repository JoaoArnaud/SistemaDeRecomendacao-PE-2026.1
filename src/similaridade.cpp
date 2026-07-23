#include <stdlib.h>
#include "../include/similaridade.h"

void inicializaSimilaridade(Similaridade *similaridade) {
    similaridade->linha = 0;
    similaridade->coluna = 0;
    similaridade->matriz_compras = NULL;
    similaridade->matriz_intersecao = NULL;
    similaridade->matriz_similaridade = NULL;
}

void freeSimilaridade(Similaridade *similaridade) {

    for (int i = 0; i < similaridade->linha; i++) free(similaridade->matriz_compras[i]);
    free(similaridade->matriz_compras);

    for (int i = 0; i < similaridade->linha; i++) free(similaridade->matriz_intersecao[i]);
    free(similaridade->matriz_intersecao);

    for (int i = 0; i < similaridade->linha; i++) free(similaridade->matriz_similaridade[i]);
    free(similaridade->matriz_similaridade);
}

void geraMatrizCompras(Similaridade *similaridade, const ListaCompras *lista_compras) {
    similaridade->linha = lista_compras->cod_clientes.size();
    similaridade->coluna = lista_compras->nomes_produtos.size();

    similaridade->matriz_compras = (Matriz) malloc(similaridade->linha * sizeof(int *));
    for (int i = 0; i < similaridade->linha; i++) {
        similaridade->matriz_compras[i] = (int *) calloc(similaridade->coluna, sizeof(int));
    }

    for (int i = 0; i < similaridade->linha; i++) {
        list<int>::const_iterator it;
        for (it = lista_compras->compras[i].begin(); it != lista_compras->compras[i].end(); it++) {
            similaridade->matriz_compras[i][*it] = 1;
        }
    }
}

Matriz getTransposta(Matriz a, int linhas, int colunas) {
    Matriz transposta = (Matriz) malloc(colunas * sizeof(int *));
    for (int j = 0; j < colunas; j++) {
        transposta[j] = (int *) calloc(linhas, sizeof(int));
    }

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            transposta[j][i] = a[i][j];
    return transposta;
}

Matriz getProdutoMatrizes(Matriz a, int linhas_a, int colunas_a, Matriz b, int colunas_b) {
    Matriz c = (Matriz) malloc(linhas_a * sizeof(int *));
    for (int i = 0; i < linhas_a; i++) {
        c[i] = (int *) calloc(colunas_b, sizeof(int));
    }

    for (int i = 0; i < linhas_a; i++)
        for (int j = 0; j < colunas_b; j++)
            for (int k = 0; k < colunas_a; k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

void similaridade_calista_comprasula(Similaridade *similaridade, const ListaCompras *lista_compras) {
    geraMatrizCompras(similaridade, lista_compras);

    Matriz transposta = getTransposta(similaridade->matriz_compras, similaridade->linha, similaridade->coluna);
    similaridade->matriz_intersecao = getProdutoMatrizes(similaridade->matriz_compras, similaridade->linha, similaridade->coluna, transposta, similaridade->linha);

    for (int i = 0; i < similaridade->coluna; i++) free(transposta[i]);
    free(transposta);

    similaridade->matriz_similaridade = (MatrizDouble) malloc(similaridade->linha * sizeof(double *));
    for (int i = 0; i < similaridade->linha; i++) {
        similaridade->matriz_similaridade[i] = (double *) calloc(similaridade->linha, sizeof(double));
    }

    for (int i = 0; i < similaridade->linha; i++) {
        int total_produtos_i = similaridade->matriz_intersecao[i][i];
        for (int j = 0; j < similaridade->linha; j++) {
            similaridade->matriz_similaridade[i][j] = 1.0 - (double) similaridade->matriz_intersecao[i][j] / total_produtos_i;
        }
    }
}

int getMaisSimilar(const Similaridade *similaridade, int indice_cliente) {
    int melhor = -1;
    for (int j = 0; j < similaridade->linha; j++) {
        if (j == indice_cliente) continue;
        if (melhor == -1 || similaridade->matriz_similaridade[indice_cliente][j] < similaridade->matriz_similaridade[indice_cliente][melhor]) {
            melhor = j;
        }
    }
    return melhor;
}
