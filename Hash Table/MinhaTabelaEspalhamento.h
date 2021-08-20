#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include <cctype>

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

template<typename T, std::size_t _capacidade>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, _capacidade>
{
  private:
  bool verificar_string(std::string str)
  {
    for(unsigned int i = 0; i < str.length();i++)
    {
      if(std::isdigit(str[i]) == true)
      {
        return true
      }
    }
    return false;
  }

  public:
  MinhaTabelaEspalhamento(){

  };
  ~MinhaTabelaEspalhamento(){


  };

  std::size_t capacidade() const override
  {
    std::array<MinhaListaEncadeada<T>,_capacidade> teste= TabelaEspalhamentoAbstrata<T, _capacidade>::_tabela;
    int count = 0;
    for(unsigned int i = 0; i < teste.size();i++)
    {
      count++;
    }
    return count;
  }

  void inserir(T dado) override
  {
    std::size_t index = funcaoEspalhamento(dado);
   
  }

  void remover(T dado) override
  {
    
  }

  bool contem(T dado) const override
  {
    return true;
  }

  std::size_t quantidade() const override
  {
    return 5;
  }

  std::size_t funcaoEspalhamento(T dado) const override
  {
    if(verificar_string(dado))
    {
      int soma = 0;
      for(unsigned int i = 0; i < dado.length();i++)
      {
        soma += int(dado[i]); //somando os dados ASCII de todas as letras da string
      }
      return soma % capacidade();
    }
    else{
      int soma = 0;
      for(unsigned int i = 0; i < dado.length();i++)
      {
        soma += dado[i];
      }
      return soma % capacidade();
    }
    
  }

};

#endif
