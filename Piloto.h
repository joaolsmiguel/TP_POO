#pragma once

#include "includes.h"

using namespace std;

class Carro;
class Campeonato;

class Piloto{
    string nome, tipo; //   TIPO = OUTRA CLASSE
    bool associado;
    int pontos = 0;
public:
    Piloto(string in_nome, string in_tipo);
    virtual ~Piloto(){};

    void mostra_pilotos(int i) const;

    string get_tipo(){return this->tipo;};
    
    string get_nome(){return this->nome;}
    bool get_associado(){return this->associado;};
    void muda_associado(bool valor){this->associado = valor;};

    void muda_pontos(int valor){this->pontos = pontos + valor;};
    int get_pontos() const {return this->pontos;};
    
    virtual void acelera(vector<struct pista>&, int) = 0;
};


class Crazy : public Piloto{
public:
	Crazy(string in_nome, string in_tipo) : Piloto(in_nome, in_tipo){};
    void acelera(vector<struct pista>&, int);/*segundo*/  /*lugar*/
};

class Rapido : public Piloto {
public:
	Rapido(string in_nome, string in_tipo) : Piloto(in_nome, in_tipo) {};
    void acelera(vector<struct pista>&, int); /*qualquer merda com segundo*/
};

class Surpresa : public Piloto {
public:
	Surpresa(string in_nome, string in_tipo) : Piloto(in_nome, in_tipo) {};
    void acelera(vector<struct pista>&, int);
};
