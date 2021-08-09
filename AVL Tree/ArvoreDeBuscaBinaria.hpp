#ifndef ARVORE_DE_BUSCA_BINARIA_HPP
#define ARVORE_DE_BUSCA_BINARIA_HPP

#include "MinhaListaEncadeada.hpp"
#include <optional>

template<typename T>
struct Nodo
{
    T chave;
    int altura{0};
    Nodo* filhoEsquerda{nullptr};
    Nodo* filhoDireita{nullptr};
};

template<typename T>
class ArvoreDeBuscaBinaria
{
protected:
    Nodo<T>* _raiz;

public:
    ArvoreDeBuscaBinaria();
    virtual ~ArvoreDeBuscaBinaria();

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const = 0;
    
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const = 0;
    
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const = 0;
    
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const = 0;

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */        
    virtual void inserir(T chave) = 0;

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */        
    virtual void remover(T chave) = 0;

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const = 0;

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */        
    virtual std::optional<T> filhoDireitaDe(T chave) const = 0;

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */
    virtual ListaEncadeadaAbstrata<T>* emOrdem() const = 0;

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */
    virtual ListaEncadeadaAbstrata<T>* preOrdem() const = 0;

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
    virtual ListaEncadeadaAbstrata<T>* posOrdem() const = 0;
};

template<typename T>
ArvoreDeBuscaBinaria<T>::ArvoreDeBuscaBinaria():
    _raiz{}
{}

template<typename T>
ArvoreDeBuscaBinaria<T>::~ArvoreDeBuscaBinaria() = default;

#endif