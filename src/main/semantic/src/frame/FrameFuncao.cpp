#include "FrameFuncao.hpp"
#include "FrameAcessoNoFrame.hpp"
#include "FrameAcessoTemp.hpp"
#include "FrameAcesso.hpp"
#include "Funcao.hpp"
#include "ExpressaoVariavel.hpp"
#include "ExpressaoChamada.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoRetorno.hpp"
#include "ComandoIf.hpp"
#include "ComandoWhile.hpp"
#include "ComandoLista.hpp"
#include "ExpressaoSoma.hpp"
#include "ExpressaoSubtracao.hpp"
#include "ExpressaoMultiplicacao.hpp"
#include "ExpressaoDivisao.hpp"
#include "ExpressaoMod.hpp"
#include "ExpressaoIgualdade.hpp"
#include "ExpressaoDiferente.hpp"
#include "ExpressaoMenor.hpp"
#include "ExpressaoMenorIgual.hpp"
#include "ExpressaoMaior.hpp"
#include "ExpressaoMaiorIgual.hpp"
#include "ExpressaoNegacao.hpp"
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

FrameFuncao::FrameFuncao() {
    tamanho_frame = 0;
    n_param_entrada = 0;
    n_maximo_param_saida = 0;
    n_pseudo_registradores = 0;
    n_variaveis_no_frame = 0;
}

static void coleta_var(Expressao* expr, vector<ExpressaoVariavel*>& vars){
    if(!expr) return;

    if(auto* e = dynamic_cast<ExpressaoVariavel*>(expr)){
        vars.push_back(e);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoChamada*>(expr)){
        for (int i = 0; i < (int)e->arglist.size(); i++){
            coleta_var(e->arglist[i], vars);
        }
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoNegacao*>(expr)){
        coleta_var(e->expressao, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoSoma*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoSubtracao*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoDivisao*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoMultiplicacao*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoMod*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoIgualdade*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoDiferente*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoMaior*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoMaiorIgual*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoMenor*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
    if(auto* e = dynamic_cast<ExpressaoMenorIgual*>(expr)){
        coleta_var(e->esquerda, vars);
        coleta_var(e->direita, vars);
        return;
    }
}

static void percorre_expr(Expressao* expr, set<string>& vars_call, vector<ExpressaoVariavel*>& all_vars, int& max_args){

    if(!expr) return;

    if(auto* e = dynamic_cast<ExpressaoVariavel*>(expr)){
        all_vars.push_back(e);
        return;
    }

    if(auto* e = dynamic_cast<ExpressaoChamada*>(expr)){
        int n = (int)e->arglist.size();
        if(n>max_args) max_args = n;
        for(int i = 0; i<n; ++i){
            vector<ExpressaoVariavel*> vars_arg;
            coleta_var(e->arglist[i], vars_arg);
            for(auto* v: vars_arg)
                vars_call.insert(v->nome->nome);
            percorre_expr(e->arglist[i], vars_call, all_vars, max_args);
        }
        return;
    }

    if(auto* e = dynamic_cast<ExpressaoNegacao*>(expr)) {
        percorre_expr(e->expressao, vars_call, all_vars, max_args);
        return;
    }
    if (auto* e = dynamic_cast<ExpressaoSoma*>(expr)) {
        percorre_expr(e->esquerda, vars_call, all_vars, max_args);
        percorre_expr(e->direita, vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoSubtracao*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoMultiplicacao*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoDivisao*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoMod*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoIgualdade*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoDiferente*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoMenor*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoMenorIgual*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoMaior*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
      if (auto* e = dynamic_cast<ExpressaoMaiorIgual*>(expr)) {
        percorre_expr(e->esquerda,vars_call, all_vars, max_args);
        percorre_expr(e->direita,vars_call, all_vars, max_args);
        return;
      }
}


static void percorre_comandos(const vector<Comando*>& cmds, set<string>& vars_call, vector<ExpressaoVariavel*>& all_vars, int& max_args){

for (int i = 0; i<(int)cmds.size(); ++i){
    Comando* cmd = cmds[i];

    if(auto* c = dynamic_cast<ComandoAtribuicao*>(cmd)){
        ExpressaoVariavel* var_esq = new ExpressaoVariavel();
        var_esq->nome = c->esquerda;
        all_vars.push_back(var_esq);
        percorre_expr(c->direita, vars_call, all_vars, max_args);
    }else if(auto* c = dynamic_cast<ComandoRetorno*>(cmd)){
        percorre_expr(c->expressao, vars_call, all_vars, max_args);
    }else if (auto* c = dynamic_cast<ComandoIf*>(cmd)) {
        percorre_expr(c->condicao, vars_call, all_vars, max_args);
        percorre_comandos(c->entao, vars_call, all_vars, max_args);
        percorre_comandos(c->senao, vars_call, all_vars, max_args);
    }else if (auto* c = dynamic_cast<ComandoWhile*>(cmd)) {
        percorre_expr(c->condicao, vars_call, all_vars, max_args);
        percorre_comandos(c->corpo, vars_call, all_vars, max_args);
    } else if (auto* c = dynamic_cast<ComandoLista*>(cmd)) {
        percorre_comandos(c->lista_comandos, vars_call, all_vars, max_args);
    }
}

}

FrameFuncao* FrameFuncao::gera_frame_de_funcao(Funcao* fun) {
    FrameFuncao* frame = new FrameFuncao();

    map<string, FrameAcesso*> map_frame_acesso;

    frame->n_param_entrada = (int)fun->parametros.size();
    for(int i = 0; i < (int)fun->parametros.size(); ++i){
        FrameAcessoNoFrame* ac = new FrameAcessoNoFrame();
        ac->posicao_no_frame = (i+1) * 8; // FP+8, FP+16, ...
        map_frame_acesso[fun->parametros[i]->nome->nome] = ac;
    }

    set<string> vars_call;
    vector<ExpressaoVariavel*> all_vars;
    int max_args = 0;
    percorre_comandos(fun->comandos, vars_call,all_vars,max_args);

    frame->n_maximo_param_saida = max_args;

    int prox_pos_frame = -40;
    int prox_id_temp = 1;

    for(int i = 0; i <(int)all_vars.size();++i){
        string nome = all_vars[i]->nome->nome;

        if(map_frame_acesso.count(nome)) {
            all_vars[i]->acesso_frame = map_frame_acesso[nome];
            continue;
        }

        if(vars_call.count(nome)){
            FrameAcessoNoFrame* ac = new FrameAcessoNoFrame();
            ac->posicao_no_frame = prox_pos_frame;
            prox_pos_frame -= 8;
            map_frame_acesso[nome] = ac;
        }
        else{
            FrameAcessoTemp* ac = new FrameAcessoTemp();
            ac->id = prox_id_temp++;
            map_frame_acesso[nome] = ac;
        }
    }

    for(int i = 0; i < (int)all_vars.size(); ++i){
        string nome = all_vars[i]->nome->nome;
        if(map_frame_acesso.count(nome)){
            all_vars[i]->acesso_frame = map_frame_acesso[nome];
        }
    }

    int n_no_frame = 0;
    int n_temp = 0;
    for (auto i = map_frame_acesso.begin(); i != map_frame_acesso.end(); ++i){
        if(dynamic_cast<FrameAcessoNoFrame*>(i->second)){
            FrameAcessoNoFrame* ac = dynamic_cast<FrameAcessoNoFrame*>(i->second);
            if(ac->posicao_no_frame < 0) n_no_frame++;
        } else if(dynamic_cast<FrameAcessoTemp*>(i->second)){
            n_temp++;
        }
    }

    frame->n_variaveis_no_frame = n_no_frame;
    frame->n_pseudo_registradores = n_temp;
    frame->tamanho_frame = 40 + n_no_frame * 8;
    return frame;
}

void FrameFuncao::debug() {
    cerr << "=== FrameFuncao ===" << endl;
    cerr << "tamanho_frame: "         << tamanho_frame          << endl;
    cerr << "n_param_entrada: "       << n_param_entrada        << endl;
    cerr << "n_maximo_param_saida: "  << n_maximo_param_saida   << endl;
    cerr << "n_pseudo_registradores: "<< n_pseudo_registradores << endl;
    cerr << "n_variaveis_no_frame: "  << n_variaveis_no_frame   << endl;
}
