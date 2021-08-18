#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.hpp"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
private:
    int achaAltura(Nodo<T> *nodo) const
    {
        if (nodo)
        {
            return achaMax(achaAltura(nodo->filhoEsquerda), achaAltura(nodo->filhoDireita)) + 1;
        }
        else
        {
            return 0;
        }
    };

    int achaMax(int a, int b) const
    {
        if (a >= b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    Nodo<T> *rotacaoDireita(Nodo<T> *nodo)
    {
        Nodo<T> *auxiliar_1 = nodo->filhoEsquerda;

        Nodo<T> *auxiliar_2 = auxiliar_1->filhoDireita;

        auxiliar_1->filhoDireita = nodo;
        nodo->filhoEsquerda = auxiliar_2;

        nodo->altura = achaAltura(nodo);
        auxiliar_1->altura = achaAltura(auxiliar_1);

        return auxiliar_1;
    };

    Nodo<T> *rotacaoEsquerda(Nodo<T> *nodo)
    {
        Nodo<T> *auxiliar_1 = nodo->filhoDireita;
        Nodo<T> *auxiliar_2 = auxiliar_1->filhoEsquerda;

        auxiliar_1->filhoEsquerda = nodo;
        nodo->filhoDireita = auxiliar_2;

        nodo->altura = achaAltura(nodo);
        auxiliar_1->altura = achaAltura(auxiliar_1);

        return auxiliar_1;
    };

    Nodo<T> * rotacaoEsquerdaDireita(Nodo<T> * nodo)
    {
        Nodo<T> * nodoesq = nodo->filhoEsquerda;
        Nodo<T> *auxiliar_1 = nodoesq->filhoDireita;
        Nodo<T> *auxiliar_2 = auxiliar_1->filhoEsquerda;

        auxiliar_1->filhoEsquerda = nodoesq;
        nodoesq->filhoDireita = auxiliar_2;

        nodo->filhoEsquerda = auxiliar_1;
        //Esquerda feita

        Nodo<T> * auxiliar_3 = nodo->filhoEsquerda;
        Nodo<T> * auxiliar_4 = auxiliar_3->filhoDireita;

        auxiliar_3->filhoDireita = nodo;
        nodo->filhoEsquerda = auxiliar_4;

        //Direita feita

        return auxiliar_3;
    };

    int balanceamento(Nodo<T> *nodo)
    {
        if (nodo)
        {
            return achaAltura(nodo->filhoEsquerda) - achaAltura(nodo->filhoDireita);
        }
        return 0;
    };

    Nodo<T> *inserir(Nodo<T> *nodo, int chave)
    {
        if (!nodo)
        {
            Nodo<T> *novo_nodo = new Nodo<T>;
            novo_nodo->chave = chave;
            novo_nodo->filhoEsquerda = NULL;
            novo_nodo->filhoDireita = NULL;
            novo_nodo->altura = 1;
            return novo_nodo;
        }

        if (nodo->chave > chave)
        {
            nodo->filhoEsquerda = inserir(nodo->filhoEsquerda, chave);
        }
        else if (nodo->chave < chave)
        {
            nodo->filhoDireita = inserir(nodo->filhoDireita, chave);
        }

        int balanco = balanceamento(nodo);

        if (balanco < -1)
        {
            if (chave > nodo->filhoDireita->chave)
            {
                return rotacaoEsquerda(nodo);
            }
            if (chave < nodo->filhoDireita->chave)
            {
                nodo->filhoDireita = rotacaoDireita(nodo->filhoDireita);
                return rotacaoEsquerda(nodo);
            }
        }
        if (balanco > 1)
        {
            if (chave < nodo->filhoEsquerda->chave)
            {
                return rotacaoDireita(nodo);
            }
            if (chave > nodo->filhoEsquerda->chave)
            {
                return rotacaoEsquerdaDireita(nodo);
            }
        }

        return nodo;
    };

    Nodo<T> *remover(Nodo<T> *nodo, int chave)
    {
        if (nodo == NULL)
        {
            return nodo;
        }

        if (chave < nodo->chave)
        {
            nodo->filhoEsquerda = remover(nodo->filhoEsquerda, chave);
        }
        else if (chave > nodo->chave)
        {
            nodo->filhoDireita = remover(nodo->filhoDireita, chave);
        }
        else
        {
            if (nodo->filhoDireita == NULL || nodo->filhoEsquerda == NULL)
            {
                if (nodo->filhoDireita == NULL && nodo->filhoEsquerda == NULL)
                {
                    delete nodo;
                    nodo = NULL;
                    return nodo;
                }
                else if (nodo->filhoDireita != NULL && nodo->filhoEsquerda == NULL)
                {
                    Nodo<T> *temporario = nodo->filhoDireita;
                    delete nodo;
                    nodo = NULL;
                    nodo = temporario;
                    return nodo;
                }
                else if (nodo->filhoDireita == NULL && nodo->filhoEsquerda != NULL)
                {
                    Nodo<T> *temporario = nodo->filhoEsquerda;
                    delete nodo;
                    nodo = NULL;
                    nodo = temporario;
                    return nodo;
                }
            }
            else
            {
                Nodo<T> *temporario;
                Nodo<T> * aux = nodo->filhoDireita;

                if(aux->filhoEsquerda){aux = aux->filhoEsquerda;};

                temporario = aux;
                
                nodo->chave = temporario->chave;
                nodo->filhoDireita = remover(nodo->filhoDireita, nodo->chave);
            }
        }

        int balanco = balanceamento(nodo);

        int balanco_esquerda = balanceamento(nodo->filhoEsquerda);

        int balanco_direita = balanceamento(nodo->filhoDireita);

        if (balanco > 1 && balanco_esquerda >= 0)
        {
            return rotacaoDireita(nodo);
        }
        if (balanco > 1 && balanco_esquerda < 0)
        {
            nodo->filhoEsquerda = rotacaoEsquerda(nodo->filhoEsquerda);
            return rotacaoDireita(nodo);
        }
        if (balanco < -1 && balanco_direita <= 0)
        {
            return rotacaoEsquerda(nodo);
        }
        if (balanco < -1 && balanco_direita > 0)
        {
            nodo->filhoDireita = rotacaoDireita(nodo->filhoDireita);
            return rotacaoEsquerda(nodo);
        }

        return nodo;
    };

public:
    void inserir(T chave) override
    {
        Nodo<T> *raiz = ArvoreDeBuscaBinaria<T>::_raiz;
        Nodo<T> *auxiliar = ArvoreDeBuscaBinaria<T>::_raiz;
        auxiliar = inserir(raiz, chave);
        ArvoreDeBuscaBinaria<T>::_raiz = auxiliar;
    };

    void remover(T chave) override
    {
        Nodo<T> *raiz = ArvoreDeBuscaBinaria<T>::_raiz;
        Nodo<T> *auxiliar = ArvoreDeBuscaBinaria<T>::_raiz;
        auxiliar = remover(raiz, chave);
        ArvoreDeBuscaBinaria<T>::_raiz = auxiliar;
    };
};

#endif