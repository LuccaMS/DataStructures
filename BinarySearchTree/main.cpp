#include "gtest/gtest.h"
#include "MinhaArvoreDeBuscaBinaria.hpp"

TEST(ArvoreBinariaBuscaTest, Inicializacao)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreDeBuscaBinaria<int>};

    ASSERT_TRUE(arvore->vazia());
    ASSERT_EQ(arvore->quantidade(), 0);

    ASSERT_TRUE(!arvore->contem(1));
    ASSERT_TRUE(!arvore->altura(1));
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(1));
    ASSERT_TRUE(!arvore->filhoDireitaDe(1));
    
    ListaEncadeadaAbstrata<int>* lista{arvore->emOrdem()};
    ASSERT_TRUE(lista != nullptr);
    ASSERT_TRUE(lista->estaVazia());
    delete lista;

    lista = arvore->preOrdem();
    ASSERT_TRUE(lista != nullptr);
    ASSERT_TRUE(lista->estaVazia());
    delete lista;

    lista = arvore->posOrdem();
    ASSERT_TRUE(lista != nullptr);
    ASSERT_TRUE(lista->estaVazia());
    delete lista;
    
    delete arvore;
}

TEST(ArvoreBinariaBuscaTest, PreOrdem)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreDeBuscaBinaria<int>};

    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    ListaEncadeadaAbstrata<int>* const lista{arvore->preOrdem()};

    for (int const e : {5, 3, 2, 4, 7, 6, 9})
        ASSERT_EQ(lista->retiraDoInicio(), e);

    delete lista;

    delete arvore;
}

TEST(ArvoreBinariaBuscaTest, EmOrdem)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreDeBuscaBinaria<int>};

    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    ListaEncadeadaAbstrata<int>* const lista{arvore->emOrdem()};

    for (int const e : {2, 3, 4, 5, 6, 7, 9})
        ASSERT_EQ(lista->retiraDoInicio(), e);

    delete lista;

    delete arvore;
}

TEST(ArvoreBinariaBuscaTest, PosOrdem)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreDeBuscaBinaria<int>};

    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    ListaEncadeadaAbstrata<int>* const lista{arvore->posOrdem()};

    for (int const e : {2, 4, 3, 6, 9, 7, 5})
        ASSERT_EQ(lista->retiraDoInicio(), e);

    delete lista;

    delete arvore;
}

TEST(ArvoreBinariaBuscaTest, Insercao)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreDeBuscaBinaria<int>};

    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    ASSERT_TRUE(!arvore->vazia());
    ASSERT_EQ(arvore->quantidade(), 7);

    ASSERT_TRUE(arvore->contem(5));
    ASSERT_EQ(*arvore->altura(5), 2);
    ASSERT_EQ(*arvore->filhoDireitaDe(5), 7);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(5), 3);

    ASSERT_TRUE(arvore->contem(3));
    ASSERT_EQ(*arvore->altura(3), 1);
    ASSERT_EQ(*arvore->filhoDireitaDe(3), 4);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(3), 2);

    ASSERT_TRUE(arvore->contem(7));
    ASSERT_EQ(*arvore->altura(7), 1);
    ASSERT_EQ(*arvore->filhoDireitaDe(7), 9);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(7), 6);

    ASSERT_TRUE(arvore->contem(2));
    ASSERT_EQ(*arvore->altura(2), 0);
    ASSERT_TRUE(!arvore->filhoDireitaDe(2));
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(2));

    ASSERT_TRUE(arvore->contem(4));
    ASSERT_EQ(*arvore->altura(4), 0);
    ASSERT_TRUE(!arvore->filhoDireitaDe(4));
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(4));

    ASSERT_TRUE(arvore->contem(6));
    ASSERT_EQ(*arvore->altura(6), 0);
    ASSERT_TRUE(!arvore->filhoDireitaDe(6));
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(6));

    ASSERT_TRUE(arvore->contem(9));
    ASSERT_EQ(*arvore->altura(9), 0);
    ASSERT_TRUE(!arvore->filhoDireitaDe(9));
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(9));

    delete arvore;  
}

TEST(ArvoreBinariaBuscaTest, Remocao)
{
    ArvoreDeBuscaBinaria<int>* arvore{new MinhaArvoreDeBuscaBinaria<int>};

    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    //Testa remover folha
    arvore->remover(9);
    ASSERT_TRUE(!arvore->contem(9));
    ASSERT_EQ(arvore->quantidade(), 6);
    ASSERT_TRUE(!arvore->filhoDireitaDe(7));
    
    //Testa remover folha
    arvore->remover(6);
    ASSERT_TRUE(!arvore->contem(6));
    ASSERT_EQ(arvore->quantidade(), 5);
    ASSERT_TRUE(!arvore->filhoDireitaDe(7));
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(7));
    
    //Testa remover raiz
    arvore->inserir(6);
    arvore->inserir(9);
    arvore->remover(5);
    ASSERT_TRUE(!arvore->contem(5));
    ASSERT_EQ(arvore->quantidade(), 6);
    ASSERT_EQ(*arvore->filhoDireitaDe(6), 7);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(6), 3);
    ASSERT_EQ(*arvore->filhoDireitaDe(7), 9);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(7));

    //Testa remover nodo com filhoDireita sem descendente a esquerda
    arvore->inserir(5);
    ASSERT_EQ(*arvore->filhoDireitaDe(4), 5);
    ASSERT_EQ(*arvore->altura(6), 3);
    ASSERT_EQ(*arvore->altura(4), 1);
    arvore->remover(3);
    ASSERT_TRUE(!arvore->contem(3));
    ASSERT_EQ(arvore->quantidade(), 6);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(6), 4);
    ASSERT_EQ(*arvore->filhoDireitaDe(6), 7);
    ASSERT_EQ(*arvore->altura(6), 2);

    ASSERT_EQ(*arvore->filhoDireitaDe(4), 5);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(4), 2);

    delete arvore;

    // Testa esvaziar a árvore.

    arvore = new MinhaArvoreDeBuscaBinaria<int>;

    for (int const e : {3, 2, 4})
        arvore->inserir(e);

    ASSERT_EQ(arvore->quantidade(), 3);

    for (int const e : {3, 2, 4})
        arvore->remover(e);

    ASSERT_EQ(arvore->quantidade(), 0);

    // Testa remover item não contido na árvore.

    arvore->inserir(2);
    ASSERT_TRUE(arvore->contem(2));
    ASSERT_EQ(arvore->quantidade(), 1);

    arvore->remover(3);
    ASSERT_TRUE(arvore->contem(2));
    ASSERT_EQ(arvore->quantidade(), 1);

    delete arvore;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
