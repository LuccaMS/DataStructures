#include "MeuGrafo.h"
// MeuGrafo
#include <algorithm>

#include <cstddef>
// std::size_t
#include <iterator>
// std::empty
// std::size
#include <queue>
// std::priority_queue
#include <vector>
// std::vector
#include "excecoes.cpp"
#include "excecoes.h"
// ExcecaoMatrizAdjacenciaVazia
// ExcecaoMatrizAdjacenciaNaoQuadrada
// ExcecaoCustoNegativo
// ExcecaoVerticeComLaco
// ExcecaoVerticeInvalido

//implente aqui
MeuGrafo::MeuGrafo(MatrizAdjacencia const &matrizAdjacencia) : GrafoAbstrato(matrizAdjacencia)
{
    if (this->_matrizAdjacencia.size() <= 0)
    {
        throw ExcecaoMatrizAdjacenciaVazia();
    }
    else
    {
        for (unsigned int i = 0; i < this->_matrizAdjacencia.size(); i++)
        {
            for (unsigned int j = 0; j < this->_matrizAdjacencia.at(i).size(); j++)
            {
                if (this->_matrizAdjacencia.at(i).at(j) < 0)
                {
                    throw ExcecaoCustoNegativo();
                }
                if (i == j && this->_matrizAdjacencia.at(i).at(j) != inf && this->_matrizAdjacencia.at(i).at(j) > 0)
                {
                    throw ExcecaoVerticeComLaco();
                }
            }
        }
        std::vector<int> vec = {};
        bool verify = false;
        int aux = 0;
        for (unsigned int i = 0; i < this->_matrizAdjacencia.size(); i++)
        {
            vec.push_back(this->_matrizAdjacencia.at(i).size());
        }

        if (std::adjacent_find(vec.begin(), vec.end(), std::not_equal_to<>()) == vec.end())
        {
            verify = true;
            aux = vec.at(0);
        }
        bool check_for_wrong_matrix = false;
        int a = 0;
        for (unsigned int i = 1; i < vec.size(); i++)
        {
            if (vec.at(a) != vec.at(i))
            {
                check_for_wrong_matrix = true;
                break;
            }
            a++;
        }
        if (check_for_wrong_matrix)
        {
            throw ExcecaoMatrizAdjacenciaNaoQuadrada();
        }

        if (verify)
        {
            if ((this->_matrizAdjacencia.size() + aux) % 2 != 0)
            {
                throw ExcecaoMatrizAdjacenciaNaoQuadrada();
            }
        }
    }
};

std::size_t MeuGrafo::quantidadeVertices() const
{
    int count = 0;
    for (unsigned int i = 0; i < this->_matrizAdjacencia.size(); i++)
    {
        if (this->_matrizAdjacencia.at(i).at(0) == 0)
        {
        }
        count++;
    }
    return count;
};

std::vector<double> MeuGrafo::menoresDistancias(std::size_t origem) const
{
    if (origem > (this->_matrizAdjacencia.size() - 1))
    {
        throw ExcecaoVerticeInvalido();
    }

    std::vector<double> teste = {};
    teste.at(origem) = inf;

    return {};
}

std::size_t MeuGrafo::quantidadeArestas(std::size_t v) const
{
    if (v > (this->_matrizAdjacencia.size() - 1))
    {
        throw ExcecaoVerticeInvalido();
    }

    int count = 0;
    for (unsigned int i = 0; i < this->_matrizAdjacencia.at(v).size(); i++)
    {
        if (this->_matrizAdjacencia.at(v).at(i) != inf)
        {
            count++;
        }
    }

    return count;
};

std::size_t MeuGrafo::quantidadeArestas() const
{
    int count = 0;
    for (unsigned int i = 0; i < this->_matrizAdjacencia.size(); i++)
    {
        for (unsigned int j = 0; j < this->_matrizAdjacencia.at(i).size(); j++)
        {
            if (this->_matrizAdjacencia.at(i).at(j) != inf)
            {
                count++;
            }
        }
    }
    return count;
};

double MeuGrafo::custo(std::size_t origem, std::size_t destino) const
{
    int size = this->_matrizAdjacencia.size() - 1;

    if (destino > size || origem > size)
    {
        throw ExcecaoVerticeInvalido();
    }
    else if (this->_matrizAdjacencia.at(origem).at(destino) < 0)
    {
        throw ExcecaoCustoNegativo();
    }
    else if (origem == destino)
    {
        return inf;
    }

    return this->_matrizAdjacencia.at(origem).at(destino);
};
