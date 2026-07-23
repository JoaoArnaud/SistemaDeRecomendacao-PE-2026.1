#include <stdlib.h>
#include "../include/similaridade.h"

void inicializa_similaridade(Similaridade *sim) {
    sim->n = 0;
    sim->m = 0;
    sim->matriz_compras = NULL;
    sim->matriz_intersecao = NULL;
    sim->matriz_similaridade = NULL;
}

void similaridade_libera(Similaridade *sim) {
    for (int i = 0; i < sim->n; i++) free(sim->matriz_compras[i]);
    free(sim->matriz_compras);

    for (int i = 0; i < sim->n; i++) free(sim->matriz_intersecao[i]);
    free(sim->matriz_intersecao);

    for (int i = 0; i < sim->n; i++) free(sim->matriz_similaridade[i]);
    free(sim->matriz_similaridade);
}

void similaridade_monta_matriz_compras(Similaridade *sim, const ListaCompras *lc) {
    sim->n = lc->cod_clientes.size();
    sim->m = lc->nomes_produtos.size();

    sim->matriz_compras = (Matriz) malloc(sim->n * sizeof(int *));
    for (int i = 0; i < sim->n; i++) {
        sim->matriz_compras[i] = (int *) calloc(sim->m, sizeof(int));
    }

    for (int i = 0; i < sim->n; i++) {
        list<int>::const_iterator it;
        for (it = lc->compras[i].begin(); it != lc->compras[i].end(); it++) {
            sim->matriz_compras[i][*it] = 1;
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

void similaridade_calcula(Similaridade *sim, const ListaCompras *lc) {
    similaridade_monta_matriz_compras(sim, lc);

    Matriz transposta = similaridade_transposta(sim->matriz_compras, sim->n, sim->m);
    sim->matriz_intersecao = similaridade_multiplica_matrizes(sim->matriz_compras, sim->n, sim->m, transposta, sim->n);

    for (int i = 0; i < sim->m; i++) free(transposta[i]);
    free(transposta);

    sim->matriz_similaridade = (MatrizDouble) malloc(sim->n * sizeof(double *));
    for (int i = 0; i < sim->n; i++) {
        sim->matriz_similaridade[i] = (double *) calloc(sim->n, sizeof(double));
    }

    for (int i = 0; i < sim->n; i++) {
        int total_produtos_i = sim->matriz_intersecao[i][i];
        for (int j = 0; j < sim->n; j++) {
            sim->matriz_similaridade[i][j] = 1.0 - (double) sim->matriz_intersecao[i][j] / total_produtos_i;
        }
    }
}

int similaridade_mais_similar(const Similaridade *sim, int indice_cliente) {
    int melhor = -1;
    for (int j = 0; j < sim->n; j++) {
        if (j == indice_cliente) continue;
        if (melhor == -1 || sim->matriz_similaridade[indice_cliente][j] < sim->matriz_similaridade[indice_cliente][melhor]) {
            melhor = j;
        }
    }
    return melhor;
}
