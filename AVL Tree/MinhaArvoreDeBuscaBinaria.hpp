#ifndef MINHAARVOREDEBUSCABINARIA_HPP
#define MINHAARVOREDEBUSCABINARIA_HPP

#include "ArvoreDeBuscaBinaria.hpp"
#include <cassert>
#include <utility>

template <typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
protected:
  Nodo<int> *redirect(Nodo<int> *raiz, int key)
  {
    if (raiz->chave < key)
    {
      raiz = raiz->filhoDireita;
      return raiz;
    }
    else if (raiz->chave > key)
    {
      raiz = raiz->filhoEsquerda;
      return raiz;
    }
    return raiz;
  };

    int achaAltura(Nodo<T> *nodo) const
    {
        if (nodo)
        {
            int altura_esq = achaAltura(nodo->filhoEsquerda);
            int altura_direita = achaAltura(nodo->filhoDireita);
            if(altura_esq >= altura_direita)
            {
                return altura_esq + 1;
            }
            else{
                return altura_direita + 1;
            }
        }
        else
        {
            return 0;
        }
    };

  int quantidade_de_elementos(Nodo<int> *raiz) const
  {
    if (raiz)
    {
      return 1 + quantidade_de_elementos(raiz->filhoEsquerda) + quantidade_de_elementos(raiz->filhoDireita);
    }
    else
    {
      return 0;
    }
  };
  void emOrdemm(Nodo<int> *a, ListaEncadeadaAbstrata<int> *teste) const
  {
    if (a)
    {
      emOrdemm(a->filhoEsquerda, teste);
      teste->adicionaNoFim(a->chave);
      emOrdemm(a->filhoDireita, teste);
    }
  };
  void posOrdemm(Nodo<int> *a, ListaEncadeadaAbstrata<int> *teste) const
  {
    if (a)
    {
      posOrdemm(a->filhoEsquerda, teste);
      posOrdemm(a->filhoDireita, teste);

      teste->adicionaNoFim(a->chave);
    }
  };
  void preOrdemm(Nodo<int> *a, ListaEncadeadaAbstrata<int> *teste) const
  {
    if (a)
    {
      teste->adicionaNoFim(a->chave);
      preOrdemm(a->filhoEsquerda, teste);
      preOrdemm(a->filhoDireita, teste);
    }
  };

  void DestrutorRecursivo(Nodo<T> * nodo)
  {
    if(nodo)
    {
      DestrutorRecursivo(nodo->filhoEsquerda);
      DestrutorRecursivo(nodo->filhoDireita);
      delete nodo;
    }
  };

public:
  MinhaArvoreDeBuscaBinaria()
  {
    ArvoreDeBuscaBinaria<T>::_raiz = NULL;
  };
  ~MinhaArvoreDeBuscaBinaria(){
    Nodo<T> * auxiliar = ArvoreDeBuscaBinaria<T>::_raiz;
    DestrutorRecursivo(auxiliar);
  };

  bool vazia() const
  {
    if (ArvoreDeBuscaBinaria<T>::_raiz == NULL)
    {
      return true;
    }
    else
    {
      return false;
    }
  };

  int quantidade() const
  {
    Nodo<int> *raiz = ArvoreDeBuscaBinaria<int>::_raiz;
    if (raiz)
    {
      int qtd = quantidade_de_elementos(raiz);
      return qtd;
    }
    else
      return 0;
  };

  bool contem(T chave) const override
  {
    bool achei = false;
    Nodo<T> *raiz_da_arvore = ArvoreDeBuscaBinaria<T>::_raiz;
    if (raiz_da_arvore == NULL)
    {
      return false;
    }

    while (raiz_da_arvore)
    {
      if (raiz_da_arvore->chave == chave)
      {
        achei = true;
        break;
      }
      else if (raiz_da_arvore->chave > chave)
      {
        raiz_da_arvore = raiz_da_arvore->filhoEsquerda;
      }
      else if (raiz_da_arvore->chave < chave)
      {
        raiz_da_arvore = raiz_da_arvore->filhoDireita;
      }
    }

    if (achei == true)
    {
      return true;
    }

    else
      return false;
  };

  std::optional<int> altura(T chave) const
  {
    bool esta_na_arvore = false;
    Nodo<int> *nodo = MinhaArvoreDeBuscaBinaria<int>::_raiz;
    if (nodo and chave != 0)
    {
      while (nodo and esta_na_arvore == false)
      {
        if (nodo->chave == chave)
        {
          esta_na_arvore = true;
        }
        else if (nodo->chave > chave)
        {
          nodo = nodo->filhoEsquerda;
        }
        else if (nodo->chave < chave)
        {
          nodo = nodo->filhoDireita;
        }
      }
      /*
      O loop while acima será o resposável para chegarmos no nodo solicitado, quando ele chegar, vai verificar se a chave é
      a solicitada e então irá parar o loop
      */
      if (esta_na_arvore == true)
      {
        //Aqui verificamos se o nodo está na arvore, então, chamamos a função para calcular a altura.
        int teste = achaAltura(nodo);
        return teste -1;
      }
      else if (!esta_na_arvore)
      {
        //Caso ele não esteja na árvore nós retornamos nullpot
        return std::nullopt;
      }
    }
    else if (nodo and chave == 0)
    {
      //Neste caso, queremos achar a altura da árvore inteira, então, mandamos a raiz ao invés de rodar um while até o solicitado
      int altura = achaAltura(nodo);
      return altura;
    }
    else if (esta_na_arvore == false)
    {
      return std::nullopt;
    }

    return 0;
  };

  void inserir(T chave) override
  {
    bool inseriu = false;
    Nodo<T> *novo_nodo = new Nodo<T>();
    novo_nodo->chave = chave;
    novo_nodo->filhoDireita = NULL;
    novo_nodo->filhoEsquerda = NULL;

    Nodo<T> *raiz_da_arvore = ArvoreDeBuscaBinaria<T>::_raiz;
    if (raiz_da_arvore == NULL)
    {
      raiz_da_arvore = novo_nodo;
      ArvoreDeBuscaBinaria<T>::_raiz = novo_nodo;
    }

    while (raiz_da_arvore and inseriu == false)
    {
      if (raiz_da_arvore->chave == chave)
      {
      }
      else if (raiz_da_arvore->chave < chave)
      {
        if (raiz_da_arvore->filhoDireita == NULL)
        {
          raiz_da_arvore->filhoDireita = novo_nodo;
          inseriu = true;
        }
        else
        {
          raiz_da_arvore = raiz_da_arvore->filhoDireita;
        }
      }
      else if (raiz_da_arvore->chave > chave)
      {
        if (raiz_da_arvore->filhoEsquerda == NULL)
        {
          raiz_da_arvore->filhoEsquerda = novo_nodo;
          inseriu = true;
        }
        else
        {
          raiz_da_arvore = raiz_da_arvore->filhoEsquerda;
        }
      }
    }
  };

  void remover(T chave)
  {
    bool deletou = false;
    Nodo<T> *raiz = ArvoreDeBuscaBinaria<T>::_raiz;
    if (raiz->chave == chave and raiz->filhoEsquerda == NULL and raiz->filhoDireita == NULL)
    {
      delete raiz;
      raiz = NULL;
      return;
    }
    while (raiz and deletou == false)
    {
      if (raiz->chave == chave)
      {
        if (raiz->filhoDireita and raiz->filhoDireita->filhoEsquerda)
        {
          int chave_nova = raiz->filhoDireita->filhoEsquerda->chave;
          delete raiz->filhoDireita->filhoEsquerda;                 
          raiz->filhoDireita->filhoEsquerda = NULL;                 
          raiz->chave = chave_nova;                                  
          deletou = true;                                            
          break;                                                    
        }
        else if (raiz->filhoDireita and raiz->filhoDireita->filhoDireita)
        {
          int chave_nova = raiz->filhoDireita->chave;
          int outra_chave = raiz->filhoDireita->filhoDireita->chave;
          delete raiz->filhoDireita->filhoDireita;
          raiz->filhoDireita->filhoDireita = NULL;
          raiz->chave = chave_nova;
          raiz->filhoDireita->chave = outra_chave;
          deletou = true;
          break;
        }
        else if (raiz->filhoDireita and raiz->filhoEsquerda)
        {
          int chave_nova = raiz->filhoDireita->chave;
          delete raiz->filhoDireita;
          raiz->filhoDireita = NULL;
          raiz->chave = chave_nova;
          deletou = true;
          break;
        }
      }
      else if (raiz->filhoDireita and raiz->filhoDireita->chave == chave)
      {
        if (raiz->filhoDireita->filhoDireita == NULL and raiz->filhoDireita->filhoEsquerda == NULL)
        {
          delete raiz->filhoDireita;
          raiz->filhoDireita = NULL;
          break;
        }
        else if (raiz->filhoDireita->filhoDireita == NULL and raiz->filhoDireita->filhoEsquerda != NULL)
        {
          Nodo<T> *filho_do_nodo_a_ser_deletado = raiz->filhoDireita->filhoEsquerda;
          delete raiz->filhoDireita;
          raiz->filhoDireita = filho_do_nodo_a_ser_deletado;
          break;
        }
        else if (raiz->filhoDireita->filhoDireita != NULL and raiz->filhoDireita->filhoEsquerda == NULL)
        {
          Nodo<T> *filho_do_nodo_a_ser_deletado = raiz->filhoDireita->filhoDireita;
          delete raiz->filhoDireita;
          raiz->filhoDireita = filho_do_nodo_a_ser_deletado;
          //Assim deletamos o nodo e como esse nodo só tinha um filho, agora o avô toma conta dele
          break;
        }
      }
      else if (raiz->filhoEsquerda and raiz->filhoEsquerda->chave == chave)
      {

        if (raiz->filhoEsquerda->filhoDireita == NULL and raiz->filhoEsquerda->filhoEsquerda == NULL)
        {
          delete raiz->filhoEsquerda;
          raiz->filhoEsquerda = NULL;
          break;
        }
        else if (raiz->filhoEsquerda->filhoDireita == NULL and raiz->filhoEsquerda->filhoEsquerda != NULL)
        {
          Nodo<T> *filho_do_nodo_a_ser_deletado = raiz->filhoEsquerda->filhoEsquerda;
          delete raiz->filhoEsquerda;
          raiz->filhoEsquerda = filho_do_nodo_a_ser_deletado;
          break;
          //Assim deletamos o nodo e como esse nodo só tinha um filho, agora o avô toma conta dele
        }
        else if (raiz->filhoEsquerda->filhoDireita != NULL and raiz->filhoEsquerda->filhoEsquerda == NULL)
        {
          Nodo<T> *filho_do_nodo_a_ser_deletado = raiz->filhoEsquerda->filhoDireita;
          delete raiz->filhoEsquerda;
          raiz->filhoEsquerda = filho_do_nodo_a_ser_deletado;
          break;
          //Assim deletamos o nodo e como esse nodo só tinha um filho, agora o avô toma conta dele
        }
        else
        {
          raiz = redirect(raiz, chave);
        }
      }
      else if (raiz->chave < chave)
      {
        raiz = raiz->filhoDireita;
      }
      else if (raiz->chave > chave)
      {
        raiz = raiz->filhoEsquerda;
      }
    }
  };

  std::optional<int> filhoEsquerdaDe(T chave) const
  {
    Nodo<T> *raiz_da_arvore = ArvoreDeBuscaBinaria<T>::_raiz;
    bool achei = false;
    while (raiz_da_arvore)
    {
      if (raiz_da_arvore->chave == chave)
      {
        achei = true;
        break;
      }
      else if (raiz_da_arvore->chave < chave)
      {
        raiz_da_arvore = raiz_da_arvore->filhoDireita;
      }
      else if (raiz_da_arvore->chave > chave)
      {
        raiz_da_arvore = raiz_da_arvore->filhoEsquerda;
      }
    }
    if (achei == true)
    {
      if (raiz_da_arvore->filhoEsquerda)
      {
        return raiz_da_arvore->filhoEsquerda->chave;
      }
      else
      {
        return std::nullopt;
      }
    }
    else if (achei == false)
    {
      return std::nullopt;
    }

    return std::nullopt;
  };

  std::optional<int> filhoDireitaDe(T chave) const
  {
    Nodo<T> *raiz_da_arvore = ArvoreDeBuscaBinaria<T>::_raiz;
    bool achei = false;
    while (raiz_da_arvore)
    {
      if (raiz_da_arvore->chave == chave)
      {
        achei = true;
        break;
      }
      else if (raiz_da_arvore->chave < chave)
      {
        raiz_da_arvore = raiz_da_arvore->filhoDireita;
      }
      else if (raiz_da_arvore->chave > chave)
      {
        raiz_da_arvore = raiz_da_arvore->filhoEsquerda;
      }
    }
    if (achei == true)
    {
      if (raiz_da_arvore->filhoDireita)
      {
        return raiz_da_arvore->filhoDireita->chave;
      }
      else
      {
        return std::nullopt;
      }
    }
    else if (achei == false)
    {
      return std::nullopt;
    }
    return std::nullopt;
  };

  ListaEncadeadaAbstrata<T> *emOrdem() const
  {
    ListaEncadeadaAbstrata<T> *p = new MinhaListaEncadeada<T>;
    Nodo<T> *nodo = ArvoreDeBuscaBinaria<T>::_raiz;

    emOrdemm(nodo, p);

    return p;
  };

  ListaEncadeadaAbstrata<T> *preOrdem() const
  {
    ListaEncadeadaAbstrata<T> *p = new MinhaListaEncadeada<T>;
    Nodo<T> *nodo = ArvoreDeBuscaBinaria<T>::_raiz;

    preOrdemm(nodo, p);

    return p;
  };

  ListaEncadeadaAbstrata<T> *posOrdem() const
  {
    ListaEncadeadaAbstrata<T> *p = new MinhaListaEncadeada<T>;
    Nodo<T> *nodo = ArvoreDeBuscaBinaria<T>::_raiz;

    posOrdemm(nodo, p);

    return p;
  };
};

#endif
