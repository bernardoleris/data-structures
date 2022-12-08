#include <iostream>
#include <string>
using namespace std;

struct produto{
    string nome;
    int quantidade;
};

class noh {
friend class lista;
private:
    produto mProduto;
    noh* proximo;
public:
    noh(produto p);
};

noh::noh(produto p) : mProduto(p){
    proximo = NULL;
}

class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos();
public:
    lista();
    ~lista();
    inline void insere(produto p);
    void insereNoFim(produto p);
    void insereNoInicio(produto p);
    void insereNaPosicao(int posicao, produto p);
    void removeNoFim();
    void removeNoInicio();
    void removeValor(produto p);
    int procura(produto p);
    int contaEspera(produto p);
    void imprimeTodos();
    void imprimeUm(string nomeProduto);
    inline bool vazia();
};

lista::lista(){ //construtor
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

lista::~lista() { //destrutor
    removeTodos();
}

void lista::removeTodos(){
    noh* aux = primeiro;
    noh* temp;
    while (aux != NULL) {
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

void lista::insere(produto p) {
    insereNoFim(p);
}

void lista::insereNoFim(produto p) {
    noh* novo = new noh(p);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void lista::insereNoInicio(produto p) {
    noh* novo = new noh(p);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

int lista::procura(produto p){
    noh* aux = primeiro;
    int posAux = 0;
    while((aux != NULL) and (aux->mProduto.nome != p.nome)){
        posAux++; 
        aux = aux->proximo;
    }
    if(aux == NULL){
        posAux = -1;
    }
    return posAux;
}

inline bool lista::vazia(){
    return (primeiro == NULL);
}

void lista::removeValor(produto p){
    noh* aux = primeiro;
    noh* anterior;
    while ((aux != NULL) and (aux->mProduto.nome != p.nome)){
        anterior = aux;
        aux = aux->proximo;
    }
    if(aux != NULL){
        if(aux == primeiro){
            removeNoInicio();
        }else if(aux == ultimo){
            removeNoFim();
        }else{
        anterior->proximo = aux->proximo;
        tamanho--;
        delete aux;
        } 
    }
}

void lista::removeNoFim(){
    noh* aux = primeiro;
    noh* anterior;
    while (aux->proximo != NULL){
        anterior = aux;
        aux = aux->proximo;
    }
    delete ultimo;
    anterior->proximo = NULL;
    ultimo = anterior;
    if (vazia()){
        primeiro = NULL;
    }
    tamanho--;
}

void lista::removeNoInicio(){
    noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vazia()){
        ultimo = NULL;
    }
}

int lista::contaEspera(produto p){
  int cont = -1;
  noh* aux = primeiro;
  while (aux != NULL){
    if(aux->mProduto.nome == p.nome){
      cont ++;
    }
    aux = aux->proximo;
  }
  return cont;
}

void lista::imprimeTodos(){
    noh* aux = primeiro;
    int tam = tamanho;
    if (tam>0){
        cout << "[";
        for (int i=tam; i>1; i--){
            cout << "(" << aux->mProduto.nome << ", " << aux->mProduto.quantidade << "), ";
            aux = aux->proximo;
        } 
    cout << "(" << aux->mProduto.nome << ", " << aux->mProduto.quantidade << ")";
    cout << "]";
    }else{
        cout << "[]";
    }
}

void lista::imprimeUm(string nomeProduto){
    noh* aux = primeiro;
    int tam = tamanho;
    
    while(aux->mProduto.nome != nomeProduto){
        aux = aux->proximo;
    }
    cout << "(" << aux->mProduto.nome << ", " << aux->mProduto.quantidade << ")";
    cout << endl;
}

int main(){
    lista minhaLista;
    produto mProduto;
    char opcao;
    do{
        cin >> opcao;
        switch (opcao){
        case 'i':
            cin >> mProduto.nome;
            if(minhaLista.procura(mProduto)==-1){
                cin >> mProduto.quantidade;
                minhaLista.insereNoFim(mProduto);
            }else{
            }
            break;
        case 'r':
            cin >> mProduto.nome;
            if(minhaLista.procura(mProduto)==-1){
                cout << "item nao existente" << endl;
            }else{
                minhaLista.removeValor(mProduto);
            }
            break;
        case 'c':
            cin >> mProduto.nome;
            if(minhaLista.procura(mProduto)==-1){
                cout << "item nao existente" << endl;
            }else{
                minhaLista.imprimeUm(mProduto.nome);
            }
            break;
        case 'p':
            minhaLista.imprimeTodos();
            break;
        }
    }while (opcao != 'q');
    minhaLista.imprimeTodos();
    
    return 0;
}