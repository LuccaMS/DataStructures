#include "gtest/gtest.h"
#include "MinhaArvoreAVL.hpp"

TEST(ArvoreAVLTest, InsercaoRotacaoDireitaSimples)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {4, 3, 2, 1})
        arvore->inserir(e);

    ASSERT_EQ(*arvore->altura(3), 2);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(3), 2);
    ASSERT_EQ(*arvore->filhoDireitaDe(3), 4);

    ASSERT_EQ(*arvore->altura(2), 1);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(2), 1);
    ASSERT_TRUE(!arvore->filhoDireitaDe(2));

    ASSERT_EQ(*arvore->altura(1), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(1));
    ASSERT_TRUE(!arvore->filhoDireitaDe(1));

    ASSERT_EQ(*arvore->altura(4), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(4));
    ASSERT_TRUE(!arvore->filhoDireitaDe(4));

    delete arvore;
}

TEST(ArvoreAVLTest, InsercaoRotacaoEsquerdaSimples)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {1, 2, 3, 4})
        arvore->inserir(e);

    ASSERT_EQ(*arvore->altura(3), 1);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(3));
    ASSERT_EQ(*arvore->filhoDireitaDe(3), 4);

    ASSERT_EQ(*arvore->altura(2), 2);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(2), 1);
    ASSERT_EQ(*arvore->filhoDireitaDe(2), 3);

    ASSERT_EQ(*arvore->altura(1), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(1));
    ASSERT_TRUE(!arvore->filhoDireitaDe(1));

    ASSERT_EQ(*arvore->altura(4), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(4));
    ASSERT_TRUE(!arvore->filhoDireitaDe(4));

    delete arvore;
}

TEST(ArvoreAVLTest, InsercaoRotacaoEsquerdaDireita)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {6, 4, 8, 2, 7, 9, 3})
        arvore->inserir(e);

    ASSERT_EQ(*arvore->altura(2), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(2));
    ASSERT_TRUE(!arvore->filhoDireitaDe(2));

    ASSERT_EQ(*arvore->altura(3), 1);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(3), 2);
    ASSERT_EQ(*arvore->filhoDireitaDe(3), 4);

    ASSERT_EQ(*arvore->altura(4), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(4));
    ASSERT_TRUE(!arvore->filhoDireitaDe(4));

    ASSERT_EQ(*arvore->altura(6), 2);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(6), 3);
    ASSERT_EQ(*arvore->filhoDireitaDe(6), 8);

    ASSERT_EQ(*arvore->altura(8), 1);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(8), 7);
    ASSERT_EQ(*arvore->filhoDireitaDe(8), 9);

    ASSERT_EQ(*arvore->altura(7), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(7));
    ASSERT_TRUE(!arvore->filhoDireitaDe(7));

    ASSERT_EQ(*arvore->altura(9), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(9));
    ASSERT_TRUE(!arvore->filhoDireitaDe(9));

    delete arvore;
}

TEST(ArvoreAVLTest, InsercaoRotacaoDireitaEsquerda)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {1, 2, 3, 4, 5, 6, 7, 16, 15})
        arvore->inserir(e);

    ASSERT_EQ(*arvore->altura(1), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(1));
    ASSERT_TRUE(!arvore->filhoDireitaDe(1));

    ASSERT_EQ(*arvore->altura(2), 1);
    ASSERT_EQ(arvore->filhoEsquerdaDe(2).value(), 1);
    ASSERT_EQ(arvore->filhoDireitaDe(2).value(), 3);

    ASSERT_EQ(*arvore->altura(3), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(3));
    ASSERT_TRUE(!arvore->filhoDireitaDe(3));

    ASSERT_EQ(*arvore->altura(4), 3);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(4), 2);
    ASSERT_EQ(*arvore->filhoDireitaDe(4), 6);

    ASSERT_EQ(*arvore->altura(5), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(5));
    ASSERT_TRUE(!arvore->filhoDireitaDe(5));

    ASSERT_EQ(*arvore->altura(6), 2);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(6), 5);
    ASSERT_EQ(*arvore->filhoDireitaDe(6), 15);

    ASSERT_EQ(*arvore->altura(7), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(7));
    ASSERT_TRUE(!arvore->filhoDireitaDe(7));

    ASSERT_EQ(*arvore->altura(15), 1);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(15), 7);
    ASSERT_EQ(*arvore->filhoDireitaDe(15), 16);

    ASSERT_EQ(*arvore->altura(16), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(16));
    ASSERT_TRUE(!arvore->filhoDireitaDe(16));

    delete arvore;
}

TEST(ArvoreAVLTest, PreOrdem)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};

    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    ListaEncadeadaAbstrata<int>* const lista{arvore->preOrdem()};

    for (int const e : {5, 3, 2, 4, 7, 6, 9})
        ASSERT_EQ(lista->retiraDoInicio(), e);

    delete lista;

    delete arvore;
}

TEST(ArvoreAVLTest, EmOrdem)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    ListaEncadeadaAbstrata<int>* const lista{arvore->emOrdem()};

    for (int const e : {2, 3, 4, 5, 6, 7, 9})
        ASSERT_EQ(lista->retiraDoInicio(), e);

    delete lista;
    
    delete arvore;
}

TEST(ArvoreAVLTest, PosOrdem)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    ListaEncadeadaAbstrata<int>* const lista{arvore->posOrdem()};

    for (int const e : {2, 4, 3, 6, 9, 7, 5})
        ASSERT_EQ(lista->retiraDoInicio(), e);

    delete lista;
    
    delete arvore;
}

TEST(ArvoreAVLTest, Remocao)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {5, 3, 7, 2, 4, 6, 9})
        arvore->inserir(e);

    //Testa remover folha
    arvore->remover(9);
    ASSERT_TRUE(!arvore->filhoDireitaDe(7));

    //Testa remover folha
    arvore->remover(6);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(7));
    ASSERT_TRUE(!arvore->filhoDireitaDe(7));

    //Testa remover raiz
    for (int const e : {6, 9})
        arvore->inserir(e);

    arvore->remover(5);

    ASSERT_EQ(*arvore->filhoDireitaDe(7), 9);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(7));

    //Testa remover nodo com filhoDireita sem descendente a direita
    arvore->inserir(5);
    ASSERT_EQ(*arvore->filhoDireitaDe(4), 5);
    arvore->remover(3);
    
    ASSERT_EQ(*arvore->filhoEsquerdaDe(6), 4);
    ASSERT_EQ(*arvore->filhoDireitaDe(4), 5);
    ASSERT_TRUE(!arvore->filhoDireitaDe(5));
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(5));
    ASSERT_EQ(*arvore->filhoEsquerdaDe(4), 2);

    delete arvore;
}

TEST(ArvoreAVLTest, RemocaoRotacaoDireitaSimples)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {50, 25, 75, 12, 37})
        arvore->inserir(e);
    
    arvore->remover(75);

    ASSERT_EQ(*arvore->altura(25), 2);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(25), 12);
    ASSERT_EQ(*arvore->filhoDireitaDe(25), 50);

    ASSERT_EQ(*arvore->altura(12), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(12));
    ASSERT_TRUE(!arvore->filhoDireitaDe(12));

    ASSERT_EQ(*arvore->altura(50), 1);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(50), 37);
    ASSERT_TRUE(!arvore->filhoDireitaDe(50));

    ASSERT_EQ(*arvore->altura(37), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(37));
    ASSERT_TRUE(!arvore->filhoDireitaDe(37));

    delete arvore;
}

TEST(ArvoreAVLTest, RemocaoRotacaoEsquerdaSimples)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {50, 25, 75, 62, 87})
        arvore->inserir(e);
    
    arvore->remover(25);

    ASSERT_EQ(*arvore->altura(75), 2);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(75), 50);
    ASSERT_EQ(*arvore->filhoDireitaDe(75), 87);

    ASSERT_EQ(*arvore->altura(50), 1);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(50));
    ASSERT_EQ(arvore->filhoDireitaDe(50), 62);

    ASSERT_EQ(*arvore->altura(87), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(87));
    ASSERT_TRUE(!arvore->filhoDireitaDe(87));

    ASSERT_EQ(*arvore->altura(62), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(62));
    ASSERT_TRUE(!arvore->filhoDireitaDe(62));

    delete arvore;
}

TEST(ArvoreAVLTest, RemocaoRotacaoEsquerdaDireita)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {50, 25, 75, 37})
        arvore->inserir(e);
    
    arvore->remover(75);

    ASSERT_EQ(*arvore->altura(37), 1);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(37), 25);
    ASSERT_EQ(*arvore->filhoDireitaDe(37), 50);

    ASSERT_EQ(*arvore->altura(25), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(25));
    ASSERT_TRUE(!arvore->filhoDireitaDe(25));

    ASSERT_EQ(*arvore->altura(50), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(50));
    ASSERT_TRUE(!arvore->filhoDireitaDe(50));

    delete arvore;
}

TEST(ArvoreAVLTest, RemocaoRotacaoDireitaEsquerda)
{
    ArvoreDeBuscaBinaria<int>* const arvore{new MinhaArvoreAVL<int>};
    
    for (int const e : {50, 25, 75, 62})
        arvore->inserir(e);
    
    arvore->remover(25);

    ASSERT_EQ(*arvore->altura(62), 1);
    ASSERT_EQ(*arvore->filhoEsquerdaDe(62), 50);
    ASSERT_EQ(*arvore->filhoDireitaDe(62), 75);

    ASSERT_EQ(*arvore->altura(50), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(50));
    ASSERT_TRUE(!arvore->filhoDireitaDe(50));

    ASSERT_EQ(*arvore->altura(75), 0);
    ASSERT_TRUE(!arvore->filhoEsquerdaDe(75));
    ASSERT_TRUE(!arvore->filhoDireitaDe(75));

    delete arvore;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
