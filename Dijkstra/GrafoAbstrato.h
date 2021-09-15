#ifndef DEC0006_GRAFO_ABSTRATO_H
#define DEC0006_GRAFO_ABSTRATO_H

#include <cstddef>
// std::size_t
#include <limits>
// std::numeric_limits
#include <vector>
// std::vector

/**
 * @brief A interface de um grafo representado por uma matriz de adjacência de
 * arestas direcionais.
 * 
 */
class GrafoAbstrato
{
public:
    // A matriz de adjacência é uma matriz de custos do tipo double.
    using MatrizAdjacencia = std::vector<std::vector<double>>;
    // O valor para um custo infinito.
    static constexpr double inf{std::numeric_limits<double>::infinity()};

    /**
     * @brief Constrói um grafo a partir de uma matriz de adjacência; lança
     * ExcecaoMatrizAdjacenciaVazia se a matriz de adjacência estiver vazia,
     * ExcecaoMatrizAdjacenciaNaoQuadrada caso não seja uma matriz quadrada,
     * ExcecaoVerticeComLaco caso algum vértice contenha um laço (ou seja, um
     * custo finito para si mesmo) ou ExcecaoCustoNegativo caso algum custo seja
     * negativo.
     * 
     * @param matrizAdjacencia A matriz de adjacência, cujos custos devem ser
     * maiores ou iguais a zero e a ausência de arestas entre dois vértices é
     * representada por inf (ou seja, um custo infinito).
     */
    GrafoAbstrato(MatrizAdjacencia const& matrizAdjacencia);
    virtual ~GrafoAbstrato();

    /**
     * @brief Obtém a quantidade de vértices no grafo.
     * 
     * @return Um inteiro maior que zero.
     */
    virtual std::size_t quantidadeVertices() const = 0;
    /**
     * @brief Obtém a quantidade de arestas que partem de um vértice; lança
     * ExcecaoVerticeInvalido caso o vértice passado não pertença ao grafo.
     * 
     * @param vertice O vértice em questão, um inteiro na faixa
     * [0, quantidadeVertices).
     * @return Um inteiro maior ou igual a zero.
     */
    virtual std::size_t quantidadeArestas(std::size_t vertice) const = 0;
    /**
     * @brief Obtém a quantidade total de arestas no grafo.
     * 
     * @return Um inteiro maior ou igual a zero.
     */
    virtual std::size_t quantidadeArestas() const = 0;

    /**
     * @brief Obtém o custo da aresta partindo do vértice \p origem até o
     * vértice \p destino; lança ExcecaoVerticeInvalido caso \p origem ou
     * \p destino não pertença ao grafo.
     * 
     * @param origem O vértice de onde parte a aresta, um inteiro na faixa
     * [0, quantidadeVertices).
     * @param destino O vértice de destino da aresta, um inteiro na faixa
     * [0, quantidadeVertices).
     * @return Um valor real maior ou igual a zero, ou inf (infinito) caso não
     * haja uma aresta partindo de \p origem a \p destino.
     */
    virtual double custo(std::size_t origem, std::size_t destino) const = 0;

    /**
     * @brief Obtém um vetor de distâncias cujos índices representam cada
     * vértice do grafo e cujos valores representam as distâncias mínimas entre
     * o vértice \p origem até cada um dos vértices; lança
     * ExcecaoVerticeInvalido caso o vértice \p origem não pertença ao grafo.
     * 
     * Dica: utilizar std::priority_queue (fila de prioridade), da biblioteca
     * <queue>, que mantém seus valores sempre ordenados.
     * 
     * @param origem O vértice de origem, um inteiro na faixa
     * [0, quantidadeVertices).
     * @return Um vetor de números reais representado as distâncias; as
     * distâncias devem ser maiores ou iguais a 0, ou inf (infinito, ou seja,
     * representando que o respectivo vértice é inalcançável a partir de
     * \p origem).
     */
    virtual std::vector<double> menoresDistancias(std::size_t origem) const = 0;

protected:
    MatrizAdjacencia _matrizAdjacencia;
};

#endif
