#include <iostream>
#include <string>

using namespace std;

    class Noh {
        friend class Fila;
        private:
            string dado; //poderia ser outra variável
            Noh *mProximo;
        public:
            Noh(string info){
                dado = info;
                mProximo = NULL;
            }
            ~Noh(){
                mProximo = NULL;
                delete mProximo;
            }
    };

// fila dinamicamente encadeada
    class Fila {
    private:
        Noh* mInicio;
        Noh* mFim;
        int mTamanho;
    public:
        Fila();
        ~Fila();
        void enfileira(string info);
        string desenfileira();
        void limpaFila();
        bool estaVazia(); // verifica se existem elementos na fila     
};


Fila::Fila() {
    mInicio = NULL;
    mFim = NULL;
    mTamanho = 0;
}

Fila::~Fila() { 
    limpaFila();
}

void Fila::limpaFila(){
    while(mTamanho>0){
        desenfileira();
    }
}

void Fila::enfileira(string info) {
    Noh* novo = new Noh(info);
    if(mTamanho==0){
        mInicio = novo;
    }else{
        mFim->mProximo = novo;
    }
    mFim = novo;
    mTamanho++;
}

string Fila::desenfileira() {
    string info = mInicio->dado;
    Noh* temp = mInicio;
    mInicio = mInicio->mProximo;
    delete temp;
    mTamanho--;
    if(mTamanho==0){
        mFim = NULL;
    }
    return info;
}
    
bool Fila::estaVazia() {
    return (mTamanho==0);
}

int main() {
    Fila f1, f2;
    int quantidade = 0;
    string opcao, nomeNormal, nomePrioridade, elemento1, elemento2;
    
    do{
        cin >> opcao;
        if(opcao=="normal"){
            cin >> nomeNormal;
            f1.enfileira(nomeNormal);
    
        }else if(opcao=="prioridade"){
            cin >> nomePrioridade;
            f2.enfileira(nomePrioridade);
        
        }else if(opcao=="atender"){
            if((quantidade!=3 and !f2.estaVazia()) or (f1.estaVazia() and !f2.estaVazia())){
                    quantidade++;
                    elemento2 = f2.desenfileira();
                    cout << elemento2 << endl;
            }else if(!f1.estaVazia()){
                quantidade = 0;
                elemento1 = f1.desenfileira();
                cout << elemento1 << endl;
            }else if(f1.estaVazia() and f2.estaVazia()){
                cout << "AGUARDE" << endl;
            }
        }
    }while (opcao!="fim");
    
    return 0;
}
