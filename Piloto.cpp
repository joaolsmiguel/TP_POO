#include "Piloto.h"

Piloto::Piloto(string in_nome, string in_tipo){
    nome = in_nome;
    tipo = in_tipo;
    string cria = "Criado piloto: " + nome + "do tipo: " + tipo;
    logs('w', cria);
}

void Piloto::mostra_pilotos(int i) const{
    if (this->associado == true){
        cout << i+1 << " Piloto: " << nome << " Tipo: " << tipo << " OCUPADO" << endl;
    }else{
        cout << i+1 << " Piloto: " << nome << " Tipo: " << tipo << endl;
    }
}

void Crazy::acelera(vector<pista>& v_corrida, int iteracao){
    if (v_corrida[iteracao].p_carro->get_stop() == true || v_corrida[iteracao].p_carro->get_sinal_emergencia() == true){
        if (v_corrida[iteracao].p_carro->get_velocidade() > 0){
            v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() - 1);
        }else{
            v_corrida[iteracao].p_carro->sai_do_carro();
            v_corrida[iteracao].corrida_terminada = true;
            v_corrida.erase(v_corrida.begin() + iteracao);
        }
    }else{
        //COMECA
        if (v_corrida[iteracao].p_carro->get_capacidade() > 0){
            if (v_corrida[iteracao].corrida_terminada != true){
                if (v_corrida[iteracao].segundo == v_corrida[iteracao].comeca){
                    v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 1);//alterar
                }else if (v_corrida[iteracao].segundo > v_corrida[iteracao].comeca) {//Durante
                    if (v_corrida[iteracao].posicao_corrida > 1 && v_corrida[iteracao].posicao_corrida < v_corrida.size()) {
                        v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 2);//acelera 2m/s
                    }
                    else {
                        v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 1);//alterar pra ir diminnuindo
                    }

                    //5% prob estragar carros dele e dos outros
                    int random = rand() % 100+1;
                    if (random > 0 && random <= 5){
                        if (v_corrida[iteracao].posicao_corrida < v_corrida.size()){
                            for (int i = 0; i < v_corrida.size(); i++){
                                if (v_corrida[i].posicao_corrida == v_corrida[iteracao].posicao_corrida + 1){
                                    v_corrida[i].p_carro->muda_danificado(true);
                                    v_corrida[i].corrida_terminada = true;
                                }
                            }
                        }else{
                            v_corrida[iteracao].p_carro->muda_danificado(true);
                            v_corrida[iteracao].corrida_terminada = true;
                        }
                    }
                }
            }
        }else{
            v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() - 1);
        }
    }
}

void Rapido::acelera(vector<pista>& v_corrida, int iteracao){
    if (v_corrida[iteracao].p_carro->get_stop() == true || v_corrida[iteracao].p_carro->get_sinal_emergencia() == true){
        if (v_corrida[iteracao].p_carro->get_velocidade() > 0){
            v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() - 1);
        }else{
            v_corrida[iteracao].p_carro->sai_do_carro();
            v_corrida[iteracao].corrida_terminada = true;
            v_corrida.erase(v_corrida.begin() + iteracao);
        }
    }else{
        if (v_corrida[iteracao].p_carro->get_capacidade() > 0){
            if ((v_corrida[iteracao].p_carro->get_cap_max() / 2) == v_corrida[iteracao].p_carro->get_capacidade()){
                if (v_corrida[iteracao].segundo % 3 == 1){
                    v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 1);
                }
            }else{
                v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 1);
            }
    //MUDAR
            //probablidade de ligar sinal de emergencia
            float divisao = (v_corrida[iteracao].segundo + 10)/10;
            if (divisao == round(divisao)){
                int prob = rand() % 100 + 1;
                if (prob >= 1 && prob <= 10){
                    v_corrida[iteracao].p_carro->carrega_emergencia(true);
                }
            } 
        }else{
            v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() - 1);
        }
    }
}


void Surpresa::acelera(vector<pista>& v_corrida, int iteracao){
    if (v_corrida[iteracao].p_carro->get_stop() == true || v_corrida[iteracao].p_carro->get_sinal_emergencia() == true){
        if (v_corrida[iteracao].p_carro->get_velocidade() > 0){
            v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() - 1);
        }else{
            v_corrida[iteracao].p_carro->sai_do_carro();
            v_corrida[iteracao].corrida_terminada = true;
            
            v_corrida.erase(v_corrida.begin() + iteracao);
            
            
        }
    }else{
        //verifica carregamento
        if (v_corrida[iteracao].p_carro->get_capacidade() >= 0){
            if (v_corrida[iteracao].p_carro->get_carregando() == true || v_corrida[iteracao].p_carro->get_capacidade() == 0){
                v_corrida[iteracao].p_carro->muda_carregando(true);
                if (v_corrida[iteracao].p_carro->get_capacidade() == v_corrida[iteracao].p_carro->get_cap_max()){
                    v_corrida[iteracao].p_carro->muda_carregando(false);
                }else{
                    v_corrida[iteracao].p_carro->carrega_bateria(v_corrida[iteracao].p_carro->get_capacidade() * .2);
                }
            }

            //quando comeca corrida
            if (v_corrida[iteracao].p_carro->get_carregando() != true){
                if (v_corrida[iteracao].p_carro->get_capacidade() == v_corrida[iteracao].p_carro->get_cap_max() && v_corrida[iteracao].segundo == 0){
                    v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 2);
                }else if (v_corrida[iteracao].segundo == 0){
                    cout << " carrega carro ate cap_max em supercharge";
                    v_corrida[iteracao].p_carro->muda_carregando(true);
                }

                //Durante corrida
                if (v_corrida[iteracao].segundo != 0){
                    if (v_corrida[iteracao].p_carro->get_capacidade() >= (v_corrida[iteracao].p_carro->get_cap_max()*.7)){
                        v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 3);
                    }else if (v_corrida[iteracao].p_carro->get_capacidade() < (v_corrida[iteracao].p_carro->get_cap_max()*.25)){
                        //mete a carregar pq ta a metade
                        if (v_corrida[iteracao].p_carro->get_velocidade() == 0){
                            v_corrida[iteracao].p_carro->carrega_bateria(v_corrida[iteracao].p_carro->get_capacidade()*.2);
                            v_corrida[iteracao].p_carro->muda_carregando(true);
                        }else{
                            v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() - 10);
                        }
                    }else{
                        v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() + 2);
                    }
                }
            }
        }else{
            v_corrida[iteracao].p_carro->muda_velocidade(v_corrida[iteracao].p_carro->get_velocidade() - 1);
        }
    }
}