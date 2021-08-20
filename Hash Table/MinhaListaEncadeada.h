#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"

template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
public:
  //rideructor da linked list
  MinhaListaEncadeada()
  {
    ListaEncadeadaAbstrata<T>::_primeiro = NULL;
    ListaEncadeadaAbstrata<T>::_tamanho = 0;
  };
  //Destructor da linked list
  ~MinhaListaEncadeada()
  {
    Elemento<T> *atual = ListaEncadeadaAbstrata<T>::_primeiro;
    Elemento<T> *proximo = NULL;

    while (atual != NULL)
    {
      proximo = atual->_proximo;
      delete atual;
      atual = proximo;
    }
    //ListaEncadeadaAbstrata<T>::_primeiro == NULL;
  };

  int getTamanho() const
  {
    int count = 0;
    Elemento<T> *atual = ListaEncadeadaAbstrata<T>::_primeiro;
    if (atual == NULL)
    {
      return 0;
    }
    else
    {
      while (atual != NULL)
      {
        //count++;
        atual = atual->_proximo;
        count++;
      }
    }

    return count;
  };
  int posicao(T umDado) const
  {
    Elemento<T> *atual = ListaEncadeadaAbstrata<T>::_primeiro;
    int count = 0;
    while (atual != NULL)
    {
      count++;
      if (umDado == atual->_dado)
      {
        return count;
      }
      atual = atual->_proximo;
    }
    return 0;
  };

  bool estaVazia() const
  {
    if (ListaEncadeadaAbstrata<T>::_primeiro == NULL)
    {
      return true;
    }
    else
    {
      return false;
    }
  };

  bool contem(T umDado) const
  {
    Elemento<T> *atual = ListaEncadeadaAbstrata<T>::_primeiro;
    while (atual != NULL)
    {
      if (atual->_dado == umDado)
      {
        return true;
      }
      atual = atual->_proximo;
    }
    return false;
  };
  void adicionaNoInicio(T umDado) override
  {
    Elemento<T> *novo = new Elemento<T>();

    novo->_dado = umDado;

    novo->_proximo = (ListaEncadeadaAbstrata<T>::_primeiro);

    ListaEncadeadaAbstrata<T>::_primeiro = novo;
  };
  void adicionaNaPosicao(T umDado, int umaPosicao) override
  {
    int tamanho = getTamanho();
    if(umaPosicao == 1 and ListaEncadeadaAbstrata<T>::_tamanho == 0)
    {
      //Quer dizer que a lista está vazia, ele quer começar ela
      Elemento<T> *auxiliar = new Elemento<T>();
      auxiliar->_dado = umDado;
      auxiliar->_proximo = NULL;
      ListaEncadeadaAbstrata<T>::_primeiro = auxiliar;
      return;
    }
    else if (umaPosicao < 1 or umaPosicao > tamanho+1)
    {
      throw posicao_invalida_exception();
    }
    else
    {
      int temp = 0;
      Elemento<T> * aux= ListaEncadeadaAbstrata<T>::_primeiro ;
      while(aux != NULL and temp < umaPosicao - 2 and aux->_proximo != NULL)
      {
        aux = aux->_proximo;
        temp++;
      }
     
      Elemento<T> * novo = new Elemento<T>();
      novo->_dado = umDado;
      //Declarando o novo nodo e seu dado;
      novo->_proximo = aux->_proximo;
      //Fazendo o novo nodo apontar para o próximo
      aux->_proximo = novo;
      //Fazendo o nodo anterior apontar para o novo
    }

   /* if (umaPosicao < 1 or umaPosicao > ListaEncadeadaAbstrata<T>::_tamanho)
    {
      throw posicao_invalida_exception();
    }*/

    return;
  };
  void adicionaNoFim(T umDado) override
  {
    Elemento<T> *novo = new Elemento<T>();
    Elemento<T> *ultimo = ListaEncadeadaAbstrata<T>::_primeiro;

    novo->_dado = umDado;
    novo->_proximo = NULL;

    if (ListaEncadeadaAbstrata<T>::_primeiro == NULL)
    {
      ListaEncadeadaAbstrata<T>::_primeiro = novo;
      return;
    }

    while (ultimo->_proximo != NULL)
    {
      ultimo = ultimo->_proximo;
    }

    ultimo->_proximo = novo;

    return;
  };

  T retiraDoInicio() override
  {
    if (ListaEncadeadaAbstrata<T>::_primeiro == NULL)
    {
      throw lista_encadeada_vazia_exception();
    }

    Elemento<T> *aux = ListaEncadeadaAbstrata<T>::_primeiro;
    //int *ptr = aux->_dado;
    T ptr = aux->_dado;
    ListaEncadeadaAbstrata<T>::_primeiro = ListaEncadeadaAbstrata<T>::_primeiro->_proximo;

    delete aux;

    return ptr;
  };

  T retiraDaPosicao(int umaPosicao) override
  {
    if (ListaEncadeadaAbstrata<T>::_primeiro == NULL)
    {
      throw lista_encadeada_vazia_exception();
    }

    int tamanho = getTamanho();

    if (umaPosicao <= 0 or umaPosicao > tamanho)
    {
      throw posicao_invalida_exception();
    }

    Elemento<T> *auxiliar = ListaEncadeadaAbstrata<T>::_primeiro;

    for (int i = 1; auxiliar != NULL and i < umaPosicao - 1; i++)
    {
      auxiliar = auxiliar->_proximo; //Rodando até o penúltimo nodo
    }
    if (getTamanho() == 1)
    {
      Elemento<T> *teste = ListaEncadeadaAbstrata<T>::_primeiro;
      //int *aux = teste->_dado;
      T aux = teste->_dado;
      delete (teste);
      ListaEncadeadaAbstrata<T>::_tamanho = 0;
      ListaEncadeadaAbstrata<T>::_primeiro = NULL;
      return aux;
    }

    if (auxiliar->_proximo == NULL)
    {
      T a = retiraDoFim();
      return a;
    }

    if (umaPosicao == 1)
    {
      T aux = retiraDoInicio();
      return aux;
    }

    if (auxiliar != NULL or auxiliar->_proximo != NULL)
    {
      Elemento<T> *deletado = auxiliar->_proximo;
      auxiliar->_proximo = auxiliar->_proximo->_proximo;
      //int *aux = deletado->_dado;
      T aux = deletado->_dado;
      delete deletado;
      return aux;
    }

    return 0;
  };

  T retiraDoFim() override
  {
    Elemento<T> *atual = ListaEncadeadaAbstrata<T>::_primeiro;
    if (atual == NULL)
    {
      throw lista_encadeada_vazia_exception();
    }
    if (atual->_proximo == NULL)
    {
      //int *data = atual->_dado;
      T data = atual->_dado;
      //atual == NULL;
      return data;
    }
    else
    {
      Elemento<T> *atual = ListaEncadeadaAbstrata<T>::_primeiro;
      while (atual->_proximo->_proximo != NULL)
      {
        atual = atual->_proximo;
      }

      Elemento<T> *ultimo = atual->_proximo;
      atual->_proximo = NULL;
      //int *aux = ultimo->_dado;
      T aux = ultimo->_dado;
      free(ultimo);

      return aux;
    }

    return 0;
  };

  T retiraEspecifico(T umDado) override // Não está sendo usado
  {
    throw ExcecaoNaoImplementado(__FUNCTION__);
  }
};

#endif