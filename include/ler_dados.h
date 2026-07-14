#ifndef LER_DADOS_H
#define LER_DADOS_H

typedef struct {
    char data_compra[9];
    char cod_cliente[9];
    char cod_produto[6];
    char nome_produto[100];
} RegistroCompra;

typedef struct {
    RegistroCompra *registros;
    int quantidade;
} DadosCompras;

DadosCompras lerArquivo(char *caminho);

#endif // LER_DADOS_H
