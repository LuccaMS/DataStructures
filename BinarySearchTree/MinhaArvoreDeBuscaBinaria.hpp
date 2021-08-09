#ifndef MINHAARVOREDEBUSCABINARIA_HPP
#define MINHAARVOREDEBUSCABINARIA_HPP

#include "ArvoreDeBuscaBinaria.hpp"
#include <cassert>
#include <utility>

template <typename T>
class MinhaArvoreDeBuscaBinaria : public ArvoreDeBuscaBinaria<T>
{
private:
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

  int achaMax(int a, int b) const
  {
    if (a >= b)
    {
      return a;
    }
    else
      return b;
  };

  int achaAltura(Nodo<int> *nodo) const
  {
    if (nodo)
    {
      return achaMax(achaAltura(nodo->filhoEsquerda), achaAltura(nodo->filhoDireita)) + 1;
      /*
      Aqui utilizamos a recursão para calcular a altura da tree, basicamente, sempre que ele achar um nodo verdadeiro ele vai 
      somar um e chamar a mesma função para os seus filhos, caso eles forem verdadeiros vai adicionar um, ai por diante, pros 
      filhos dos filhos ..., se o nodo for nulo, ele retorna 0, não adicionando nada na altura
      */
    }
    else
      return 0;
  };

  int quantidade_de_elementos(Nodo<int> *raiz) const
  {
    if (raiz)
    {
      return 1 + quantidade_de_elementos(raiz->filhoEsquerda) + quantidade_de_elementos(raiz->filhoDireita);
      /*
      Aqui utilizamos a recursividade para encontrar a quantidade de elementos, basicamente, chamamos a função mandando a raiz,
      daí, ela verifica se essa raiz existe, se existir, soma 1 e chama a mesma função para ambos os filhos, caso os filhos 
      existam, ela soma para cada um existente e chama para os netos, assim em diante ..., caso em algum momento um nodo seja nulo
      será retornado 0, não alterando na quantidade de elementos
      */
    }
    else
    {
      return 0;
    }
  };
  void inOrder(Nodo<int> *a, ListaEncadeadaAbstrata<int> *teste) const
  {
    if (a)
    {
      inOrder(a->filhoEsquerda, teste);
      teste->adicionaNoFim(a->chave);
      inOrder(a->filhoDireita, teste);
    }
  };
  void postOrder(Nodo<int> *a, ListaEncadeadaAbstrata<int> *teste) const
  {
    if (a)
    {
      postOrder(a->filhoEsquerda, teste);
      postOrder(a->filhoDireita, teste);

      teste->adicionaNoFim(a->chave);
    }
  };
  void preOrder(Nodo<int> *a, ListaEncadeadaAbstrata<int> *teste) const
  {
    if (a)
    {
      teste->adicionaNoFim(a->chave);
      preOrder(a->filhoEsquerda, teste);
      preOrder(a->filhoDireita, teste);
    }
  };

public:
  MinhaArvoreDeBuscaBinaria()
  {
    ArvoreDeBuscaBinaria<T>::_raiz = NULL;
  };
  ~MinhaArvoreDeBuscaBinaria(){
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
    else
    {
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
    }
  };

  /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */

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
        return teste - 1;
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
    bool inseriu = false;                   //Booleano para verificar se já foi inserido a chave;
    Nodo<int> *novo_nodo = new Nodo<int>(); //Alocando o novo nodo
    novo_nodo->chave = chave;               //Declarando a chave do novo nodo como a chave informada
    novo_nodo->filhoDireita = nullptr;
    novo_nodo->filhoEsquerda = nullptr;

    Nodo<T> *raiz_da_arvore = ArvoreDeBuscaBinaria<T>::_raiz;
    if (raiz_da_arvore == NULL)
    {
      raiz_da_arvore = novo_nodo;
      ArvoreDeBuscaBinaria<T>::_raiz = novo_nodo;
    }
    else
    {
      while (raiz_da_arvore and inseriu == false)
      {
        if (raiz_da_arvore->chave == chave)
        {
          //Caso seja igual não precimos inserir novamente
        }
        else if (raiz_da_arvore->chave < chave)
        {
          //Verificando se a chave da raiz é menor que a chave informada, então, nos moveremos para a direita
          if (raiz_da_arvore->filhoDireita == NULL)
          {
            //Caso o filho a direita já seja nulo, já adicionamos o nodo na tree
            raiz_da_arvore->filhoDireita = novo_nodo; //Setando o filho da direita do nodo para a chave
            inseriu = true; //Setando booleano inseriu para true, daí quebrando o loop
          }
          else
          {
            //Se não for nulo, vamos continuar nos movento através da tree
            raiz_da_arvore = raiz_da_arvore->filhoDireita;
          }
        }
        else if (raiz_da_arvore->chave > chave)
        {
          //Como a chave é menor que a chave do nodo, iremos olhar para a esquerda
          if (raiz_da_arvore->filhoEsquerda == NULL)
          {
            //Se o nodo a esquerda for nulo já iremos inserir na tree
            raiz_da_arvore->filhoEsquerda = novo_nodo; //Setando o nodo nulo para o desejado a ser inserido
            inseriu = true; //Booleano setado para true como já inserimos o valor 
          }
          else
          {
            //Redirecionando para o lado esquerdo da tree
            raiz_da_arvore = raiz_da_arvore->filhoEsquerda; 
          }
        }
      }
    }
  };

  void remover(T chave)
  {
    bool deletou = false;
    Nodo<T> *raiz = ArvoreDeBuscaBinaria<T>::_raiz;
    if (raiz->chave == chave and raiz->filhoEsquerda == nullptr and raiz->filhoDireita == nullptr)
    {
      /*
      Primeiro, verificamos se a raiz da árvore é o nodo a ser deletado e se seus filhos são ponteiros nulos
      Daí, deletamos a raiz e setamos ela para nula e retornamos a função void.
      */
      delete raiz;
      raiz = NULL;
      ArvoreDeBuscaBinaria<T>::_raiz = NULL;
      return;
    }
    while (raiz and deletou == false)
    {
      /*
      Loop enquanto a raiz verdadeira e o booleano deletou é falso.
      */
      if (raiz->chave == chave)
      {
        /*
        Aqui, verificamos inicialmente se o nodo é a chave a ser deletada.
        */
        if (raiz->filhoDireita and raiz->filhoDireita->filhoEsquerda)
        {
          /*
          Primeiro, verificamos se a raiz tem um filho a direita, então, se o filho a direita tem um filho a esquerda,
          fazemos isso porque assim garantimos que as regras da tree são seguidas, os filhos a esquerda da raiz ainda
          são menores que o neto em questão, então, iremos tornar ele a raiz porque ainda cumprimos as regras da tree.
          */
         // NOTA
         // Aqui o ideal seria rodarmos um loop para encontrar o filho mais a esquerda do elemento a direita da raiz, porque
         // assim encontrariamos o menor valor que ainda é maior que a raiz e cumpre as regras, aqui eu peguei logo o seguinte
         // mas para o código ser funcional em 100% dos casos deveriamos mudar isso 

          int chave_nova = raiz->filhoDireita->filhoEsquerda->chave; //Pegando a chave do neto
          delete raiz->filhoDireita->filhoEsquerda; //Deletando o neto
          raiz->filhoDireita->filhoEsquerda = NULL; //Tornando o neto como nulo
          raiz->chave = chave_nova; //Trocando a chave da raiz para a chave do neto
          deletou = true; //Setando o booleano deletou para true
          break; //Saindo
        }
        else if (raiz->filhoDireita and raiz->filhoDireita->filhoDireita)
        {
          /*
          Nesse caso, queremos deletar a raiz, contudo, ela tem um filho a direita, que tem um filho a direita, então, pegamos
          os dados do neto, e deletamos e setamos ele para nulo, após isso, a raiz recebe os dados do filho e o filho do neto.
          */
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
          //Assim deletamos o nodo e como esse nodo só tinha um filho, agora o avô toma conta dele
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
    ListaEncadeadaAbstrata<int> *p = new MinhaListaEncadeada<int>;
    Nodo<T> *nodo = ArvoreDeBuscaBinaria<T>::_raiz;

    inOrder(nodo, p);

    return p;
  };

  ListaEncadeadaAbstrata<T> *preOrdem() const
  {
    ListaEncadeadaAbstrata<int> *p = new MinhaListaEncadeada<int>;
    Nodo<T> *nodo = ArvoreDeBuscaBinaria<T>::_raiz;
    preOrder(nodo, p);
    return p;
  };

  ListaEncadeadaAbstrata<T> *posOrdem() const
  {
    ListaEncadeadaAbstrata<int> *p = new MinhaListaEncadeada<int>;
    Nodo<T> *nodo = ArvoreDeBuscaBinaria<T>::_raiz;
    postOrder(nodo, p);
    return p;
  };
};

#endif
