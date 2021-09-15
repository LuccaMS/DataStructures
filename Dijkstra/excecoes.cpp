#include "excecoes.h"
// ExcecaoMatrizAdjacenciaVazia

#include <stdexcept>
// invalid_argument
// std::length_error
// std::out_of_range

ExcecaoMatrizAdjacenciaVazia::ExcecaoMatrizAdjacenciaVazia():
    std::length_error{"a matriz de adjacencia nao deve ser vazia"}
{}

ExcecaoMatrizAdjacenciaNaoQuadrada::ExcecaoMatrizAdjacenciaNaoQuadrada():
    std::length_error{"a matriz de adjacencia deve ser quadrada"}
{}

ExcecaoCustoNegativo::ExcecaoCustoNegativo():
    std::invalid_argument{"o custo nao deve ser negativo"}
{}

ExcecaoVerticeComLaco::ExcecaoVerticeComLaco():
    std::invalid_argument{"um vertice nao deve conter um laco"}
{}

ExcecaoVerticeInvalido::ExcecaoVerticeInvalido():
    std::out_of_range{"vertice invalido"}
{}
