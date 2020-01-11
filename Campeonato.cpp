#include "Campeonato.h"

using namespace std;

void Campeonato::carrega_autodromos(string path){
    int n_linhas = get_linhas(path);
    ifstream ficheiro;
    string linha, nome;
    int max_carros;
    float comp;

    ficheiro.open(path);

    for (int i = 0; i < n_linhas; i++){
        getline(ficheiro, linha);
        istringstream iss(linha);
        iss >> max_carros;
        iss >> comp;
        iss >> nome;
        if (verifica_autodromo_nome_unico(nome) != true){
            autodromos.push_back(new Autodromo(nome, comp, max_carros));
        }
    }
    ficheiro.close();
}

void Campeonato::apaga_autodromo(string nome){
    int tam_autodromos = autodromos.size();
    bool encontra = false;
    int i = 0;

    while (encontra == false){
        if (autodromos[i]->get_nome() == nome){
            encontra = true;
            delete autodromos[i];
            autodromos.erase(autodromos.begin() + i);
        }
        i++;
    }

    if (encontra == false){
        cout << "Autodromo nao encontrado!" << endl;
    }
}

void Campeonato::percorre_vetores(string vetor, int iteracoes){
    if (vetor != ""){
        if (vetor == "a"){
            for (int i = 0; i < iteracoes; i++){
                autodromos[i]->mostra_autodromo(i);
            }
        }
    }
}

bool Campeonato::verifica_existe_autodromo(string nome){
    int n_autodromos = get_size_autodromos();
    for (int i = 0; i < n_autodromos; i++){
        if (autodromos[i]->get_nome() == nome){
            ordem_autodromos.push_back(autodromos[i]);
            return true;
        }
    }
    return false;
}

void Campeonato::desenha_carro(int i){
    Consola::gotoxy(v_corrida[i].pos_x, v_corrida[i].pos_y);
    Consola::setTextColor(Consola::VERMELHO);
    cout << ">";
    Consola::setTextColor(Consola::BRANCO);
}

void Campeonato::desenha_pista(int n_pistas){
    Consola::clrscr();
    //cout << " Autodromo: " << ordem_autodromos[n_corrida]->get_nome() << endl; era debug
    int x = 2, y= 1;
    for (int i = 0; i < n_pistas; i++){
        Consola::gotoxy(x,y);
        cout << "----------------------------------------------------------------------------------------------------";
		y++;

        Consola::gotoxy(x-1,y);
        cout << v_corrida[i].p_carro->get_char() << "|";//ocupa 2 posicoes de x

		if (v_corrida[i].pos_x == 0){
            v_corrida[i].pos_x=x+1;
            v_corrida[i].pos_y=y;
        }
        desenha_carro(i);

        Consola::gotoxy(101, y);
        cout << "|";

        if (v_corrida[i].corrida_terminada == true || v_corrida[i].pos_x == 100){
            cout << "Acabou";
        }

        y++;

        Consola::gotoxy(x,y);
        cout << "----------------------------------------------------------------------------------------------------";
        y++;
    }
    cout << endl;
    info_corrida();
    obj_dgv->mostra_garagem((100-30), (v_corrida[v_corrida.size() - 1].pos_y + 2));
}

int Campeonato::comeca_corridas(int n_corrida){//fazer
    if (verifica_todos_acabaram_corrida() == true){
        if (decorre_corrida == ""){
            decorre_corrida = ordem_autodromos[0]->get_nome();
        }else{
            if (ordem_autodromos.size() > n_corrida){
                this->n_corrida = n_corrida;
                decorre_corrida = ordem_autodromos[n_corrida]->get_nome();
            }else{
                logs('w', "Já nao existem mais autodromos para correr");
                cout << "Já nao existem mais autodromos para correr" << endl;
                return 0;
            }
        }

        v_corrida.clear();
        int cap_max = ordem_autodromos[this->n_corrida]->get_cap_max_pista();

        if (cap_max <= garagem.size()){
            for (int i = 0; i < cap_max; i++){
                get_carros_e_pilotos(garagem[i]);
            }
        }else if (garagem.size() <= cap_max){
            for (int i = 0; i < garagem.size(); i++){
                get_carros_e_pilotos(garagem[i]);
            }
        }else{
            logs('w', "erro");
        }

        int n_pistas = v_corrida.size();
        desenha_pista(n_pistas);
    }else{
        cout << "A corrida ainda esta a decorrer!!!" << endl;
    }
}

bool Campeonato::verifica_autodromo_nome_unico(string in_nome){
    for (int i = 0; i < get_size_autodromos(); i++){
        if (autodromos[i]->get_nome() == in_nome){
            return true;//ja existe
        }
    }
    return false;
}

void Campeonato::get_carros_e_pilotos(Carro* carro){
    pista estrutura = {carro->get_piloto(), carro};
    v_corrida.push_back(estrutura);

    if (carro->get_piloto()->get_tipo() == "crazy"){
        v_corrida[v_corrida.size()-1].comeca = rand() % 5 + 1;
    }
}

void Campeonato::anda_carro(){
    int size_autodromos = autodromos.size();

    float comp_pista = 0;
    int i = 0;

    for (int i = 0; i < ordem_autodromos.size(); i++)
    {
        if (decorre_corrida == ordem_autodromos[i]->get_nome()){
            comp_pista = ordem_autodromos[i]->get_comp_pista();
			break;
        }
    }


	//cout << "kjdgvbkdnj,v";//debug

    //teste velocidade
    //v_corrida[0].p_carro->muda_velocidade(100);
    //v_corrida[1].p_carro->muda_velocidade(50);

//BUG
	int size_v = v_corrida.size();
    for (int i = 0; i < v_corrida.size(); i++){
        if (v_corrida[i].corrida_terminada != true){
			v_corrida[i].p_piloto->acelera(v_corrida, i);
			if (v_corrida.size() != size_v) {
				i--;
			}else {
				v_corrida[i].segundo++;
			}
        }
    }
    

	vector<int> maior;

	for (int i = 0; i < v_corrida.size(); i++) {
		maior.push_back(v_corrida[i].metros_percorridos);
	}
	sort(maior.begin(), maior.end(), greater<int>());

    for (int i = 0; i < maior.size(); i++) {
		for (int j = 0; j < maior.size(); j++) {
			if (maior[i] == v_corrida[j].metros_percorridos) {
				v_corrida[i].posicao_corrida = j + 1;
				break;
			}
		}
	}
    

    

    for (int i = 0; i < v_corrida.size(); i++){
        //v_corrida[i].p_carro->muda_velocidade(100);
        if (v_corrida[i].pos_x != 100){
            int comp_m_pista = static_cast<int>(comp_pista*1000);
            v_corrida[i].metros_percorridos = v_corrida[i].metros_percorridos + v_corrida[i].p_carro->get_velocidade();
			
            float soma = ((float)v_corrida[i].metros_percorridos / (float)comp_m_pista)*100;
            //v_corrida[i].pos_x = v_corrida[i].pos_x + round(soma);
            v_corrida[i].pos_x = 3 + round(soma);

            if (v_corrida[i].pos_x >= 100){
                v_corrida[i].pos_x = 100;
                v_corrida[i].metros_percorridos = comp_m_pista;

				if (v_corrida[i].posicao_corrida == 1) {
					v_corrida[i].p_piloto->muda_pontos(10);
				}
				else if (v_corrida[i].posicao_corrida == 2) {
					v_corrida[i].p_piloto->muda_pontos(5);
				}
				else if (v_corrida[i].posicao_corrida == 3) {
					v_corrida[i].p_piloto->muda_pontos(2);
				}
            }
            
        }else{
            v_corrida[i].corrida_terminada = true;
        }
    }
}

bool Campeonato::verifica_todos_acabaram_corrida(){
    int n_acabaram = 0;

    int i = 0;
    while (i < v_corrida.size()){
        if (v_corrida[i].pos_x == 100){
            v_corrida[i].corrida_terminada = true;
        }

        if (v_corrida[i].corrida_terminada == true){
            n_acabaram++;
        }
        i++;
    }

    if (n_acabaram == i){
        vetor_corridas.push_back(v_corrida);
        return true;
    }
    
    return false;
}

void Campeonato::atualiza_campeonato(){
    if (verifica_todos_acabaram_corrida() == true){
        for (int i = 0; i < ordem_autodromos.size(); i++){
            if (ordem_autodromos[i]->get_nome() == decorre_corrida){
                if (ordem_autodromos.size() <= i+1){
                    break;//fazer
                    //verifica se quer sair de campeonato.
                }else{
                    decorre_corrida = ordem_autodromos[i+1]->get_nome();
                    desenha_pista(v_corrida.size());//NOTA IMPORTANTE: pq isto tem que ser alterado porque a struct corrida vai manter as posicoes e atriburos todos da corrida no autodromo anterior.
                    break;//Se eu alterar aqui os atributos da struct vou perder informacao da corrida no autodromo anterior.
                }
            }
        }
    }else{
        anda_carro();
        desenha_pista(v_corrida.size());
    }
}

void Campeonato::destroi_carro(char caracter){
    int n_carros = v_corrida.size();
    bool encontra = false;
    int i = 0;

    while (encontra == false){
        if (v_corrida[i].p_carro->get_char() == caracter){
            encontra = true;
            delete v_corrida[i].p_carro;
            v_corrida.erase(v_corrida.begin() + i);
        }
		i++;
    }

    if (encontra == false){
        cout << "Carro nao encontrado!" << endl;
    }
    
}

bool Campeonato::verifica_condicoes_campeonato(){
    if (v_corrida.size() < 2){
        Consola::clrscr();
        cout << "Apenas existe 1 carro em corrida!" << endl;
        return false;
    }
    return true;
}

void Campeonato::passatempo(int tempo){
    for (int i = 0; i < tempo; i++)
    {
        atualiza_campeonato();
    }
}

Campeonato::~Campeonato(){
    for (int i = 0; i < autodromos.size(); i++){
        delete autodromos[i];
    }
    autodromos.clear();
    ordem_autodromos.clear();
    vetor_corridas.clear();
    v_corrida.clear();
}

bool Campeonato::configura_campeonato(vector<string> v_cmd){
    int ver_autodromos = 0;
    for (int i = 1; i < v_cmd.size(); i++){
        if (verifica_existe_autodromo(v_cmd[i]) == true){
            ver_autodromos++;
        }
    }
    if (ver_autodromos == (v_cmd.size()-1)){//verifica o n de argumentos com o n de autodromos que realmente existem
        return true;
    }else{
        logs('w', "Verifique os nomes dos autodromos");
        cout << "Verifique os nomes dos autodromos" << endl;
        return false;
    }
    //v_corrida[0].p_carro->
}

void Campeonato::info_corrida(){
    cout << "Corrida no Autodromo " << ordem_autodromos[n_corrida]->get_nome() << " (" << ordem_autodromos[n_corrida]->get_comp_pista()*1000 << " m)" << endl;
    for (int i = 0; i < v_corrida.size(); i++){
        for (int j = 0; j < v_corrida.size(); j++){
            if (v_corrida[j].posicao_corrida == i+1){
                cout << v_corrida[j].posicao_corrida << ". ";
                cout << v_corrida[j].p_carro->get_char() << " " << v_corrida[j].p_carro->get_marca() << " / ";
                cout << v_corrida[j].p_piloto->get_nome() << " (" << v_corrida[j].p_piloto->get_tipo() << ") - ";
                //carrega(nao sei), bateria restante, posicao na pista, velocidade carro;
                cout << v_corrida[j].metros_percorridos << "m - " << v_corrida[j].p_carro->get_velocidade() << "m/s / ";
                cout << v_corrida[j].p_carro->get_capacidade() << " ma/h";
                if (v_corrida[j].p_carro->get_danificado() == true){
                    cout << " DANIFICADO";
                }
                cout << endl;
            }
        }
    }
    cout << endl;
}

void Campeonato::carrega_bat(){
    for (int i = 0; i < garagem.size(); i++){
        garagem[i]->carrega_bateria(garagem[i]->get_cap_max());
    }
}

void Campeonato::stop(char caracter){
    for (int i = 0; i < garagem.size(); i++){
        if (garagem[i]->get_char() == caracter){
            garagem[i]->muda_stop(true);
        }
    }
}