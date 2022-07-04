#include <iostream>
#include <list>
#include <stdlib.h>
using namespace std;

class TabelaHash {
    public:
        int quantidade, max_quantidade, tamanho_vetor;
        std::list<int> *estrutura;

        TabelaHash(int vetor) {
            this->quantidade = 0;
            this->tamanho_vetor = vetor;
            this->estrutura = new std::list<int>[tamanho_vetor];
            this->max_quantidade = (100 * tamanho_vetor)/100;
        }

        ~TabelaHash() {
            delete[] this->estrutura;
        }

        int hash(int numero) {
            return (numero % tamanho_vetor);
        }

        void inserir(int numero) {
            if (this->quantidade < this->max_quantidade) {
                this->estrutura[hash(numero)].push_front(numero);
                this->quantidade++;
            }
        }

        bool remover(int numero) {
            bool num = buscar(numero);
            if (num) {
                this->estrutura[hash(numero)].remove(numero);
                this->quantidade--;
            }
            return num;
        }

        bool buscar(int numero) {
            int count = 0;
            bool retorno = false;
            int elemento = hash(numero);
            for (int num : this->estrutura[elemento]) {
                count++;
                if (num == numero) {
                    retorno = true;
                    break;
                }
            }
            cout << "\n";
            cout << "Numero de interacoes Tabela hash: " << count;
            cout << "\n";
            return retorno;
        }

        /* Metodo auxiar, não efetivamente está na estrutura */
        void imprimir() {
            for (int i = 0; i < tamanho_vetor; i++) {
                cout << "\n"<<"Posicao:"<<i<<" :  ";
                for (int num : this->estrutura[i]){
                    cout <<'[';
                    cout << num;
                    cout << ']';
                }
            }
        }
        
        /* Metodo auxiar, não efetivamente está na estrutura */
        void contar() {
            int maior = 0;
            for (int i = 0; i < tamanho_vetor; i++) {
                int t = 0;
                for (int num : this->estrutura[i]){
                    t += 1;
                }
                if (t > maior) {
                    maior = t;
                }
            }
            cout << "\nNumero maximo de colisoes: " << maior;
        }
};

int main() {
    // valores para teste => 100, 1000, 10000, 100000
    int size = 100000;
    TabelaHash tabela = TabelaHash(size);

    /* Iserção*/
    for (int i = 0; i < size; i++) {
        int num = rand() % 1000000;
        tabela.inserir(num);
    }

    //tabela.imprimir();

    // Numero para buscar e excluir
    int find_number = 29996;
    
    /* Busca */
    cout << "\nBusca ============================";
    tabela.buscar(find_number);

    /* Remoção */
    cout << "\nRemocao ============================";
    tabela.remover(find_number);
    
    tabela.contar();
}