#include <cmath>
// std::isinf
#include <cstddef>
// std::size_t
#include <iostream>
// std::clog
#include <iterator>
// std::size
#include <vector>
// std::vector

#include "gtest/gtest.h"
// ASSERT_EQ
// ASSERT_THROW
// ASSERT_TRUE
// TEST
// RUN_ALL_TESTS
// testing::InitGoogleTest

#include "GrafoAbstrato.h"
// GrafoAbstrato
#include "MeuGrafo.h"
// MeuGrafo
#include "excecoes.h"
// ExcecaoMatrizAdjacenciaVazia
// ExcecaoMatrizAdjacenciaNaoQuadrada
// ExcecaoCustoNegativo
// ExcecaoVerticeComLaco

using std::clog;
using std::isinf;
using std::size;

using testing::InitGoogleTest;

constexpr double inf{GrafoAbstrato::inf};

TEST(TesteGrafo, Inicializacao)
{
    // Nenhuma linha
    ASSERT_THROW
    (
        (new MeuGrafo
        {{
        }}),
        
        ExcecaoMatrizAdjacenciaVazia
    );

    // Uma linha, nenhuma coluna
    ASSERT_THROW
    (
        (new MeuGrafo
        {{
            {}
        }}),
        
        ExcecaoMatrizAdjacenciaNaoQuadrada
    );
    
    // Uma linha, múltiplas colunas
    ASSERT_THROW
    (
        (new MeuGrafo
        {{
            {0, 1}
        }}),
        
        ExcecaoMatrizAdjacenciaNaoQuadrada
    );

    // Matriz não quadrada
    ASSERT_THROW
    (
        (new MeuGrafo
        {{
            {inf,   1,      1,      1},
            {1,     inf,    1,      1},
            {1,     1,      inf,    1},
        }}),

        ExcecaoMatrizAdjacenciaNaoQuadrada
    );

    // Matriz quadrada incompleta
    ASSERT_THROW
    (
        (new MeuGrafo
        {{
            {inf,   1,      1,      1},
            {1,     inf,    1},
            {1,     1,      inf,    1},
            {1,     1,      1,      inf}
        }}),

        ExcecaoMatrizAdjacenciaNaoQuadrada
    );

    // Custo negativo
    ASSERT_THROW
    (
        (new MeuGrafo
        {{
            {inf,   1,      1,      1},
            {1,     inf,    1,      1},
            {1,     1,      inf,    1},
            {1,     1,      -1,     inf}
        }}),

        ExcecaoCustoNegativo
    );

    // Vértice com laço
    ASSERT_THROW
    (
        (new MeuGrafo
        {{
            {inf,   1,      1,  1},
            {1,     inf,    1,  1},
            {1,     1,      2,  1},
            {1,     1,      1,  inf}
        }}),

        ExcecaoVerticeComLaco
    );
}

TEST(TesteGrafo, QuantidadeVertices)
{
    // http://graphonline.ru/en/?graph=utTbxodBMrQDICua
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0
            /* 0 */{    inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeVertices(), 1);

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=RMsOPsWuCIswbBAJ
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      inf,    inf},
            /* 1 */{    inf,    inf,    1,      inf},
            /* 2 */{    inf,    inf,    inf,    11},
            /* 3 */{    inf,    inf,    inf,    inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeVertices(), 4);

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=IrxAXXtFwKvwLEvf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      8,      inf},
            /* 1 */{    5,      inf,    9,      2},
            /* 2 */{    8,      9,      inf,    6},
            /* 3 */{    inf,    2,      6,      inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeVertices(), 4);

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=cGnAGPNIHorWtYXf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3       4       5       6
            /* 0 */{    inf,    2,      inf,    4,      inf,    inf,    inf},
            /* 1 */{    inf,    inf,    inf,    3,      10,     inf,    inf},
            /* 2 */{    4,      inf,    inf,    inf,    inf,    5,      inf},
            /* 3 */{    inf,    inf,    2,      inf,    2,      8,      4},
            /* 4 */{    inf,    inf,    inf,    inf,    inf,    inf,    6},
            /* 5 */{    inf,    inf,    inf,    inf,    inf,    inf,    inf},
            /* 6 */{    inf,    inf,    inf,    inf,    inf,    1,      inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeVertices(), 7);

        delete grafo;
    }
}

TEST(TesteGrafo, QuantidadeArestasVertice)
{
    // http://graphonline.ru/en/?graph=utTbxodBMrQDICua
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0
            /* 0 */{    inf}
            }}
        };

        std::vector<std::size_t> const esperados{0};

        for
        (
            std::size_t vertice{0};
            vertice < grafo->quantidadeVertices();
            ++vertice
        )
        {
            ASSERT_EQ
            (
                grafo->quantidadeArestas(vertice),
                esperados[vertice]
            );
        }

        for (std::size_t const vertice: {1, 10, 100})
            ASSERT_THROW
            (
                grafo->quantidadeArestas(vertice),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=RMsOPsWuCIswbBAJ
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      inf,    inf},
            /* 1 */{    inf,    inf,    1,      inf},
            /* 2 */{    inf,    inf,    inf,    11},
            /* 3 */{    inf,    inf,    inf,    inf}
            }}
        };

        std::vector<std::size_t> const esperados{1, 1, 1, 0};

        for
        (
            std::size_t vertice{0};
            vertice < grafo->quantidadeVertices();
            ++vertice
        )
        {
            ASSERT_EQ
            (
                grafo->quantidadeArestas(vertice),
                esperados[vertice]
            );
        }

        for (std::size_t const vertice: {4, 10, 100})
            ASSERT_THROW
            (
                grafo->quantidadeArestas(vertice),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=IrxAXXtFwKvwLEvf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      8,      inf},
            /* 1 */{    5,      inf,    9,      2},
            /* 2 */{    8,      9,      inf,    6},
            /* 3 */{    inf,    2,      6,      inf}
            }}
        };

        std::vector<std::size_t> const esperados{2, 3, 3, 2};

        for
        (
            std::size_t vertice{0};
            vertice < grafo->quantidadeVertices();
            ++vertice
        )
        {
            ASSERT_EQ
            (
                grafo->quantidadeArestas(vertice),
                esperados[vertice]
            );
        }

        for (std::size_t const vertice: {4, 10, 100})
            ASSERT_THROW
            (
                grafo->quantidadeArestas(vertice),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=cGnAGPNIHorWtYXf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3       4       5       6
            /* 0 */{    inf,    2,      inf,    4,      inf,    inf,    inf},
            /* 1 */{    inf,    inf,    inf,    3,      10,     inf,    inf},
            /* 2 */{    4,      inf,    inf,    inf,    inf,    5,      inf},
            /* 3 */{    inf,    inf,    2,      inf,    2,      8,      4},
            /* 4 */{    inf,    inf,    inf,    inf,    inf,    inf,    6},
            /* 5 */{    inf,    inf,    inf,    inf,    inf,    inf,    inf},
            /* 6 */{    inf,    inf,    inf,    inf,    inf,    1,      inf}
            }}
        };

        std::vector<std::size_t> const esperados{2, 2, 2, 4, 1, 0, 1};

        for
        (
            std::size_t vertice{0};
            vertice < grafo->quantidadeVertices();
            ++vertice
        )
        {
            ASSERT_EQ
            (
                grafo->quantidadeArestas(vertice),
                esperados[vertice]
            );
        }

        for (std::size_t const vertice: {7, 10, 100})
            ASSERT_THROW
            (
                grafo->quantidadeArestas(vertice),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }
}

TEST(TesteGrafo, QuantidadeArestas)
{
    // http://graphonline.ru/en/?graph=utTbxodBMrQDICua
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0
            /* 0 */{    inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeArestas(), 0);

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=RMsOPsWuCIswbBAJ
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      inf,    inf},
            /* 1 */{    inf,    inf,    1,      inf},
            /* 2 */{    inf,    inf,    inf,    11},
            /* 3 */{    inf,    inf,    inf,    inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeArestas(), 3);

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=IrxAXXtFwKvwLEvf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      8,      inf},
            /* 1 */{    5,      inf,    9,      2},
            /* 2 */{    8,      9,      inf,    6},
            /* 3 */{    inf,    2,      6,      inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeArestas(), 10);

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=cGnAGPNIHorWtYXf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3       4       5       6
            /* 0 */{    inf,    2,      inf,    4,      inf,    inf,    inf},
            /* 1 */{    inf,    inf,    inf,    3,      10,     inf,    inf},
            /* 2 */{    4,      inf,    inf,    inf,    inf,    5,      inf},
            /* 3 */{    inf,    inf,    2,      inf,    2,      8,      4},
            /* 4 */{    inf,    inf,    inf,    inf,    inf,    inf,    6},
            /* 5 */{    inf,    inf,    inf,    inf,    inf,    inf,    inf},
            /* 6 */{    inf,    inf,    inf,    inf,    inf,    1,      inf}
            }}
        };

        ASSERT_EQ(grafo->quantidadeArestas(), 12);

        delete grafo;
    }
}

TEST(TesteGrafo, Custo)
{
    struct Aresta
    {
        std::size_t origem;
        std::size_t destino;
    };

    struct Esperado
    {
        Aresta aresta;
        double custo;
    };

    // http://graphonline.ru/en/?graph=utTbxodBMrQDICua
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0
            /* 0 */{    inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {{0, 0}, inf}
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->custo(esperado.aresta.origem, esperado.aresta.destino),
                esperado.custo
            );
        
        std::vector<Aresta> const arestas
        {
            {0, 1},
            {1, 0},
            {1, 1}
        };

        for (Aresta const& aresta: arestas)
            ASSERT_THROW
            (
                grafo->custo(aresta.origem, aresta.destino),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=RMsOPsWuCIswbBAJ
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      inf,    inf},
            /* 1 */{    inf,    inf,    1,      inf},
            /* 2 */{    inf,    inf,    inf,    11},
            /* 3 */{    inf,    inf,    inf,    inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {{0, 0}, inf},
            {{0, 1}, 5},
            {{2, 3}, 11},
            {{3, 3}, inf}
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->custo(esperado.aresta.origem, esperado.aresta.destino),
                esperado.custo
            );
        
        std::vector<Aresta> const arestas
        {
            {0, 4},
            {5, 2},
            {6, 10}
        };

        for (Aresta const& aresta: arestas)
            ASSERT_THROW
            (
                grafo->custo(aresta.origem, aresta.destino),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=IrxAXXtFwKvwLEvf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      8,      inf},
            /* 1 */{    5,      inf,    9,      2},
            /* 2 */{    8,      9,      inf,    6},
            /* 3 */{    inf,    2,      6,      inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {{0, 0}, inf},
            {{0, 1}, 5},
            {{2, 3}, 6},
            {{3, 3}, inf}
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->custo(esperado.aresta.origem, esperado.aresta.destino),
                esperado.custo
            );
        
        std::vector<Aresta> const arestas
        {
            {0, 4},
            {5, 2},
            {6, 10}
        };

        for (Aresta const& aresta: arestas)
            ASSERT_THROW
            (
                grafo->custo(aresta.origem, aresta.destino),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=cGnAGPNIHorWtYXf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3       4       5       6
            /* 0 */{    inf,    2,      inf,    4,      inf,    inf,    inf},
            /* 1 */{    inf,    inf,    inf,    3,      10,     inf,    inf},
            /* 2 */{    4,      inf,    inf,    inf,    inf,    5,      inf},
            /* 3 */{    inf,    inf,    2,      inf,    2,      8,      4},
            /* 4 */{    inf,    inf,    inf,    inf,    inf,    inf,    6},
            /* 5 */{    inf,    inf,    inf,    inf,    inf,    inf,    inf},
            /* 6 */{    inf,    inf,    inf,    inf,    inf,    1,      inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {{0, 0}, inf},
            {{0, 1}, 2},
            {{2, 3}, inf},
            {{4, 6}, 6},
            {{6, 5}, 1}
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->custo(esperado.aresta.origem, esperado.aresta.destino),
                esperado.custo
            );
        
        std::vector<Aresta> const arestas
        {
            {0, 7},
            {10, 2},
            {10, 100}
        };

        for (Aresta const& aresta: arestas)
            ASSERT_THROW
            (
                grafo->custo(aresta.origem, aresta.destino),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }
}

TEST(TesteGrafo, MenoresDistancias)
{
    struct Esperado
    {
        std::size_t origem;
        std::vector<double> menoresDistancias;
    };

    // http://graphonline.ru/en/?graph=utTbxodBMrQDICua
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0
            /* 0 */{    inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {0, {0}}
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->menoresDistancias(esperado.origem),
                esperado.menoresDistancias
            );
        
        for (std::size_t const origem: {1, 10, 100})
            ASSERT_THROW
            (
                grafo->menoresDistancias(origem),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=RMsOPsWuCIswbBAJ
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      inf,    inf},
            /* 1 */{    inf,    inf,    1,      inf},
            /* 2 */{    inf,    inf,    inf,    11},
            /* 3 */{    inf,    inf,    inf,    inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {0, {0, 5, 6, 17}},
            {3, {inf, inf, inf, 0}},
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->menoresDistancias(esperado.origem),
                esperado.menoresDistancias
            );
        
        for (std::size_t const origem: {4, 10, 100})
            ASSERT_THROW
            (
                grafo->quantidadeArestas(origem),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=IrxAXXtFwKvwLEvf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3
            /* 0 */{    inf,    5,      8,      inf},
            /* 1 */{    5,      inf,    9,      2},
            /* 2 */{    8,      9,      inf,    6},
            /* 3 */{    inf,    2,      6,      inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {0, {0, 5, 8, 7}},
            {3, {7, 2, 6, 0}}
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->menoresDistancias(esperado.origem),
                esperado.menoresDistancias
            );
        
        for (std::size_t const origem: {4, 10, 100})
            ASSERT_THROW
            (
                grafo->menoresDistancias(origem),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }

    // http://graphonline.ru/en/?graph=cGnAGPNIHorWtYXf
    {
        GrafoAbstrato const* const grafo
        {
            new MeuGrafo
            {{
            //          0       1       2       3       4       5       6
            /* 0 */{    inf,    2,      inf,    4,      inf,    inf,    inf},
            /* 1 */{    inf,    inf,    inf,    3,      10,     inf,    inf},
            /* 2 */{    4,      inf,    inf,    inf,    inf,    5,      inf},
            /* 3 */{    inf,    inf,    2,      inf,    2,      8,      4},
            /* 4 */{    inf,    inf,    inf,    inf,    inf,    inf,    6},
            /* 5 */{    inf,    inf,    inf,    inf,    inf,    inf,    inf},
            /* 6 */{    inf,    inf,    inf,    inf,    inf,    1,      inf}
            }}
        };

        std::vector<Esperado> const esperados
        {
            {0, {0, 2, 6, 4, 6, 9, 8}},
            {2, {4, 6, 0, 8, 10, 5, 12}},
            {4, {inf, inf, inf, inf, 0, 7, 6}},
            {6, {inf, inf, inf, inf, inf, 1, 0}}
        };

        for (Esperado const& esperado: esperados)
            ASSERT_EQ
            (
                grafo->menoresDistancias(esperado.origem),
                esperado.menoresDistancias
            );
        
        for (std::size_t const origem: {7, 10, 100})
            ASSERT_THROW
            (
                grafo->menoresDistancias(origem),
                ExcecaoVerticeInvalido
            );

        delete grafo;
    }
}

int main(int argc, char **argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
