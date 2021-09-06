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
    if(contem(dado))
    {
      size_t indice = funcaoEspalhamento(dado);
      int posicao_do_dado_na_lista = this->_tabela.at(indice).posicao(dado);
      this->_tabela.at(indice).retiraDaPosicao(posicao_do_dado_na_lista);
    }
    else{
      throw ExcecaoDadoInexistente();
    }
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
    size_t aux = capacidade();  
    size_t qtd_indice = capacidade(); 
    if constexpr(!std::is_integral<T>::value){
      size_t somatorio = 0; 
      int expo = 1;  
      for(unsigned int i = 0; i < dado.length();i++)
      {
        int conversao = int(dado[i]);
        somatorio += conversao*pow(31,dado.length() - expo); 
        expo++; 
      }
      size_t indice_esperado = somatorio % aux; 
      return indice_esperado; 
    }
    else{
      size_t indice_esperado = dado % aux;  
      return indice_esperado;
    }
  }
};

#endif
