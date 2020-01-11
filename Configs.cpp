#include "Configs.h"

extern vector<string> v_logs;

using namespace std;

class Piloto;
class Crazy;
class Rapido;
class Surpresa;
class Carro;

Configs::~Configs(){
    delete dgv;
    delete campeonato;
}

Configs::Configs(){
    comecou_campeonato = false;
    sair = false;

	this->dgv = new DGV();
    this->campeonato = new Campeonato(dgv);
}

void Configs::configura(){
    v_comandos = lista_comandos("v_comandos.txt");

    {
        if (verifica_ficheiro("help.txt") != false){
            ifstream ficheiro;
            string linha;

            ficheiro.open("help.txt");
            while (getline(ficheiro, linha)){
                help.push_back(linha);
            }
            ficheiro.close();
        }
    }

    string cmd;
    int primeiro_atualiza = 0;
    while (sair == false)
    {
        if (comecou_campeonato == true){
            if(campeonato->verifica_condicoes_campeonato() == true){
                if (primeiro_atualiza == 0){
                    primeiro_atualiza++;
                }else if(campeonato->verifica_todos_acabaram_corrida() == true){
                    /*      MUDAR
                    string op;
                    cout << "Deseja terminar o campeonato? ('s' para terminar)" << endl;
                    getline(cin, op);
                    if (op == "s" || op == "S"){
                        comecou_campeonato = false;
                    }
                    */
                   comecou_campeonato = false;
                }else{
                    campeonato->atualiza_campeonato();
                    
                    POINT p;
                    GetCursorPos(&p);
                    Consola::gotoxy(p.x, p.y);
                }
            }else{
				comecou_campeonato = false;
                cout << "Impossivel acabar o campeonato!" << endl;
            }
        }
        
        cout << "Introduza um comando: ";
        
		getline(cin, cmd);

		
		
		if(cmd != ""){
            if (verifica_cmd(cmd) == true){
                v_cmd = divide_cmd(cmd);
                comandos();
            }else{
                if (comecou_campeonato != true){
                    cout << "Comando nao existe!" << endl;
                }
            }
        }else{
            if (comecou_campeonato != true){
                cout << "Comando vazio" << endl;
            }
        }
    }
    
}

vector<struct_comandos> Configs::lista_comandos(string path){        //Cria lista de comandos ('help.txt')
    if (verifica_ficheiro(path)!=false){
        ifstream ficheiro;
        vector<struct_comandos> result;
        string linha;

        string cmd;
        int arg;

        

        ficheiro.open(path);
        while (getline(ficheiro, linha)){
            istringstream iss(linha);
            iss >> cmd;
            iss >> arg;
            struct_comandos estrutura = {cmd, arg};
            result.push_back(estrutura);
        }
        ficheiro.close();
        return result;
    }
}

bool Configs::verifica_cmd(string cmd){
    vector<string> args = divide_cmd(cmd);
    
    int tam_comandos = v_comandos.size(); //Quantos comandos existem no projeto
    for (int i = 0; i < tam_comandos; i++){
        if (args[0] == v_comandos[i].comando){
            return true;
        }
    }
	return false;
}

vector<string> Configs::divide_cmd(string cmd){
    vector<string> resultado;
    istringstream iss(cmd);
    string arg;

    while (getline(iss, arg, ' ')) {
        resultado.push_back(arg);
    }

    return resultado;
}

bool Configs::verifica_args(int args, string cmd){       //n = args deve ter pelo menos
    int tam_comandos = v_comandos.size();
    args--;

    for (int i = 0; i < tam_comandos; i++)
    {
        if (v_comandos[i].comando == cmd){
            if (args == v_comandos[i].args){
                return true;
            }else{
                if(args < v_comandos[i].args){
                    cout << "Faltam Argumentos" << endl;
                    return false;
                }
                return true;
            }
        }
    }
	return false;
}

void Configs::comandos(){
    if (v_cmd[0] == "sair"){
        sair = true;
    }else if(v_cmd[0] == "carregaC"){              //done             //carrega Carros
        if (comecou_campeonato == false){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                if (verifica_ficheiro(v_cmd[1])){
                    dgv->carrega_carros(v_cmd[1]);
                    logs('w', "carregaC utilizado com sucesso");
                }
            }
        }else{
            logs('w', "Campeonato ja comecou!");
            cout << "Campeonato ja comecou!" << endl;
        }
    }else if(v_cmd[0] == "carregaP"){              //done             //carrega Pilotos
        if (comecou_campeonato == false){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                if (verifica_ficheiro(v_cmd[1])){            
                    dgv->carrega_pilotos(v_cmd[1]);
                }
            }
        }else{
            logs('w', "Campeonato ja comecou!");
            cout << "Campeonato ja comecou!" << endl;
        }
    }else if(v_cmd[0] == "carregaA"){              //done             //carrega Autodromos
        if (comecou_campeonato == false){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                if (verifica_ficheiro(v_cmd[1])){            
                    campeonato->carrega_autodromos(v_cmd[1]);//Alterar da DGV para Campeonato
                }
            }
        }else{
            logs('w', "Campeonato ja comecou!");
            cout << "Campeonato ja comecou!" << endl;
        }
    }else if (v_cmd[0] == "cria"){                 //done             //Cria
        if (comecou_campeonato == false){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                if (v_cmd[1] == "p"){
                    if (dgv->verifica_nome_existe(v_cmd[3]) != true){
                        if (v_cmd[2] == "crazy"){
                            dgv->add_piloto(new Crazy(v_cmd[3], v_cmd[2]));
                        }else if (v_cmd[2] == "rapido"){
                            dgv->add_piloto(new Rapido(v_cmd[3], v_cmd[2]));
                        }else if (v_cmd[2] == "surpresa"){
                            dgv->add_piloto(new Surpresa(v_cmd[3], v_cmd[2]));
                        }else{
                            cout << "Formato Incorreto" << endl;
                        }
                    }else{
                        cout << "O nome do piloto ja existe registado" << endl;
                        logs('w', "O nome do piloto ja existe");
                    }
                }else if (v_cmd[1] == "c"){
                    if (v_cmd[2] != "" && v_cmd[3] != ""){//2 = marca 3 = velocidademax
                        char caracter = static_cast<char>(dgv->get_last_char()+1);			//LETRA DEPOIS DO ULTIMO CARRO NO VETOR
                        if ((v_cmd.size()-1) == 3){
                            dgv->add_carro(new Carro(v_cmd[2], stoi(v_cmd[3]), 0, "", caracter));
                        }else if (v_cmd.size() > 3){
                            dgv->add_carro(new Carro(v_cmd[2], stoi(v_cmd[3]), 0, v_cmd[4], caracter));
                        }
                    }else{
                        cout << "Formato Incorreto" << endl;
                    }
                }else if (v_cmd[1] == "a"){
                    if (v_cmd.size()<4){
                        cout << "Faltam Argumentos" << endl;
                    }else{//nome, tamanho em km, n_max_carros
                        if (campeonato->verifica_autodromo_nome_unico(v_cmd[2]) != true){
                            campeonato->add_autodromo(new Autodromo(v_cmd[2], stof(v_cmd[3]), stoi(v_cmd[4])));
                        }else{
                            cout << "nome ja se encontra em uso" << endl;
                            logs('w', "nome ja se encontra em uso");
                        }
                    }
                }else{
                    cout << "Tipo Incorreto" << endl;
                }
            }
        }else{
            logs('w', "Campeonato ja comecou!");
            cout << "Campeonato ja comecou!" << endl;
        }
    }else if(v_cmd[0] == "apaga"){                 //done             //APAGA
        if (comecou_campeonato == false){
            if (v_cmd[1] == "c"){                                  //APAGA CARRO
                if (v_cmd[2] == "?"){
                    string op;
                    cout << "o programa ira apagar o primeiro carro com caracter '?' \n Pretende continuar? (sim / nao): " << endl;
                    getline(cin, op);
                    if (op == "sim"){
                        dgv->apaga_carro('?');
                    }
                }else{
                    dgv->apaga_carro(v_cmd[2][0]);
                }
            }else if (v_cmd[1] == "p"){                         //APAGA PILOTO
                dgv->apaga_piloto(v_cmd[2]);
            }else if (v_cmd[1] == "a"){                         //APAGA AUTODROMO
                campeonato->apaga_autodromo(v_cmd[2]);
            }else{
                cout << "Tipo Incorreto" << endl;
            }
        }else{
            logs('w', "Campeonato ja comecou!");
            cout << "Campeonato ja comecou!" << endl;
        }
    }else if (v_cmd[0] == "entranocarro"){         //done             //Entranocarro
        if (comecou_campeonato == false){
            dgv->associa_piloto(v_cmd[1][0], v_cmd[2]);
        }else{
            logs('w', "Campeonato ja comecou!");
            cout << "Campeonato ja comecou!" << endl;
        }
    }else if(v_cmd[0] == "saidocarro"){            //done             //Saidocarro
        if (comecou_campeonato == false){
            if (dgv->get_size_v_carros() != 0){
                dgv->sair_carro(v_cmd[1][0]);
            }
		}else {
			logs('w', "Campeonato ja comecou!");
			cout << "Campeonato ja comecou!" << endl;
		}
    }else if(v_cmd[0] == "lista"){                 //done            //Lista
        if (comecou_campeonato == false){

            int n_c = this->dgv->get_size_v_carros();
            int n_p = this->dgv->get_size_v_pilotos();
            int n_a = this->campeonato->get_size_autodromos();

            if (n_c > 0){
                cout << "\nCarros:" << endl;
                this->dgv->percorre_vetores("c", n_c);
				cout << endl;
            }else{
                cout << "\nAinda nao adicionou Carros!\n" << endl;
            }
            
            if (n_p > 0){
                cout << "\nPilotos: " << endl;
                this->dgv->percorre_vetores("p", n_p);
				cout << endl;
            }else{
                cout << "Ainda nao adicionou Pilotos!\n" << endl;
            }
            
            if (n_a > 0){
                cout << "\nAutodromos: " << endl;
                this->campeonato->percorre_vetores("a", n_a);
				cout << endl;
            }else{
                cout << "Ainda nao adicionou Autodromos!\n" << endl;
            }
            /*BUG
            cout << "Carros com Piloto:"<< endl;
            for (int i = 0; i < dgv->get_size_v_carros(); i++)
            {
                if (dgv->verifica_piloto_n_c(i) == true){
                    dgv->percorre_vetores("c",i);
                }
            }
            */
            cout << endl;
        }else{
            logs('w', "Campeonato ja comecou!");
            cout << "Campeonato ja comecou!" << endl;
        }
    }else if (v_cmd[0] == "savedgv"){                       //saveDGV FAZER
        if (comecou_campeonato != true){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                DGV copia_dgv = *dgv;
                //memcpy(&copia_dgv, &dgv, sizeof(dgv));
                v_dgvs guarda_dgv = {&copia_dgv, v_cmd[1]};
                backup_dgv.push_back(guarda_dgv);
            }
        }else{
            cout << "campeonato ja comecou!!" << endl;
        }
    }else if (v_cmd[0] == "loaddgv"){                           //loadDGV FAZER
        if (comecou_campeonato != true){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                if (backup_dgv.size() == 0){
                    cout << "Nao existem DGV guardadas" << endl;
                }else{
                    for (int i = 0; i < backup_dgv.size(); i++){
                        if (v_cmd[1] == backup_dgv[i].nome){
                            dgv = backup_dgv[i].dgv;
                        }else{
                            logs('w', "nao existe backup da dgv com esse nome");
                            cout << "nao existe backup da dgv com esse nome" << endl;
                        }
                    }
                }
            }
        }else{
            cout << "campeonato ja comecou!!" << endl;
        }
    }else if (v_cmd[0] == "deldgv"){                            //delDGV FAZER
        if (comecou_campeonato != true){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                if (backup_dgv.size() == 0){
                    cout << "Nao existem DGV guardadas" << endl;
                }else{
                    for (int i = 0; i < backup_dgv.size(); i++){
                        if (v_cmd[1] == backup_dgv[i].nome){
                            backup_dgv[i].dgv->~DGV();
                        }else{
                            logs('w', "nao existe backup da dgv com esse nome");
                            cout << "nao existe backup da dgv com esse nome" << endl;
                        }
                    }
                }
            }
        }else{
            cout << "O campeonato ja comecou!!" << endl;
        }
    }else if (v_cmd[0] == "campeonato"){                        //Campeonato
        if (v_cmd.size() >= 2){
            if(modo1_config() == true){
                if (campeonato->configura_campeonato(v_cmd) == true){
                    comecou_campeonato = true;
                    campeonato->comeca_corridas(0);
                }
            }
        }
    }else if(v_cmd[0] == "listacarros"){           //notdone +/-             //listacarros
        if (verifica_args((int)v_cmd.size(), v_cmd[0])){
            dgv->p_listacarros();
            Consola::getch();
        }
    }else if (v_cmd[0] == "carregabat"){                        //carregabat <letraC> <mAH>
        if (verifica_args((int)v_cmd.size(), v_cmd[0])){
            dgv->carrega_carro(v_cmd[1][0], stof(v_cmd[2]));
        }
    }else if(v_cmd[0] == "carregatudo"){                       //carregatudo
        campeonato->carrega_bat();
    }else if (v_cmd[0] == "corrida"){                           //corrida
        if (comecou_campeonato == false){
            if (modo1_config() == true){
                campeonato->comeca_corridas(campeonato->get_n_corrida()+1);
            }
        }
    }else if(v_cmd[0] == "acidente"){              //done             //ACIDENTE
        if(dgv->acidente(v_cmd[1][0])){
            cout << "Carro danificado com Sucesso!" << endl;
        }else{
            cout << "Erro!" << endl;
        }
    }else if (v_cmd[0] == "stop"){                              //stop
        if (comecou_campeonato == true){
            if (verifica_args((int)v_cmd.size(), v_cmd[0])){
                campeonato->stop(v_cmd[1][0]);
            }
        }
        cout << "parar ir desacelerando";
    }else if (v_cmd[0] == "destroi"){              //done             //DESTROI  //Verificar se é isto que se pretende visto ser igual
        if (verifica_args((int)v_cmd.size(), v_cmd[0])){
            if (comecou_campeonato == true){
                campeonato->destroi_carro(v_cmd[1][0]);
            }else{
                logs('w', "O campeonato ainda nao comecou!");
                cout << "O campeonato ainda nao comecou!" << endl;
            }
        }
    }else if (v_cmd[0] == "passatempo"){           //FAZER             //Passatempo
        cout << "faz passar x segundos do tempo de simulacao";
        if (v_cmd.size() > 1){
            campeonato->passatempo(stoi(v_cmd[1]));

		}
        //sleep_for(milliseconds(500));
    }else if (v_cmd[0] == "log"){
        logs('r', "");
    }else if (v_cmd[0] == "help"){
        if (v_cmd.size() > 1){
            if (v_cmd[1] != ""){
                for (int i = 0; i < help.size(); i++){
                    if (help[i].find(v_cmd[1]) != std::string::npos){
                        cout << help[i] << endl;
                        break;
                    }
                }
            }
        }else{
            for (int i = 0; i < help.size(); i++){
                cout << help[i] << endl;
            }
        }
    }else if (v_cmd[0] == "pontuacao"){
        dgv->mostra_pontuacao();
    }
}


bool Configs::modo1_config(){
    int n_carros = dgv->get_size_v_carros();
    if (n_carros >= 2 && dgv->get_size_v_pilotos() >= 2 && campeonato->get_size_autodromos() >= 1){
        int pilotos_no_carro = 0, i = 0;
        while (i < n_carros){
            if (dgv->verifica_piloto_n_c(i) == true){
                pilotos_no_carro++;
                //campeonato->get_carros_e_pilotos(dgv->get_carro_men(i));
                campeonato->coloca_na_garagem(dgv->get_carro_men(i));
            }
            i++;
        }

        if (pilotos_no_carro < 2){
            //vetor log
            cout << "Precisa de associar pilotos aos carros" << endl;
            campeonato->apaga_garagem();
            return false;
        }else if (pilotos_no_carro == n_carros){
            return true;
        }else if(pilotos_no_carro < n_carros && pilotos_no_carro >= 2){
            return true;
        }
    }else{
        cout << "Estao configuracoes em falta para poder avancar!" << endl;
    }
    return false;
}

bool verifica_ficheiro(string path){
    ifstream ficheiro;
    ficheiro.open(path);
    if (!ficheiro.is_open()){
        ficheiro.close();
        //log
        cout << "Erro ao abrir ficheiro" << endl;
        return false;
    }else{
        ficheiro.close();
        return true;
    }
}

int get_linhas(string path){
    if (verifica_ficheiro(path) == true){
        string linha;
        ifstream ficheiro(path);
        int i = 0;
        while (getline(ficheiro, linha)) {
            i++;
        }
	    return i;
    }
	return 0;
}


void logs(char caracter, string frase){ // w ou r
    if (caracter == 'r'){//read
        if (v_logs.size() == 0){
            cout << "Ainda nao existem logs" << endl;
        }else{
            for (int i = 0; i < v_logs.size(); i++){
                cout << i+1 << " log: " << v_logs[i] << endl;
            }
        }
    }else if (caracter == 'w'){//write
        if (frase != ""){
            v_logs.push_back(frase);
        }
    }
}
