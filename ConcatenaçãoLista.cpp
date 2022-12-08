#include <iostream>
#include <string>
using namespace std;

typedef int Dado;

class noh {
friend class lista;
private:
    const Dado dado;;
    noh* proximo;
public:
    noh(Dado d = 0);
};

noh::noh(Dado d) : dado(d){
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
    lista(const lista& umaLista);
    ~lista();
    lista& operator=(const lista& umaLista);
    inline void insere(Dado dado);
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void insereNaPosicao(int posicao, Dado dado);
    void removeNoFim();
    void removeNoInicio();
    void removeValor(Dado valor);
    int procura(Dado valor);
    void imprimeTodos();
    int espia();
    inline bool vazia();
};

lista::lista(){ //construtor
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

lista::lista(const lista& umaLista){
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
    noh* aux = umaLista.primeiro;
    while(aux != NULL){
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
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

lista& lista::operator=(const lista& umaLista){
    removeTodos();
    noh* aux = umaLista.primeiro;
    while(aux!=NULL){
        insereNoFim(aux->dado);
        aux = aux->proximo;
    }
    return *this;
}

void lista::insere(Dado dado) {
    insereNoFim(dado);
}

void lista::insereNoFim(Dado dado) {
    noh* novo = new noh(dado);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void lista::insereNoInicio(Dado dado) {
    noh* novo = new noh(dado);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

int lista::procura(Dado valor){
    noh* aux = primeiro;
    int posAux = 0;
    while((aux != NULL) and (aux->dado != valor)){
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

void lista::removeValor(Dado valor){
    noh* aux = primeiro;
    noh* anterior;
    while ((aux != NULL) and (aux->dado != valor)){
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

int lista::espia(){
    return primeiro->dado;
}

void lista::imprimeTodos(){
    noh* aux = primeiro;
    int tam = tamanho;
    if (tam>0){
        for (int i=tam; i>0; i--){
            cout << aux->dado << " ";
            aux = aux->proximo;
        }
    } 
    cout << endl;
}

int main(){
    lista minhaLista1;
    lista minhaLista2;
    lista minhaLista3;
    int vetor[3];
    int dado;
    for(int i=0; i<5; i++){
        cin >> dado;
        minhaLista1.insereNoFim(dado);
    }
    
    for(int i=0; i<5; i++){
        cin >> dado;
        minhaLista2.insereNoFim(dado);
    }
    
    for(int i=0; i<3; i++){
        cin >> vetor[i];
    }

    for(int i=0; i<5; i++){
        minhaLista3.insereNoFim(minhaLista1.espia());
        minhaLista1.insereNoFim(minhaLista1.espia());
        minhaLista1.removeNoInicio();
    }

    for(int i=0; i<5; i++){
        minhaLista3.insereNoFim(minhaLista2.espia());
        minhaLista2.insereNoFim(minhaLista2.espia());
        minhaLista2.removeNoInicio();
    }
    minhaLista3.imprimeTodos();
    minhaLista1.imprimeTodos();
    minhaLista2.imprimeTodos();
    minhaLista3.removeValor(vetor[0]);
    minhaLista3.removeValor(vetor[1]);
    minhaLista3.removeValor(vetor[2]);
    minhaLista3.imprimeTodos();

    return 0;
}