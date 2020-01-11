#include "DGV.h"

void DGV::carrega_carros(string path){
    int n_linhas = get_linhas(path);

    for (int i = 0; i < n_linhas; i++)
    {
        char letra, letra_inicio = 'a';
        if (i <= 25){
            letra =static_cast<char>(letra_inicio + i);
            carros.push_back(new Carro(path, n_linhas, i, letra));
        }else{
            carros.push_back(new Carro(path, n_linhas, i, '?'));
        }
    }
}

void DGV::carrega_pilotos(string path){
    int n_linhas = get_linhas(path);
    string linha, tipo, nome;
    ifstream ficheiro;
    ficheiro.open(path);

    for (int i = 0; i < n_linhas; i++)
    {
        getline(ficheiro, linha);

        istringstream iss(linha);
		iss >> tipo;
        iss >> nome;
        if (!verifica_nome_existe(nome)){
            if (tipo == "crazy"){
                pilotos.push_back(new Crazy(nome, tipo));
            }else if(tipo == "rapido"){
                pilotos.push_back(new Rapido(nome, tipo));
            }else if(tipo == "surpresa"){
                pilotos.push_back(new Surpresa(nome, tipo));
            }
        }else{
            logs('w', "O nome do piloto ja se encontra registado");
        }
    }
    ficheiro.close();
}

void DGV::p_listacarros(){
    int n_carros = carros.size();
    cout << endl;
    for (int i = 0; i < n_carros; i++)
    {
        carros[i]->mostra_carro(i);
    }
    cout << endl;
}

char DGV::get_last_char(){
    return carros[carros.size()-1]->get_char();
}

void DGV::apaga_carro(char caracter_carro){
    int tam_caros = carros.size();
    bool encontra = false;
    int i = 0;

    while (encontra == false){
        if (carros[i]->get_char() == caracter_carro){
            encontra = true;
            delete carros[i];
            carros.erase(carros.begin() + i);
        }
        i++;
    }

    if (encontra == false){
        cout << "Carro nao encontrado!" << endl;
    }
}

void DGV::apaga_piloto(string nome){
    int tam_pilotos = pilotos.size();
    bool encontra = false;
    int i = 0;

    while (encontra == false){
        if (pilotos[i]->get_nome() == nome){
            encontra = true;
            delete pilotos[i];
            pilotos.erase(pilotos.begin() + i);
        }
        i++;
    }

    if (encontra == false){
        cout << "Piloto nao encontrado!" << endl;
    }
}

bool DGV::acidente(char carro){
    bool encontra = false;
    int i = 0;

    while (encontra == false){
        if (carros[i]->get_char() == carro){
            encontra = true;
            if (carros[i]->get_danificado() == false){
                carros[i]->muda_danificado(true);
				return true;
            }else{
                cout << "Carro já se encontra danificado!" << endl;
				return true;
            }
        }
        i++;
    }
	return false;
}

int DGV::encontra_c(char char_carro){
    bool encontra = false;
    int i = 0;
    
    while (encontra == false){
        if(carros[i]->get_char() == char_carro){
            return i;
        }
        i++;
    }
    cout << "Carro nao existe" << endl;
    return -1;
}

int DGV::encontra_p(string nome_piloto){
    bool encontra = false;
    int i = 0;

    while (encontra == false){
        if (pilotos[i]->get_nome() == nome_piloto){
            return i;
        }
        i++;
    }
    cout << "Piloto nao Existe" << endl;
    return -1;
}

void DGV::associa_piloto(char letra_carro, string nome_p){
    if (carros.size() == 0){
        //log
        cout << "nao existem carros registados" << endl;
    }else{
        if (encontra_c(letra_carro) != -1 && encontra_p(nome_p) != -1){
            int c = encontra_c(letra_carro);
            int p = encontra_p(nome_p);

            if (pilotos[p]->get_associado() != true && carros[c]->get_opucado() != true){
                pilotos[p]->muda_associado(true);
                carros[c]->muda_ocupado(true);
                carros[c]->associa_piloto(pilotos[p]);
                cout << "Piloto: " << nome_p << " entrou no carro: " << letra_carro << endl;
            }else{
                if (pilotos[p]->get_associado() == true){
                    cout << "Piloto ja se encontra associado" << endl;
                }else if (carros[c]->get_opucado() == true){
                    cout << "Carro ja se encontra ocupado" << endl;
                }
            }
        }
    }
}

void DGV::tira_todos_do_carro(){
    for (int i = 0; i < carros.size(); i++){
        carros[i]->sai_do_carro();
    }
    Consola::clrscr();
}

void DGV::sair_carro(char letra_carro){
    if (encontra_c(letra_carro) != -1){
        carros[encontra_c(letra_carro)]->sai_do_carro();
    }
}

bool DGV::verifica_piloto_n_c(int i){
    return carros[i]->tem_piloto();
}

void DGV::percorre_vetores(string vetor, int iteracoes){
    if (vetor != ""){
        if (vetor == "c"){
			if (iteracoes == 0) {
				carros[iteracoes]->mostra_carro(iteracoes);
			}
            for (int i = 0; i < iteracoes; i++){
                carros[i]->mostra_carro(i);
            }
        }else if (vetor == "p"){
			if (iteracoes == 0) {
				carros[iteracoes]->mostra_carro(iteracoes);
			}
            
            for (int i = 0; i < iteracoes; i++)
            {
                pilotos[i]->mostra_pilotos(i);
            }
        }
    }
}

DGV::~DGV(){
    for (int i = 0; i < carros.size(); i++){
        delete carros[i];
    }
    carros.clear();

    for (int i = 0; i < pilotos.size(); i++){
        delete pilotos[i];
    }
    pilotos.clear();
}

DGV::DGV(DGV& copia_dgv){
    for (int i = 0; i < copia_dgv.get_size_v_carros(); i++)
    {
        carros.push_back( copia_dgv.get_carro_men(i));
    }
    
    copy(carros.begin(), carros.end(), back_inserter(copia_dgv.carros));
    copy(pilotos.begin(), pilotos.end(), back_inserter(copia_dgv.pilotos));
    //copia_dgv.pilotos = pilotos;
    obj_carro = nullptr;
}

bool DGV::verifica_nome_existe(string nome){
    for (int i = 0; i < pilotos.size(); i++){
        if (pilotos[i]->get_nome() == nome){
            return true;
        }
    }
    return false;
}


void DGV::mostra_garagem(int x, int y){
    int i, j = 0;

    Consola::gotoxy(x, y);
    cout << "-- Garagem ------------------" << endl;
    for (i = 0; i < carros.size(); i++){
        if (carros[i]->get_opucado() != true && carros[i]->get_danificado() != true){
            Consola::gotoxy(x, y + (j + 1));
            cout << "| " << carros[i]->get_char() << " " << carros[i]->get_marca() << " - ";
            cout << carros[i]->get_capacidade() << " mah";

            Consola::gotoxy(x + 28, y + (j + 1));
            if (i != (carros.size() - 1)){
                cout << "|";
            }
            j++;
        }
    }
    Consola::gotoxy(x, y + j);
    cout << "-----------------------------";
    cout << "\n" << endl;
}


void DGV::carrega_carro(char caracter, float mha){
    int encontra = encontra_c(caracter);
    if (encontra != -1){
        if (carros[encontra]->get_velocidade() > 0){
            cout << "pare o carro para o carregar" << endl;
        }else{
            carros[encontra]->carrega_bateria(mha);
        }
    }
}

void DGV::mostra_pontuacao(){
    Consola::clrscr();
    if (pilotos.size() > 0){
        cout << "Pontoacao de cada piloto" << endl;
        for (int i = 0; i < pilotos.size(); i++)
        {
            cout << "Nome: " << pilotos[i]->get_nome();
            cout << " - pontos: " << pilotos[i]->get_pontos();
            cout << endl;
        }
    }
    cout << endl;
}