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
            int altura_esq = achaAltura(nodo->filhoEsquerda);
            int altura_direita = achaAltura(nodo->filhoDireita);

            if (altura_esq >= altura_direita)
            {
                return altura_esq + 1;
            }
            else
            {
                return altura_direita + 1;
            }
        }
        else
        {
            return 0;
        }
    };

    Nodo<T> *rotacaoDireita(Nodo<T> *nodo)
    {
        Nodo<T> *auxiliar_1 = nodo->filhoEsquerda;

        Nodo<T> *auxiliar_2 = nodo->filhoEsquerda->filhoDireita;

        auxiliar_1->filhoDireita = nodo;
        nodo->filhoEsquerda = auxiliar_2;

        return auxiliar_1;
    };

    Nodo<T> *rotacaoEsquerda(Nodo<T> *nodo)
    {
        Nodo<T> *auxiliar_1 = nodo->filhoDireita;
        Nodo<T> *auxiliar_2 = nodo->filhoDireita->filhoEsquerda;

        auxiliar_1->filhoEsquerda = nodo;
        nodo->filhoDireita = auxiliar_2;

        return auxiliar_1;
    };

    Nodo<T> *rotacaoEsquerdaDireita(Nodo<T> *nodo)
    {
        Nodo<T> *nodoesq = nodo->filhoEsquerda;
        Nodo<T> *auxiliar_1 = nodoesq->filhoDireita;
        Nodo<T> *auxiliar_2 = nodoesq->filhoDireita->filhoEsquerda;

        auxiliar_1->filhoEsquerda = nodoesq;
        nodoesq->filhoDireita = auxiliar_2;

        nodo->filhoEsquerda = auxiliar_1;
        //Esquerda feita

        Nodo<T> *auxiliar_3 = nodo->filhoEsquerda;
        Nodo<T> *auxiliar_4 = nodo->filhoEsquerda->filhoDireita;

        auxiliar_3->filhoDireita = nodo;
        nodo->filhoEsquerda = auxiliar_4;

        //Direita feita

        return auxiliar_3;
    };

    Nodo<T> *rotacaoDireitaEsquerda(Nodo<T> *nodo)
    {
        Nodo<T> *filho_dir = nodo->filhoDireita;

        Nodo<T> *auxiliar_1 = filho_dir->filhoEsquerda;

        Nodo<T> *auxiliar_2 = filho_dir->filhoEsquerda->filhoDireita;

        auxiliar_1->filhoDireita = filho_dir;
        filho_dir->filhoEsquerda = auxiliar_2;

        nodo->filhoDireita = auxiliar_1;

        Nodo<T> *auxiliar_3 = nodo->filhoDireita;
        Nodo<T> *auxiliar_4 = nodo->filhoDireita->filhoEsquerda;

        auxiliar_3->filhoEsquerda = nodo;
        nodo->filhoDireita = auxiliar_4;

        return auxiliar_3;
    }

    Nodo<T> *inserir(Nodo<T> *nodo, int chave)
    {
        if (!nodo)
        {
            Nodo<T> *novo_nodo = new Nodo<T>;
            novo_nodo->chave = chave;
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

        int balanco = achaAltura(nodo->filhoEsquerda) - achaAltura(nodo->filhoDireita);

        if (balanco < -1)
        {
            if (chave > nodo->filhoDireita->chave)
            {
                return rotacaoEsquerda(nodo);
            }
            if (chave < nodo->filhoDireita->chave)
            {
                return rotacaoDireitaEsquerda(nodo);
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

            else
            {
                Nodo<T> *temporario;
                Nodo<T> *aux = nodo->filhoDireita;

                if (aux->filhoEsquerda)
                {
                    aux = aux->filhoEsquerda;
                };

                temporario = aux;
                //Neste caso, basicamente estamos pegando o filho a esquerda do filho a direita e tornando a "raiz" com o mesmo nodo
                //porque esse filho vai ser maior que todos os elementos da esquerda e ainda menor que os elementos da direita.

                nodo->chave = temporario->chave;
                nodo->filhoDireita = remover(nodo->filhoDireita, nodo->chave);
            }
        }

        int balanco = achaAltura(nodo->filhoEsquerda) - achaAltura(nodo->filhoDireita);

        int balanco_esquerda = 0;

        if (nodo->filhoEsquerda)
        {
            balanco_esquerda = achaAltura(nodo->filhoEsquerda->filhoEsquerda) - achaAltura(nodo->filhoEsquerda->filhoDireita);
        }

        int balanco_direita = 0;

        if (nodo->filhoDireita)
        {
            balanco_direita = achaAltura(nodo->filhoDireita->filhoEsquerda) - achaAltura(nodo->filhoDireita->filhoDireita);
        }

        if (balanco > 1 && balanco_esquerda >= 0)
        {
            //Como há um desbalança na parte direita mas a parte esquerda está equilibrada rotacionamos para a direita
            return rotacaoDireita(nodo);
        }
        if (balanco > 1 && balanco_esquerda < 0)
        {
            //Como há um desbalanço na parte direita mas a parte esquerda não está em equilibrio fazemos esquerda direita
            return rotacaoEsquerdaDireita(nodo);
        }
        if (balanco < -1 && balanco_direita <= 0)
        {
            return rotacaoEsquerda(nodo);
        }
        if (balanco < -1 && balanco_direita > 0)
        {
            return rotacaoDireitaEsquerda(nodo);
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