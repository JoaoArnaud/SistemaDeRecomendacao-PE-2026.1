import solver


def carregar_dados(caminho_arquivo):
    cod_clientes = []
    mapa_clientes = {}

    nomes_produtos = []
    mapa_produtos = {}

    # Primeira passagem: cria os clientes, produtos e mapas.
    with open(caminho_arquivo, "r", encoding="utf-8") as arquivo:
        next(arquivo)

        for linha in arquivo:
            if not linha.strip():
                continue

            campos = linha.strip().split(",", 3)

            cod_cliente = campos[1]
            cod_produto = campos[2]
            nome_produto = campos[3]

            if cod_cliente not in mapa_clientes:
                indice_cliente = len(cod_clientes)

                cod_clientes.append(cod_cliente)
                mapa_clientes[cod_cliente] = indice_cliente

            if cod_produto not in mapa_produtos:
                indice_produto = len(nomes_produtos)

                nomes_produtos.append(nome_produto)
                mapa_produtos[cod_produto] = indice_produto

    compras = []

    for _ in range(len(cod_clientes)):
        compras.append([])

    # Segunda passagem: preenche a lista de compras.
    with open(caminho_arquivo, "r", encoding="utf-8") as arquivo:
        next(arquivo)

        for linha in arquivo:
            if not linha.strip():
                continue

            campos = linha.strip().split(",", 3)

            cod_cliente = campos[1]
            cod_produto = campos[2]

            indice_cliente = mapa_clientes[cod_cliente]
            indice_produto = mapa_produtos[cod_produto]

            compras[indice_cliente].append(indice_produto)

    return (
        cod_clientes,
        mapa_clientes,
        nomes_produtos,
        mapa_produtos,
        compras,
    )


def exibir_compras(
    codigo_cliente,
    mapa_clientes,
    nomes_produtos,
    compras
):
    indice_cliente = mapa_clientes[codigo_cliente]

    print(f"\nCompras do cliente {codigo_cliente}:")

    for indice_produto in compras[indice_cliente]:
        print(nomes_produtos[indice_produto])


def main():
    caminho_arquivo = "../data/dados_venda_cluster_17.csv"

    (
        cod_clientes,
        mapa_clientes,
        nomes_produtos,
        mapa_produtos,
        compras,
    ) = carregar_dados(caminho_arquivo)

    k = int(input("Quantidade de produtos recomendados: "))

    clientes_testados = 0

    while clientes_testados < 3:
        codigo_cliente = input(
            f"\nDigite o codigo do cliente {clientes_testados + 1}: "
        )

        if codigo_cliente not in mapa_clientes:
            print("Cliente nao encontrado.")
            continue

        indice_cliente = mapa_clientes[codigo_cliente]

        exibir_compras(
            codigo_cliente,
            mapa_clientes,
            nomes_produtos,
            compras,
        )

        recomendacoes = solver.recomendar_produtos(
            cod_clientes=cod_clientes,
            mapa_clientes=mapa_clientes,
            nomes_produtos=nomes_produtos,
            mapa_produtos=mapa_produtos,
            compras=compras,
            indice_cliente=indice_cliente,
            k=k,
        )

        print(f"\nRecomendacoes para o cliente {codigo_cliente}:")

        for indice_produto in recomendacoes:
            print(nomes_produtos[indice_produto])

        clientes_testados += 1


if __name__ == "__main__":
    main()