#ifndef LISTAENCADEADAABSTRATA_H
#define LISTAENCADEADAABSTRATA_H

#include <exception>

class posicao_invalida_exception : public std::exception
{
	virtual const char* what() const throw()
  	{
    	return "Posicao invalida na lista encadeada";
  	}
}; 

class lista_encadeada_vazia_exception : public std::exception
{
	virtual const char* what() const throw()
  	{
    	return "Lista encadeada vazia";
  	}
}; 

template <typename T>
struct Elemento
{
            struct Elemento* _proximo;
            T* _dado;
};

//using Elemento = typename ListaEncadeadaAbstrata<T>::Elemento


template <typename T>
class ListaEncadeadaAbstrata
{
    protected :
        Elemento<T>* _primeiro;
        int _tamanho;

    public :
        virtual ~ListaEncadeadaAbstrata() {};
        virtual bool estaVazia() = 0;
        virtual int getTamanho() = 0;
        virtual int posicao(T* umDado) = 0;
        virtual bool contem(T* umDado) = 0;
        virtual void adicionaNoInicio(T* umDado) = 0;
        virtual void adicionaNaPosicao(T* umDado, int umaPosicao) = 0;
        virtual void adicionaNoFim(T* umDado) = 0;
        virtual T* retiraDoInicio() = 0;
        virtual T* retiraDaPosicao(int umaPosicao) = 0;
        virtual T* retiraDoFim() = 0;
        virtual T* retiraEspecifico(T* umDado) = 0;
};

#endif