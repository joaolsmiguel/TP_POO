#pragma once

#include "includes.h"
/*
#include "Piloto.h"
#include "Crazy.h"
#include "Rapido.h"
#include "Surpresa.h"
*/

using namespace std;

class DGV;
class Campeonato;


//Estrutura para guardar lista comandos e n_argumentos
struct struct_comandos{
    string comando;
    int args;
};

struct v_dgvs{
    DGV* dgv;
    string nome;
};

class Configs{
	DGV *dgv;
    Campeonato *campeonato;

    vector<string> help;//vetor ajuda com comandos
    vector<struct_comandos> v_comandos;  //Lista todos os comandos
    vector<string> v_cmd;       //Comando introduzido
    bool comecou_campeonato, sair;

    vector<v_dgvs> backup_dgv;
public:
    vector<string> v_logs;


    Configs();
    void configura();

    bool modo1_config();
    vector<struct_comandos> lista_comandos(string path);
    vector<string> divide_cmd(string cmd);
    bool verifica_cmd(string cmd);
    void comandos();
    bool verifica_args(int args, string cmd);
    ~Configs();

    vector<struct_comandos> return_comandos() const {return v_comandos;};
};

bool verifica_ficheiro(string path);
int get_linhas(string path);

void logs(char, string = "");