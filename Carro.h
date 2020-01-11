#pragma once

#include "includes.h"

using namespace std;

class Configs;
class DGV;
class Piloto;

class Carro{
    Piloto* p_piloto;
    char caracter_carro;
    string marca, modelo;
    bool stop = false;
    int velocidade = 0, vel_max;
    float capacidade, cap_maxima;
    bool ocupado = false, carregando = false;
    bool danificado = false, sinal_emergencia = false;
public:
    Carro();
    Carro(string path, int n_linhas, int n_le, char caracter_in = '?');
    Carro(string marca, int vel_max, int max, string modelo = "Modelo Base", char caracter = '?');
    ~Carro(){};

	bool tem_piloto() const;

    void mostra_carro(int i) const;

    void muda_ocupado(bool valor){this->ocupado = valor;};
    void muda_velocidade(int nova_vel);
    void muda_danificado(bool valor);
    void muda_carregando(bool valor){this->carregando = valor;};
    void carrega_emergencia(bool valor) {this->sinal_emergencia = valor;};
    void consome(int);
    void carrega_bateria(float);

    bool get_sinal_emergencia() const {return this->sinal_emergencia;};
    int get_capacidade() const {return this->capacidade;};
    int get_cap_max() const {return this->cap_maxima;};
    bool get_opucado(){return this->ocupado;};
    bool get_carregando(){return this->carregando;};
	char get_char() { return caracter_carro; };
    bool get_danificado() const { return danificado; };
    int get_velocidade() const {return this->velocidade;};
    string get_marca() const {return this->marca;};

	void associa_piloto(Piloto* piloto) { this->p_piloto = piloto; };
	void sai_do_carro();

    void muda_stop(bool valor){this->stop = valor;};
    bool get_stop(){return this->stop;};

    Piloto* get_piloto(){return this->p_piloto;};
};