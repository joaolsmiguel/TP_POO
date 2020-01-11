#include "Carro.h"

Carro::Carro(string path, int n_linhas, int n_le, char caracter_in){
	if (n_linhas>0){
		string linha;
		ifstream ficheiro;

		ficheiro.open(path);
		if (n_le == 0){
			getline(ficheiro, linha);
		}else{
			for (int i = 0; i <= n_le; i++)
			{
				getline(ficheiro, linha);
			}
		}

		istringstream iss(linha);
        iss >> vel_max;
		iss >> capacidade;
		iss >> cap_maxima;
		
		iss >> marca;
		iss >> modelo;
		caracter_carro = caracter_in;
		ficheiro.close();
	}
}

Carro::Carro(string marca, int vel_max, int cap_max, string modelo, char caracter){				//DEFAULTS APENAS SE COLOCA NOS .H
	this->marca = marca;
	this->vel_max = vel_max;
	this->cap_maxima = cap_max;
	this->modelo = modelo;
	this->caracter_carro = caracter;
}

void Carro::mostra_carro(int i) const{
	if (tem_piloto() == true){
		cout << i+1 << " - Carro: " << marca << " Modelo: " << modelo << " Identificador: " << caracter_carro << ",\n Associado ao Piloto: " << p_piloto->get_nome() << endl;
		cout << endl;
	}else{
		cout << i+1 << " - Carro: " << marca << " Modelo: " << modelo << " Identificador: " << caracter_carro << endl;
	}
}

bool Carro::tem_piloto() const{
	if (this->p_piloto != NULL){
		return true;
	}else{
		return false;
	}
}

void Carro::sai_do_carro(){
	if (p_piloto == NULL){
		logs('w', "o carro nao tem nenhum piloto associado");
		cout << "o carro nao tem nenhum piloto associado" << endl;
	}else{
		cout << "Piloto " << p_piloto->get_nome() << " saiu do carro " << caracter_carro << endl;
		this->p_piloto->muda_associado(false);
		this->p_piloto = NULL;
		ocupado = false;
	}
}

void Carro::muda_velocidade(int nova_vel){
	if (nova_vel < vel_max && nova_vel >= 0){
		if (nova_vel > vel_max){
			cout << "Definiu uma velocidade maior que a maxima\npretende acelerar até ao limite? (s / n)" << endl;
			string op;
			getline(cin, op);
			if(op == "s" || op == "S"){
				velocidade = vel_max;
			}
		}else{
			velocidade = nova_vel;
			consome(velocidade);
		}
	}else if (nova_vel < 0) {
		velocidade = 0;
	}
}

void Carro::muda_danificado(bool valor){
	if (valor == true){
		danificado = true;
		velocidade = 0;
		vel_max = 0;//ver
	}
}

void Carro::consome(int velocidade){
	if (capacidade > 0){
		float consumir = velocidade * 0.1;
		capacidade = capacidade - consumir;
		if (capacidade <= 0){
			capacidade = 0;
		}
	}
}
void Carro::carrega_bateria(float mah){
	if (velocidade == 0){
		if (mah == 0) {
			mah = 10;
		}
		if (mah > 0){
			if ((capacidade + mah) >= cap_maxima){
				capacidade = cap_maxima;
			}else{
				capacidade = capacidade + mah;
			}
		}
	}else{
		logs('w', "O carro nao esta parado, nao pode carregar");
	}
}