#ifndef DEC0006_GRAFO_EXCECOES_H
#define DEC0006_GRAFO_EXCECOES_H

#include <stdexcept>
// std::invalid_argument
// std::length_error
// std::out_of_range

/**
 * @brief Exceção lançada quando a matriz de adjacência de um grafo está vazia.
 * 
 */
class ExcecaoMatrizAdjacenciaVazia: public std::length_error
{
public:
    ExcecaoMatrizAdjacenciaVazia();
};

/**
 * @brief Exceção lançada quando a matriz de adjacência de um grafo não é
 * quadradada.
 * 
 */
class ExcecaoMatrizAdjacenciaNaoQuadrada: public std::length_error
{
public:
    ExcecaoMatrizAdjacenciaNaoQuadrada();
};

/**
 * @brief Exceção lançada quando a matriz de adjacência de um grafo contém
 * algum custo negativo.
 * 
 */
class ExcecaoCustoNegativo: public std::invalid_argument
{
public:
    ExcecaoCustoNegativo();
};

/**
 * @brief Exceção lançada quando a matriz de adjacência de um grafo contém
 * algum laço.
 * 
 */
class ExcecaoVerticeComLaco: public std::invalid_argument
{
public:
    ExcecaoVerticeComLaco();
};

/**
 * @brief Exceção lançada quando um vértice inválido é utilizado em um grafo.
 * 
 */
class ExcecaoVerticeInvalido: public std::out_of_range
{
public:
    ExcecaoVerticeInvalido();
};

#endif
