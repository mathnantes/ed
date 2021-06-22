#include <iostream>

using namespace std;

class BST
{
  struct node
  {
    int chave;
    node* esq;
    node* dir;
    node* pai;
  };

  node* raiz;

  node* makeEmpty(node* t)
  {
    if (t == NULL)
      return NULL;
    else
    {
      makeEmpty(t->esq);
      makeEmpty(t->dir);
      delete t;
    }
    return NULL;
  }

  node* inserir(int ch, node* t)
  {
    if (t == NULL)
    {
      t = new node;
      t->chave = ch;
      t->esq = t->dir = NULL;
    }
    else if (ch < t->chave)
    {
      t->esq = inserir(ch, t->esq);
      t->esq->pai = t;
    }
    else if (ch > t->chave)
    {
      t->dir = inserir(ch, t->dir);
      t->dir->pai = t;
    }

    return t;
  }

  node* minimo(node* t)
  {
    if (t == NULL)
      return NULL;
    else if (t->esq == NULL)
      return t;
    else
      return minimo(t->esq);
  }

  node* maximo(node* t)
  {
    if (t == NULL)
      return NULL;
    else if (t->dir == NULL)
      return t;
    else
      return maximo(t->dir);
  }

  node* remover(int ch, node* t)
  {
    node* temp;
    if (t == NULL)
      return NULL;
    else if (ch < t->chave)
      t->esq = remover(ch, t->esq);
    else if (ch > t->chave)
      t->dir = remover(ch, t->dir);
    else if (t->esq && t->dir)
    {
      temp = minimo(t->dir);
      t->chave = temp->chave;
      t->dir = remover(t->chave, t->dir);
    }
    else
    {
      temp = t;
      if (t->esq == NULL)
        t = t->dir;
      else if (t->dir == NULL)
        t = t->esq;

      delete temp;
    }

    return t;
  }

  void emOrdem(node* t)
  {
    if (t == NULL)
      return;

    emOrdem(t->esq);
    cout << t->chave << endl;
    emOrdem(t->dir);
  }

  node* busca(node* t, int ch)
  {
    if (t == NULL)
      return NULL;
    else if (ch < t->chave)
      return busca(t->esq, ch);
    else if (ch > t->chave)
      return busca(t->dir, ch);
    else
      return t;
  }

  node* sucessor(node* t)
  {
    node* aux;

    if (t->dir != NULL)
      return minimo(t->dir);

    aux = t->pai;
    while (aux != NULL && t == aux->dir)
    {
      t = aux;
      aux = aux->pai;
    }

    return aux;
  }

  node* predecessor(node* t)
  {
    node* aux;

    if (t->esq != NULL)
      return maximo(t->esq);

    aux = t->pai;
    while (aux != NULL && t == aux->esq)
    {
      t = aux;
      aux = aux->pai;
    }

    return aux;
  }

public:
  BST();
  ~BST();

  void inserir(int);
  void remover(int);
  void busca(int);
  void sucessor(int);
  void predecessor(int);

  void escrever();
};

BST::BST()
{
  raiz = NULL;
}

BST::~BST()
{
  raiz = makeEmpty(raiz);
}

void
BST::inserir(int ch)
{
  raiz = inserir(ch, raiz);
}

void
BST::remover(int ch)
{
  raiz = remover(ch, raiz);
}

void
BST::busca(int ch)
{
  raiz = busca(raiz, ch);
}

void
BST::sucessor(int ch)
{
  node* suc = NULL;

  suc = busca(raiz, ch);
  suc = sucessor(suc);

  cout << "Sucessor de " << ch << ": ";

  if (suc != NULL)
    cout << suc->chave << endl;
  else
    cout << "Nao tem sucessor!" << endl;
}

void
BST::predecessor(int ch)
{
  node* pred;
  pred = busca(raiz, ch);
  pred = predecessor(pred);

  cout << "Predecessor de " << ch << ": ";

  if (pred != NULL)
    cout << pred->chave << endl;
  else
    cout << "Nao tem predecessor!" << endl;
}

void
BST::escrever()
{
  emOrdem(raiz);
  cout << endl;
}


int
main()
{
  BST t;
  t.inserir(20);
  t.inserir(25);
  t.inserir(15);
  t.inserir(10);
  t.inserir(30);
  t.escrever();
  t.sucessor(30);
  t.sucessor(15);
  t.predecessor(30);
  t.predecessor(10);
  cout << endl;

  t.remover(20);
  t.escrever();
  t.remover(25);
  t.escrever();
  t.remover(30);
  t.escrever();

  // destrutor
  t.~BST();

  return 0;
}
