#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../include/lista_compras.h"
#include "../include/similaridade.h"
#include "../include/recomendacao.h"

namespace py = pybind11;

PYBIND11_MODULE(solver, m) {
    m.doc() = "Módulo de integração para solver";

    m.def("calcular_similaridade", &calcular_similaridade, "Calcula a similaridade entre clientes com base em suas listas de compras");
    m.def("gerar_recomendacoes", &gerar_recomendacoes, "Gera recomendações para um cliente com base KNN");
}