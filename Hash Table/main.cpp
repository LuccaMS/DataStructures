#include <cstddef>
// std::size_t
#include <iterator>
// std::size
#include <string>
// std::string
#include <optional>
// std::nullopt
#include <map>
// std::map
#include <utility>
// std::pair

#include "gtest/gtest.h"
// TEST
// RUN_ALL_TESTS
// testing::InitGoogleTest

#include "MinhaTabelaEspalhamento.h"
// MinhaTabelaEspalhamento
#include "Posicao.h"
// Posicao
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

using std::nullopt;
using std::size;

// Instanciação explícita de template: força - para fins de teste -
// a instanciação de todas as funções-membros, pois elas seriam instanciadas
// apenas quando chamadas.
template class TabelaEspalhamentoAbstrata<int, 1>;
template class MinhaTabelaEspalhamento<std::string, 1>;

TEST(TabelaEspalhamentoTest, Inicializacao)
{
    using T = int;
    constexpr std::size_t capacidade{7};

    TabelaEspalhamentoAbstrata<T, capacidade> const* const tabela
    {
        new MinhaTabelaEspalhamento<T, capacidade>
    };

    ASSERT_EQ(tabela->capacidade(), capacidade);
    ASSERT_EQ(tabela->quantidade(), 0);
    
    delete tabela;
}

TEST(TabelaEspalhamentoTest, InsercaoSemColisao)
{
    using T = int;
    constexpr std::size_t capacidade{5};

    TabelaEspalhamentoAbstrata<T, capacidade>* const tabela
    {
        new MinhaTabelaEspalhamento<T, capacidade>
    };

    std::map<T, Posicao> const dadosEPosicoesEsperadas
    {
        // dado     posição na tabela    tamanho da lista    posição na lista
        {0,         {0,                  1,                  1}},
        {1,         {1,                  1,                  1}},
        {2,         {2,                  1,                  1}},
        {3,         {3,                  1,                  1}},
        {4,         {4,                  1,                  1}}
    };

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const dado{dadoEPosicao.first};
        tabela->inserir(dado);
    }

    ASSERT_EQ(tabela->quantidade(), size(dadosEPosicoesEsperadas));

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const dado{dadoEPosicao.first};
        ASSERT_EQ(tabela->contem(dado), true);
    }

    for (auto const& [dado, posicaoEsperada]: dadosEPosicoesEsperadas)
        ASSERT_EQ(tabela->posicao(dado), posicaoEsperada);
    
    delete tabela;
}

TEST(TabelaEspalhamentoTest, InsercaoComColisao)
{
    using T = std::string;
    constexpr std::size_t capacidade{3};

    TabelaEspalhamentoAbstrata<T, capacidade>* const tabela
    {
        new MinhaTabelaEspalhamento<T, capacidade>
    };

    std::map<T, Posicao> const dadosEPosicoesEsperadas
    {
        // dado     posição na tabela    tamanho da lista    posição na lista
        {"AA",      {1,                  2,                  1}},
        {"AB",      {2,                  1,                  1}},
        {"AD",      {1,                  2,                  2}}
    };

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const& dado{dadoEPosicao.first};
        tabela->inserir(dado);
    }

    ASSERT_EQ(tabela->quantidade(), size(dadosEPosicoesEsperadas));

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const& dado{dadoEPosicao.first};
        ASSERT_EQ(tabela->contem(dado), true);
    }

    for (auto const& [dado, posicaoEsperada]: dadosEPosicoesEsperadas)
        ASSERT_EQ(tabela->posicao(dado), posicaoEsperada);
    
    delete tabela;
}

TEST(TabelaEspalhamentoTest, RemocaoSemColisao)
{
    using T = int;
    constexpr std::size_t capacidade{3};

    TabelaEspalhamentoAbstrata<T, capacidade>* const tabela
    {
        new MinhaTabelaEspalhamento<T, capacidade>
    };

    std::map<T, Posicao> dadosEPosicoesEsperadas
    {
        // dado     posição na tabela    tamanho da lista    posição na lista
        {0,         {0,                  1,                  1}},
        {1,         {1,                  1,                  1}},
        {2,         {2,                  1,                  1}}
    };

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const dado{dadoEPosicao.first};
        tabela->inserir(dado);
    }

    ASSERT_EQ(tabela->quantidade(), size(dadosEPosicoesEsperadas));

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const dado{dadoEPosicao.first};
        ASSERT_EQ(tabela->contem(dado), true);
    }

    for (auto const& [dado, posicaoEsperada]: dadosEPosicoesEsperadas)
        ASSERT_EQ(tabela->posicao(dado), posicaoEsperada);

    // Dado existente.
    {
        T const dadoSaindo{2};
        tabela->remover(dadoSaindo);

        --dadosEPosicoesEsperadas.at(dadoSaindo).tamanhoLista;
        dadosEPosicoesEsperadas.at(dadoSaindo).posicaoLista = nullopt;

        ASSERT_EQ(tabela->quantidade(), size(dadosEPosicoesEsperadas) - 1);
        ASSERT_EQ(tabela->contem(dadoSaindo), false);
        
        for (auto const& [dado, posicaoEsperada]: dadosEPosicoesEsperadas)
            ASSERT_EQ(tabela->posicao(dado), posicaoEsperada);
    }
    
    // Dado inexistente.
    {
        T const dadoSaindo{3};
        ASSERT_THROW(tabela->remover(dadoSaindo), ExcecaoDadoInexistente);

        ASSERT_EQ(tabela->quantidade(), size(dadosEPosicoesEsperadas) - 1);
        ASSERT_EQ(tabela->contem(dadoSaindo), false);

        ASSERT_EQ(tabela->posicao(dadoSaindo).posicaoLista, nullopt);

        for (auto const& [dado, posicaoEsperada]: dadosEPosicoesEsperadas)
            ASSERT_EQ(tabela->posicao(dado), posicaoEsperada);
    }
    
    delete tabela;
}

TEST(TabelaEspalhamentoTest, RemocaoComColisao)
{
    using T = std::string;
    constexpr std::size_t capacidade{4};

    TabelaEspalhamentoAbstrata<T, capacidade>* const tabela
    {
        new MinhaTabelaEspalhamento<T, capacidade>
    };

    std::map<T, Posicao> dadosEPosicoesEsperadas
    {
        // dado     posição na tabela    tamanho da lista    posição na lista
        {"D",       {0,                  1,                  1}},
        {"A",       {1,                  4,                  1}},
        {"B",       {2,                  3,                  1}},
        {"C",       {3,                  2,                  1}},
        {"E",       {1,                  4,                  2}},
        {"I",       {1,                  4,                  3}},
        {"M",       {1,                  4,                  4}},
        {"F",       {2,                  3,                  2}},
        {"J",       {2,                  3,                  3}},
        {"G",       {3,                  2,                  2}}
    };

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const& dado{dadoEPosicao.first};
        tabela->inserir(dado);
    }

    ASSERT_EQ(tabela->quantidade(), size(dadosEPosicoesEsperadas));

    for (std::pair<T, Posicao> const dadoEPosicao: dadosEPosicoesEsperadas)
    {
        T const& dado{dadoEPosicao.first};
        ASSERT_EQ(tabela->contem(dado), true);
    }

    for (auto const& [dado, posicaoEsperada]: dadosEPosicoesEsperadas)
        ASSERT_EQ(tabela->posicao(dado), posicaoEsperada);

    // Dado existente.
    {
        T const dadoSaindo{"C"};
        tabela->remover(dadoSaindo);

        --dadosEPosicoesEsperadas.at(dadoSaindo).tamanhoLista;
        dadosEPosicoesEsperadas.at(dadoSaindo).posicaoLista = nullopt;

        T const dadoMesmaPosicaoTabela{"G"};
        --dadosEPosicoesEsperadas.at(dadoMesmaPosicaoTabela).tamanhoLista;
        dadosEPosicoesEsperadas.at(dadoMesmaPosicaoTabela).posicaoLista = 1;

        ASSERT_EQ(tabela->quantidade(), size(dadosEPosicoesEsperadas) - 1);
        ASSERT_EQ(tabela->contem(dadoSaindo), false);
        
        for (auto const& [dado, posicaoEsperada]: dadosEPosicoesEsperadas)
            ASSERT_EQ(tabela->posicao(dado), posicaoEsperada);
    }
    
    delete tabela;
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
