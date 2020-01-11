#pragma once

#include "includes.h"

using namespace std;

class Autodromo{
    int max_carros_pista;
    float comprimento;
    string nome;
public:
    Autodromo(string, float , int);

    string get_nome(){return this->nome;}

    void mostra_autodromo(int i);
    int get_cap_max_pista(){return this->max_carros_pista;};
    float get_comp_pista(){return this->comprimento;};

    ~Autodromo(){};
};