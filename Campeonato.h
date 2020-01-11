#pragma once

#include "includes.h"
//#include "Piloto.h"

using namespace std;

//SO PRO CASO DE PRECISAR

class Carro;
class Piloto;
class DGV;
class Autodromo;

struct pista{
    Piloto* p_piloto;
    Carro* p_carro;
    int pos_x = 0, pos_y = 0;// posicoes x e y para desenha;
    int metros_percorridos = 0;
    int posicao_corrida;
    bool corrida_terminada = false;
    int segundo = 0, comeca = 0;
};

//ideia de resolver problema desacrito em: campeonato.cpp ln:166
/*
struct struct_autodromos_corridas{
    vector<Autodromo*> ordem_autodromos;
    vector<struct_Corrida> corrida_no_autodromo;
};
*/

class Campeonato{
    DGV* obj_dgv;

    vector<Autodromo*> autodromos;
    vector<pista> v_corrida;     //vetor da estrutura corrida "PISTA"
    
    vector<vector<pista>> vetor_corridas;//ex: [0][1] corresponde a primeira corrida 2 piloto
    vector<Carro*> garagem;
    
    vector<Autodromo*> ordem_autodromos;

    string decorre_corrida;

    int n_corrida = 0;
public:
	Campeonato(DGV* dgv) { this->obj_dgv = dgv; };

    int comeca_corridas(int);

    bool verifica_condicoes_campeonato();

    void carrega_autodromos(string path);
    void add_autodromo(Autodromo* dados) { autodromos.push_back(dados); };
    int get_size_autodromos() { return this->autodromos.size(); };
    
    void apaga_garagem(){garagem.clear();};
    void apaga_autodromo(string nome);

    bool verifica_existe_autodromo(string nome);

    void percorre_vetores(string vetor, int iteracoes);

    void atualiza_campeonato();
    bool configura_campeonato(vector<string> v_cmd);
    void corrida(int);

    int get_n_corrida(){return this->n_corrida;}; 

    void coloca_na_garagem(Carro* carro){garagem.push_back(carro);};
    void get_carros_e_pilotos(Carro*);
    void desenha_pista(int n_pistas);//done
    void desenha_carro(int);//">"

    void anda_carro();

    bool verifica_autodromo_nome_unico(string);//true = existir igual

    bool verifica_todos_acabaram_corrida();

    void stop(char);
    void destroi_carro(char);

    void passatempo(int);

    void info_corrida();
    void carrega_bat();

    int get_size_garagem(){return this->garagem.size();};

    ~Campeonato();
};