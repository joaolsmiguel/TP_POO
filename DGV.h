#pragma once

#include "includes.h"
//#include "Piloto.h"

using namespace std;

class Carro;
class Configs;
class Piloto;
class Autodromo;

/*
struct struct_DGV{
    vector<Carro*> carros;
    vector<Piloto*> pilotos;
};
*/

class DGV{
    Carro* obj_carro;//esta aqui so para funcionar o return do ponteiro para obter todas as informacoes no autodromo.

    vector<Carro*> carros;
    vector<Piloto*> pilotos;
public: 
    DGV(){};
    DGV(DGV&);//cria copia

    void carrega_carros(string path);
    void carrega_pilotos(string path);

    void p_listacarros();           //Print lista carros

	void add_carro(Carro* dados) { carros.push_back(dados); };
	void add_piloto(Piloto* dados) { pilotos.push_back(dados); };

    void apaga_carro(char caracter_Carro = '?');
    void apaga_piloto(string nome);

    bool acidente(char carro);

    void associa_piloto(char letra_carro, string nome_p);
    void sair_carro(char letra_carro);

    void percorre_vetores(string vetor, int iteracoes);

    int encontra_c(char char_carro);
    int encontra_p(string nome_piloto);

    void carrega_carro(char, float);

    char get_last_char();

    bool verifica_nome_existe(string);

	bool verifica_piloto_n_c(int i);

	int get_size_v_carros() { return this->carros.size(); };
	int get_size_v_pilotos() { return this->pilotos.size(); };

    void tira_todos_do_carro();

	Carro* get_carro_men(int i) { return carros[i]; };
	~DGV();

    void mostra_garagem(int, int);
    void mostra_pontuacao();
};