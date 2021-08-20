#ifndef DEC0006_TABELA_ESPALHAMENTO_POSICAO_H
#define DEC0006_TABELA_ESPALHAMENTO_POSICAO_H

#include <cstddef>
// std::size_t
#include <optional>
// std::nullopt
// std::optional

/**
 * @brief Armazena informações da posição de um valor em uma tabela de
 * espalhamento.
 * 
 */
struct Posicao
{
    /**
     * @brief A posição em que se encontra(ria) o valor na tabela.
     * 
     */
    std::size_t posicaoTabela;
    /**
     * @brief A quantidade de elementos na lista em que o dado se encontra(ria).
     * 
     */
    std::size_t tamanhoLista;
    /**
     * @brief A posição do valor na lista de posição \p posicaoTabela.
     * 
     */
    std::optional<std::size_t> posicaoLista;

    /**
     * @brief Constrói uma Posição.
     * 
     * @param posicaoTabela A posição em que se encontra(ria) o valor na tabela.
     * @param tamanhoLista A quantidade de elementos na lista em que o dado se
     * encontra(ria).
     * @param posicaoLista A posição opcional do valor na lista de posição
     * \p posicaoTabela.
     */
    Posicao
    (
        std::size_t posicaoTabela,
        std::size_t tamanhoLista,
        std::optional<std::size_t> posicaoLista
    );
};

Posicao::Posicao
(
    std::size_t const posicaoTabela,
    std::size_t const tamanhoLista,
    std::optional<std::size_t> const posicaoLista = std::nullopt
):
    posicaoTabela{posicaoTabela},
    tamanhoLista{tamanhoLista},
    posicaoLista{posicaoLista}
{}

bool operator == (Posicao const& a, Posicao const& b)
{
    return
        a.posicaoTabela == b.posicaoTabela &&
        a.tamanhoLista == b.tamanhoLista &&
        a.posicaoLista == b.posicaoLista;
}

#endif
