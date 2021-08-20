#ifndef TABELA_ESPALHAMENTO_ABSTRATA_H
#define TABELA_ESPALHAMENTO_ABSTRATA_H

#include <array>
// std::array
#include <cstddef>
// std::size_t
#include <optional>
// std::nullopt

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "Posicao.h"
// Posicao

/**
 * @brief A interface de uma tabela de espalhamento.
 * 
 * @tparam T O tipo de dado armazenado na tabela.
 * @tparam _capacidade O tamanho da tabela. Tem que ser maior que 0.
 */
template<typename T, std::size_t _capacidade>
class TabelaEspalhamentoAbstrata
{
public:
    virtual ~TabelaEspalhamentoAbstrata();

    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    virtual std::size_t capacidade() const = 0;

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     * 
     * @param dado O dado a ser inserido.
     */
    virtual void inserir(T dado) = 0;
    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     * 
     * @param dado O dado a ser removido.
     */
    virtual void remover(T dado) = 0;

    /**
     * @brief Verifica se \p dado está contido na tabela.
     * 
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    virtual bool contem(T dado) const = 0;

    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t quantidade() const = 0;

    /**
     * @brief Obtém a posição de um dado na tabela e o tamanho da lista em que
     * se encontra.
     * 
     * @param dado O dado sendo buscado.
     * @return A posição do dado na tabela estando ele ou não na tabela e, caso
     * esteja, a posição na lista.
     */
    Posicao posicao(T dado) const;

protected:
    /**
     * @brief A matriz de dados.
     * 
     */
    std::array<MinhaListaEncadeada<T>, _capacidade> _tabela;

    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    virtual std::size_t funcaoEspalhamento(T dado) const = 0;
};

template<typename T, std::size_t _capacidade>
TabelaEspalhamentoAbstrata<T, _capacidade>::~TabelaEspalhamentoAbstrata() =
    default;

template<typename T, std::size_t _capacidade>
Posicao TabelaEspalhamentoAbstrata<T, _capacidade>::posicao(T const dado) const
{
    using std::nullopt;

    std::size_t const posicaoTabela{funcaoEspalhamento(dado)};

    MinhaListaEncadeada<T> const& lista{_tabela[posicaoTabela]};

    std::size_t const tamanhoLista
    {
        static_cast<std::size_t>(lista.getTamanho())
    };

    Posicao posicao{posicaoTabela, tamanhoLista};

    if(int const posicaoLista{lista.posicao(dado)}; posicaoLista >= 1)
        posicao.posicaoLista = static_cast<std::size_t>(posicaoLista);

    return posicao;
}

#endif
