#ifndef DEC0006_MEU_GRAFO_H
#define DEC0006_MEU_GRAFO_H

#include <cstddef>
// std::size_t
#include <vector>
// std::vector

#include "GrafoAbstrato.h"
// GrafoAbstrato

/**
 * @brief Um grafo representado por uma matriz de adjacência de arestas
 * direcionais.
 * 
 */
class MeuGrafo final: public GrafoAbstrato
{
public:
    MeuGrafo(MatrizAdjacencia const& matrizAdjacencia);

    std::size_t quantidadeVertices() const override;
    std::size_t quantidadeArestas(std::size_t vertice) const override;
    std::size_t quantidadeArestas() const override;

    double custo(std::size_t origem, std::size_t destino) const override;

    std::vector<double> menoresDistancias(std::size_t origem) const override;
};

#endif
