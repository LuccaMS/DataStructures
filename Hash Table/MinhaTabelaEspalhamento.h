#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H
#include <cmath>
#include <cctype>
#include <type_traits>

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

template <typename T, std::size_t _capacidade>
class MinhaTabelaEspalhamento final : public TabelaEspalhamentoAbstrata<T, _capacidade>
{
public:
  MinhaTabelaEspalhamento(){

  };
  ~MinhaTabelaEspalhamento(){

  };

  std::size_t capacidade() const override
  {
    return _capacidade;
  }

  void inserir(T dado) override
  {
    size_t indice = funcaoEspalhamento(dado);
    this->_tabela.at(indice).adicionaNoFim(dado);
  }

  void remover(T dado) override
  {
    size_t indice = funcaoEspalhamento(dado);
    int posicao_do_dado_na_lista = this->_tabela.at(indice).posicao(dado);
    this->_tabela.at(indice).retiraDaPosicao(posicao_do_dado_na_lista);
  }

  bool contem(T dado) const override
  {
    for (unsigned int i = 0; i < this->_tabela.size(); i++)
    {
      if (this->_tabela.at(i).contem(dado))
      {
        return true;
      }
    }
    return false;
  }

  std::size_t quantidade() const override
  {
    int count = 0;
    for (unsigned int i = 0; i < this->_tabela.size(); i++)
    {
      count += this->_tabela.at(i).getTamanho();
    }
    return count;
  }
  std::size_t funcaoEspalhamento(T dado) const override
  {
    size_t aux = capacidade();  //capacity of the hash table
    int qtd_indice = capacidade(); //capacity of the hash table
    if constexpr(!std::is_integral<T>::value){
      int somatorio = 0; //sum of the convertion to int
      int expo = -1;  //the exponential of the method
      for(unsigned int i = 0; i < dado.length();i++)
      {
        somatorio += pow(dado[i]*31,qtd_indice - expo); //incrementing each conversion of int 
        expo--; 
      }
      size_t indice_esperado = somatorio % aux; //finding the expected indice of the data in the hash table
      return indice_esperado; //returning the expected indice
    }
    else{
      size_t indice_esperado = dado % aux;  // here i'm doing the same thing but the data is a integer so 
      return indice_esperado;
    }
  }
};

#endif
