#include "gtest/gtest.h"
#include "MinhaListaEncadeada.h"

//extern "C" {
//#include "stack.h"
//}

//remover este teste
TEST(ListaEncadeadaTest,Init){
	ListaEncadeadaAbstrata<int>* p = new MinhaListaEncadeada<int>;
	ASSERT_NE(p,nullptr);
	ASSERT_EQ(p->estaVazia(),true);
	delete p;
}


TEST(ListaEncadeadaTest,ListaVazia){
	ListaEncadeadaAbstrata<int>* p = new MinhaListaEncadeada<int>;
	int d1 = 10;
	
	ASSERT_EQ(p->estaVazia(),true);
	
	p->adicionaNoInicio(&d1);
	
	ASSERT_EQ(p->estaVazia(),false);

	delete p;
}

TEST(ListaEncadeadaTest,AdicionaNoInicio){
	ListaEncadeadaAbstrata<int>* p = new MinhaListaEncadeada<int>;
	int d1 = 10;
	int d2 = 20;
	int d3 = 30;
	
	p->adicionaNoInicio(&d1);
	ASSERT_EQ(p->getTamanho(),1);
	ASSERT_EQ(p->contem(&d1),true);
	ASSERT_EQ(p->posicao(&d1),1);
	
	p->adicionaNoInicio(&d2);
	ASSERT_EQ(p->getTamanho(),2);
	ASSERT_EQ(p->contem(&d2),true);
	ASSERT_EQ(p->posicao(&d2),1);
	ASSERT_EQ(p->posicao(&d1),2);

	p->adicionaNoInicio(&d3);
	ASSERT_EQ(p->getTamanho(),3);
	ASSERT_EQ(p->contem(&d3),true);
	ASSERT_EQ(p->posicao(&d3),1);
	ASSERT_EQ(p->posicao(&d2),2);
	ASSERT_EQ(p->posicao(&d1),3);
	
	delete p;
}

TEST(ListaEncadeadaTest,AdicionaNaPosicao){
	ListaEncadeadaAbstrata<int>* p = new MinhaListaEncadeada<int>;
	int d1 = 10;
	int d2 = 20;
	int d3 = 30;
	int d4 = 40;
	
	EXPECT_THROW(p->adicionaNaPosicao(&d1, -1),posicao_invalida_exception);
	EXPECT_THROW(p->adicionaNaPosicao(&d1, 0),posicao_invalida_exception);
	EXPECT_THROW(p->adicionaNaPosicao(&d1, 2),posicao_invalida_exception);
	EXPECT_THROW(p->adicionaNaPosicao(&d1, 100),posicao_invalida_exception);
	
	p->adicionaNaPosicao(&d1, 1);
	ASSERT_EQ(p->getTamanho(),1);
	ASSERT_EQ(p->posicao(&d1),1);
	
	p->adicionaNaPosicao(&d2, 2);
	ASSERT_EQ(p->getTamanho(),2);
	ASSERT_EQ(p->posicao(&d2),2);
	ASSERT_EQ(p->posicao(&d1),1);
	
	p->adicionaNaPosicao(&d3, 2);
	ASSERT_EQ(p->getTamanho(),3);
	ASSERT_EQ(p->posicao(&d3),2);
	ASSERT_EQ(p->posicao(&d2),3);
	ASSERT_EQ(p->posicao(&d1),1);
	
	p->adicionaNaPosicao(&d4, 3);
	ASSERT_EQ(p->getTamanho(),4);
	ASSERT_EQ(p->posicao(&d4),3);
	ASSERT_EQ(p->posicao(&d3),2);
	ASSERT_EQ(p->posicao(&d2),4);
	ASSERT_EQ(p->posicao(&d1),1);
	
	delete p;
}

TEST(ListaEncadeadaTest,RetiraDoInicio){
	ListaEncadeadaAbstrata<int>* p = new MinhaListaEncadeada<int>;
	int d1 = 10;
	int d2 = 20;
	int d3 = 30;
	
	int *r;
	
	p->adicionaNoInicio(&d3);
	p->adicionaNoInicio(&d2);
	p->adicionaNoInicio(&d1);
	
	r = (int*) p->retiraDoInicio();
	ASSERT_EQ(*r, d1);
	ASSERT_EQ(p->getTamanho(),2);
	ASSERT_EQ(p->posicao(&d2),1);
	ASSERT_EQ(p->posicao(&d3),2);
	
	r = (int*) p->retiraDoInicio();
	ASSERT_EQ(*r, d2);
	ASSERT_EQ(p->getTamanho(),1);
	ASSERT_EQ(p->posicao(&d3),1);
	
	r = (int*) p->retiraDoInicio();
	ASSERT_EQ(*r, d3);
	ASSERT_EQ(p->getTamanho(),0);
	
	EXPECT_THROW(p->retiraDoInicio(),lista_encadeada_vazia_exception);
	
	delete p;
}

TEST(ListaEncadeadaTest,RetiraDaPosicao){
	ListaEncadeadaAbstrata<int>* p = new MinhaListaEncadeada<int>;
	int d1 = 10;
	int d2 = 20;
	int d3 = 30;
	int d4 = 40;
	int d5 = 50;
	int *r;
	
	p->adicionaNoInicio(&d5);
	p->adicionaNoInicio(&d4);
	p->adicionaNoInicio(&d3);
	p->adicionaNoInicio(&d2);
	p->adicionaNoInicio(&d1);

	EXPECT_THROW(p->retiraDaPosicao(-1),posicao_invalida_exception);
	EXPECT_THROW(p->retiraDaPosicao(0),posicao_invalida_exception);
	EXPECT_THROW(p->retiraDaPosicao(6),posicao_invalida_exception);
	EXPECT_THROW(p->retiraDaPosicao(7),posicao_invalida_exception);

    r = (int*) p->retiraDaPosicao(5);
	ASSERT_EQ(*r, d5);
	ASSERT_EQ(p->getTamanho(),4);
	ASSERT_EQ(p->posicao(&d2),2);

    r = (int*) p->retiraDaPosicao(3);
	ASSERT_EQ(*r, d3);
	ASSERT_EQ(p->getTamanho(),3);
	ASSERT_EQ(p->posicao(&d4),3);
	
	r = (int*) p->retiraDaPosicao(2);
	ASSERT_EQ(*r, d2);
	ASSERT_EQ(p->getTamanho(),2);
	ASSERT_EQ(p->posicao(&d4),2);
	
	r = (int*) p->retiraDaPosicao(1);
	ASSERT_EQ(*r, d1);
	ASSERT_EQ(p->getTamanho(),1);
	ASSERT_EQ(p->posicao(&d4),1);
	
	r = (int*) p->retiraDaPosicao(1);
	ASSERT_EQ(*r, d4);
	ASSERT_EQ(p->getTamanho(),0);
	ASSERT_EQ(p->contem(&d4),false);
	
	delete p;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
