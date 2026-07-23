#include <stdlib.h>
#include "../include/similaridade.h"

void inicializaSimilaridade(Similaridade *similaridade) {
    similaridade->n = 0;
    similaridade->m = 0;
    similaridade->matriz_compras = NULL;
    similaridade->matriz_intersecao = NULL;
    similaridade->matriz_similaridade = NULL;
}

void freeSimilaridade(Similaridade *similaridade) {
    for (int i = 0; i < similaridade->n; i++) free(similaridade->matriz_compras[i]);
    free(similaridade->matriz_compras);

    for (int i = 0; i < similaridade->n; i++) free(similaridade->matriz_intersecao[i]);
    free(similaridade->matriz_intersecao);

    for (int i = 0; i < similaridade->n; i++) free(similaridade->matriz_similaridade[i]);
    free(similaridade->matriz_similaridade);
}

void similaridade_monta_matriz_compras(Similaridade *similaridade, const ListaCompras *lista_compras) {
    similaridade->n = lista_compras->cod_clientes.size();
    similaridade->m = lista_compras->nomes_produtos.size();

    similaridade->matriz_compras = (Matriz) malloc(similaridade->n * sizeof(int *));
    for (int i = 0; i < similaridade->n; i++) {
        similaridade->matriz_compras[i] = (int *) calloc(similaridade->m, sizeof(int));
    }

    for (int i = 0; i < similaridade->n; i++) {
        list<int>::const_iterator it;
        for (it = lista_compras->compras[i].begin(); it != lista_compras->compras[i].end(); it++) {
            similaridade->matriz_compras[i][*it] = 1;
        }
    }
}

Matriz similaridade_transposta(Matriz a, int linhas, int colunas) {
    Matriz t = (Matriz) malloc(colunas * sizeof(int *));
    for (int j = 0; j < colunas; j++) {
        t[j] = (int *) calloc(linhas, sizeof(int));
    }

    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            t[j][i] = a[i][j];
    return t;
}

Matriz similaridade_multiplica_matrizes(Matriz a, int linhas_a, int colunas_a, Matriz b, int colunas_b) {
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
    similaridade_monta_matriz_compras(similaridade, lista_compras);

    Matriz transposta = similaridade_transposta(similaridade->matriz_compras, similaridade->n, similaridade->m);
    similaridade->matriz_intersecao = similaridade_multiplica_matrizes(similaridade->matriz_compras, similaridade->n, similaridade->m, transposta, similaridade->n);

    for (int i = 0; i < similaridade->m; i++) free(transposta[i]);
    free(transposta);

    similaridade->matriz_similaridade = (MatrizDouble) malloc(similaridade->n * sizeof(double *));
    for (int i = 0; i < similaridade->n; i++) {
        similaridade->matriz_similaridade[i] = (double *) calloc(similaridade->n, sizeof(double));
    }

    for (int i = 0; i < similaridade->n; i++) {
        int total_produtos_i = similaridade->matriz_intersecao[i][i];
        for (int j = 0; j < similaridade->n; j++) {
            similaridade->matriz_similaridade[i][j] = 1.0 - (double) similaridade->matriz_intersecao[i][j] / total_produtos_i;
        }
    }
}

int similaridade_mais_similar(const Similaridade *similaridade, int indice_cliente) {
    int melhor = -1;
    for (int j = 0; j < similaridade->n; j++) {
        if (j == indice_cliente) continue;
        if (melhor == -1 || similaridade->matriz_similaridade[indice_cliente][j] < similaridade->matriz_similaridade[indice_cliente][melhor]) {
            melhor = j;
        }
    }
    return melhor;
}
