#include "Autodromo.h"

Autodromo::Autodromo(string in_nome, float comp, int mx_cars){
    nome = in_nome;
    comprimento = comp;
    max_carros_pista = mx_cars;
}

void Autodromo::mostra_autodromo(int i){
    cout << i+1 << " Autodromo: " << nome << " comprimento pista: " << comprimento << " capacidade: " << max_carros_pista << endl;
}