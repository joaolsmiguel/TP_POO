#include <iostream>
#include "includes.h"

//FICHEIRO help.txt SERVE DE APOIO PARA QUANDO SE COLOCA ARGUMENTOS A +/- NUM COMANDO (MUDAR NO VERIFICA_ARGS)



using namespace std;

vector<string> v_logs; //GLOBAL VAR

int main()
{
	//Consola::setTextColor(Consola::BRANCO);
    Configs *configuracoes = new Configs();

    configuracoes->configura();

    delete configuracoes;

    return 0;
}