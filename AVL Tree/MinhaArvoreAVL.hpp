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
    Nodo<T> *acharMinimo(Nodo<T> *nodo)
    {
        //Essa função serve para achar a chave mínima de uma sub-tree fornecida;
        //Usamos um simples loop, andando para direita infinitamente enquanto o filho esquerdo do próximo nodo n seja nulo.
        while (nodo->filhoEsquerda)
        {
            nodo = nodo->filhoEsquerda;
        }

        return nodo;
    }

    int acharAltura(Nodo<T> *nodo) const
    {
        /*
        Basicamente, essa função irá receber um nodo, então, chamar a achaMax mandando a mesma função com seus filhos, quando
        um nodo é true, ela chama isso para seus filhos e assim respectivamente, então, todo nodo não nulo contará como 1 para
        nós, a achaMax está basicamente comparando a altura de uma sub-tree esquerda e de uma sub-tree direita e retornando 
        a mais alta, que é o nosso objetivo com a altura.
        */
        if (nodo)
        {
            return achaMax(acharAltura(nodo->filhoEsquerda), acharAltura(nodo->filhoDireita)) + 1;
        }
        else
        {
            return 0;
        }
    };

    int achaMax(int a, int b) const
    {
        //Note que, usamos maior ou igual, porque se dois "caminhos" tem a mesma altura, a altura é igual, tanto faz
        //exemplo: um nodo que tem um filho a esquerda e um a direita, a altura é igual nos dois lados.
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

        nodo->altura = acharAltura(nodo);
        auxiliar_1->altura = acharAltura(auxiliar_1);

        return auxiliar_1; //Retornando a nova raiz;
    };

    Nodo<T> *rotacaoEsquerda(Nodo<T> *nodo)
    {
        Nodo<T> *auxiliar_1 = nodo->filhoDireita;
        Nodo<T> *auxiliar_2 = auxiliar_1->filhoEsquerda;

        auxiliar_1->filhoEsquerda = nodo;
        nodo->filhoDireita = auxiliar_2;

        nodo->altura = acharAltura(nodo);
        auxiliar_1->altura = acharAltura(auxiliar_1);

        return auxiliar_1; //Retornando a nova raiz;
    };

    int balanceamento(Nodo<T> *nodo)
    {
        if (nodo)
        {
            return acharAltura(nodo->filhoEsquerda) - acharAltura(nodo->filhoDireita);
            //Retornando o balanceamento usando a função recursiva para achar a altura do filho esquerdo e direito;
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
            //nodo = novo_nodo;
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

        nodo->altura = acharAltura(nodo);

        int balanco = balanceamento(nodo); //Aqui chamamos a função balaneamento para encontrar o balanço do nodo atual;

        if (balanco < -1)
        {
            if (chave > nodo->filhoDireita->chave)
            {
                return rotacaoEsquerda(nodo);
            }
            if (chave < nodo->filhoDireita->chave)
            {
                //Aplicando right-left
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
                nodo->filhoEsquerda = rotacaoEsquerda(nodo->filhoEsquerda);
                return rotacaoDireita(nodo);
            }
        }

        return nodo;
    };

    Nodo<T> *remover(Nodo<T> *nodo, int chave)
    {
        if (nodo == NULL)
        {
            //é null , basicamente isso só vai acontecer se o primeiro nodo já for nulo
            return nodo;
        }

        if (chave < nodo->chave)
        {
            nodo->filhoEsquerda = remover(nodo->filhoEsquerda, chave);
            //chamando a recursividade para realizar os mesmos passos aqui até chegar em null
        }
        else if (chave > nodo->chave)
        {
            nodo->filhoDireita = remover(nodo->filhoDireita, chave);
            //chamando a recursividade para o lado direito
        }
        else
        {
            if (nodo->filhoDireita == NULL || nodo->filhoEsquerda == NULL)
            {
                //Podemos fazer isso para uma melhor organização do código, basicamante, vai entrar aqui se um dos dois for nulo
                if (nodo->filhoDireita == NULL && nodo->filhoEsquerda == NULL)
                {
                    //Aqui é o caso de uma leaf.
                    delete nodo;
                    nodo = NULL;
                    return nodo;
                }
                else if (nodo->filhoDireita != NULL && nodo->filhoEsquerda == NULL)
                {
                    Nodo<T> *temporario = nodo->filhoDireita;
                    //Pegando os dados do filho nao nulo antes de deletar o pai para retornar para o avo
                    delete nodo;
                    nodo = NULL;
                    nodo = temporario;
                    return nodo;
                }
                else if (nodo->filhoDireita == NULL && nodo->filhoEsquerda != NULL)
                {
                    Nodo<T> *temporario = nodo->filhoEsquerda;
                    //Pegando os dados do filho nao nulo antes de deletar o pai para retornar para o avo
                    delete nodo;
                    nodo = NULL;
                    nodo = temporario;
                    return nodo;
                }
            }
            else
            {
                Nodo<T> *temporario = acharMinimo(nodo->filhoDireita);
                //Assim temos o menor nodo que ainda é maior que o nodo atual.
                nodo->chave = temporario->chave;
                nodo->filhoDireita = remover(nodo->filhoDireita, nodo->chave);
            }
        }

        if (nodo == NULL)
        {
            return nodo;
        }

        nodo->altura = acharAltura(nodo); //atualizando a altura de todos os nodos, já que é recursivo

        int balanco = balanceamento(nodo); //Pegando o balanço

        int balanco_esquerda = balanceamento(nodo->filhoEsquerda);

        int balanco_direita = balanceamento(nodo->filhoDireita);

        if (balanco > 1 && balanco_esquerda >= 0)
        {
            return rotacaoDireita(nodo);
            //Aplicando apenas right
        }
        if (balanco > 1 && balanco_esquerda < 0)
        {
            nodo->filhoEsquerda = rotacaoEsquerda(nodo->filhoEsquerda);
            //Aplicando a left right
            return rotacaoDireita(nodo);
        }
        if (balanco < -1 && balanco_direita <= 0)
        {
            return rotacaoEsquerda(nodo);
            //Aplicando apenas left
        }
        if (balanco < -1 && balanco_direita > 0)
        {
            //Aplicando a right left
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

    MinhaArvoreAVL()
    {
        MinhaArvoreAVL<T>::_raiz = NULL;
    }
    ~MinhaArvoreAVL()
    {
    Nodo<T> * aux = MinhaArvoreAVL<T>::_raiz;
    delete aux->filhoDireita;s
    delete aux->filhoEsquerda;
    }
};

#endif