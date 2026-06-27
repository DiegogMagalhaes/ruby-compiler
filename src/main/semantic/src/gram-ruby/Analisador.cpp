#include "Analisador.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoIf.hpp"
#include "ComandoLista.hpp"
#include "ComandoRetorno.hpp"
#include "ComandoWhile.hpp"
#include "ExpressaoDiferente.hpp"
#include "ExpressaoDivisao.hpp"
#include "ExpressaoIgualdade.hpp"
#include "ExpressaoMaior.hpp"
#include "ExpressaoMaiorIgual.hpp"
#include "ExpressaoMenor.hpp"
#include "ExpressaoMenorIgual.hpp"
#include "ExpressaoMod.hpp"
#include "ExpressaoMultiplicacao.hpp"
#include "ExpressaoNegacao.hpp"
#include "ExpressaoSoma.hpp"
#include "ExpressaoSubtracao.hpp"
#include "ExpressaoValor.hpp"
#include "ExpressaoVariavel.hpp"
#include "ExpressaoChamada.hpp"
#include "Tipo.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

// ---------------------------------------------------------------------------
// Escopo: pilha de mapas — suporta begin/end aninhados
typedef map<string, ValorLiteral> Escopo;
typedef vector<Escopo> PilhaEscopos;

// Busca variável do topo até a base da pilha
static bool busca_var(PilhaEscopos& pilha, const string& nome, ValorLiteral& out) {
  for (int i = (int)pilha.size() - 1; i >= 0; --i) {
    if (pilha[i].count(nome)) { out = pilha[i][nome]; return true; }
  }
  return false;
}

// Atribui no topo
// Ruby não possui shadowing real em begin/end.
// Portanto os exemplos de shadowing não retornarão a resposta esperada)
// Ref: https://www.ruby-lang.org/en/documentation/faq/4/". Diz:
// A new scope for a local variable is introduced in (1) the toplevel (main), (2) a class (or module) definition, or (3) a method definition.
static void atribui_var(PilhaEscopos& pilha, const string& nome, const ValorLiteral& val) {
  for (int i = (int)pilha.size() - 1; i >= 0; --i) {
    if (pilha[i].count(nome)) {
      pilha[i][nome] = val;
      return;
    }
  }
  if (!pilha.empty()) pilha.back()[nome] = val;
}

// ---------------------------------------------------------------------------
// Avaliação de expressões
static ValorLiteral avalia(Expressao* expr, PilhaEscopos& escopos);

static ValorLiteral opera_arit(const string& op,
                                const ValorLiteral& esq,
                                const ValorLiteral& dir) {
  ValorLiteral res;
  // Erro: booleano em operação aritmética
  if ((esq.tipo && esq.tipo->valor == Tipo::BOOL) ||
      (dir.tipo && dir.tipo->valor == Tipo::BOOL)) {
    cerr << "Erro de tipo: operacao aritmetica com booleano" << endl;
    res.tipo = new Tipo(Tipo::INT);
    return res;
  }
  bool tem_float = (esq.tipo && esq.tipo->valor == Tipo::FLOAT) ||
                   (dir.tipo && dir.tipo->valor == Tipo::FLOAT);
  if (tem_float) {
    res.tipo = new Tipo(Tipo::FLOAT);
    float ve = esq.tipo->valor == Tipo::FLOAT ? esq.valor_float : (float)esq.valor_int;
    float vd = dir.tipo->valor == Tipo::FLOAT ? dir.valor_float : (float)dir.valor_int;
    if      (op == "+") res.valor_float = ve + vd;
    else if (op == "-") res.valor_float = ve - vd;
    else if (op == "*") res.valor_float = ve * vd;
    else if (op == "/") { res.valor_float = vd==0.0f ? (cerr<<"Erro: divisao por zero"<<endl, 0.0f) : ve/vd; }
    else if (op == "%") { cerr << "Erro: % nao suportado em float" << endl; res.valor_float = 0; }
  } else {
    res.tipo = new Tipo(Tipo::INT);
    int ve = esq.valor_int, vd = dir.valor_int;
    if      (op == "+") res.valor_int = ve + vd;
    else if (op == "-") res.valor_int = ve - vd;
    else if (op == "*") res.valor_int = ve * vd;
    else if (op == "/") { res.valor_int = vd==0 ? (cerr<<"Erro: divisao por zero"<<endl, 0) : ve/vd; }
    else if (op == "%") { res.valor_int = vd==0 ? (cerr<<"Erro: mod por zero"<<endl, 0) : ve%vd; }
  }
  return res;
}

static ValorLiteral opera_rel(const string& op,
                               const ValorLiteral& esq,
                               const ValorLiteral& dir) {
  ValorLiteral res;
  res.tipo = new Tipo(Tipo::BOOL);
  // Erro: < <= > >= com booleano
  if (op != "==" && op != "!=" &&
      ((esq.tipo && esq.tipo->valor == Tipo::BOOL) ||
       (dir.tipo && dir.tipo->valor == Tipo::BOOL))) {
    cerr << "Erro de tipo: operador " << op << " nao aplicavel a booleano" << endl;
    res.valor_bool = false;
    return res;
  }
  bool tem_float = (esq.tipo && esq.tipo->valor == Tipo::FLOAT) ||
                   (dir.tipo && dir.tipo->valor == Tipo::FLOAT);
  if (op == "==" || op == "!=") {
    bool igual;
    if (esq.tipo->valor == Tipo::BOOL && dir.tipo->valor == Tipo::BOOL)
      igual = esq.valor_bool == dir.valor_bool;
    else if (tem_float) {
      float ve = esq.tipo->valor==Tipo::FLOAT ? esq.valor_float : (float)esq.valor_int;
      float vd = dir.tipo->valor==Tipo::FLOAT ? dir.valor_float : (float)dir.valor_int;
      igual = (ve == vd);
    } else {
      igual = esq.valor_int == dir.valor_int;
    }
    res.valor_bool = (op == "==") ? igual : !igual;
  } else {
    float ve = tem_float ? (esq.tipo->valor==Tipo::FLOAT ? esq.valor_float : (float)esq.valor_int) : (float)esq.valor_int;
    float vd = tem_float ? (dir.tipo->valor==Tipo::FLOAT ? dir.valor_float : (float)dir.valor_int) : (float)dir.valor_int;
    if      (op == "<")  res.valor_bool = ve <  vd;
    else if (op == "<=") res.valor_bool = ve <= vd;
    else if (op == ">")  res.valor_bool = ve >  vd;
    else if (op == ">=") res.valor_bool = ve >= vd;
  }
  return res;
}

static ValorLiteral avalia(Expressao* expr, PilhaEscopos& escopos) {
  ValorLiteral res;
  if (!expr) return res;

  if (auto* e = dynamic_cast<ExpressaoValor*>(expr))     return *e->valor;

  if (auto* e = dynamic_cast<ExpressaoVariavel*>(expr)) {
    if (!busca_var(escopos, e->nome->nome, res))
      cerr << "Erro: variavel '" << e->nome->nome << "' nao definida" << endl;
    return res;
  }

  if (auto* e = dynamic_cast<ExpressaoNegacao*>(expr)) {
    ValorLiteral v = avalia(e->expressao, escopos);
    if (!v.tipo || v.tipo->valor != Tipo::BOOL)
      cerr << "Erro de tipo: ! aplicado a nao-booleano" << endl;
    res.tipo = new Tipo(Tipo::BOOL);
    res.valor_bool = v.tipo ? !v.valor_bool : false;
    return res;
  }

  // Aritméticas
  if (auto* e = dynamic_cast<ExpressaoSoma*>(expr))
    return opera_arit("+", avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoSubtracao*>(expr))
    return opera_arit("-", avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoMultiplicacao*>(expr))
    return opera_arit("*", avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoDivisao*>(expr))
    return opera_arit("/", avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoMod*>(expr))
    return opera_arit("%", avalia(e->esquerda,escopos), avalia(e->direita,escopos));

  // Relacionais
  if (auto* e = dynamic_cast<ExpressaoIgualdade*>(expr))
    return opera_rel("==", avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoDiferente*>(expr))
    return opera_rel("!=", avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoMenor*>(expr))
    return opera_rel("<",  avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoMenorIgual*>(expr))
    return opera_rel("<=", avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoMaior*>(expr))
    return opera_rel(">",  avalia(e->esquerda,escopos), avalia(e->direita,escopos));
  if (auto* e = dynamic_cast<ExpressaoMaiorIgual*>(expr))
    return opera_rel(">=", avalia(e->esquerda,escopos), avalia(e->direita,escopos));

  if (auto* e = dynamic_cast<ExpressaoChamada*>(expr)) {
    cerr << "Aviso: chamada de funcao '" << e->nome_funcao->nome << "' retorna valor padrao" << endl;
    res.tipo = new Tipo(Tipo::INT);
    res.valor_int = 0;
    return res;
  }

  cerr << "Erro: expressao desconhecida em avalia()" << endl;
  return res;
}

// ---------------------------------------------------------------------------
// Execução de comandos
struct ExecRes { bool retornou; ValorLiteral valor; ExecRes(): retornou(false){} };

static ExecRes executa_lista(const vector<Comando*>& cmds, PilhaEscopos& esc, ValorLiteral& ult);

static ExecRes executa_cmd(Comando* cmd, PilhaEscopos& esc, ValorLiteral& ult) {
  ExecRes res;

  if (auto* c = dynamic_cast<ComandoAtribuicao*>(cmd)) {
    ValorLiteral val = avalia(c->direita, esc);
    atribui_var(esc, c->esquerda->nome, val);
    ult = val;
    return res;
  }

  if (auto* c = dynamic_cast<ComandoRetorno*>(cmd)) {
    res.retornou = true;
    res.valor = avalia(c->expressao, esc);
    ult = res.valor;
    return res;
  }

  if (auto* c = dynamic_cast<ComandoIf*>(cmd)) {
    ValorLiteral cond = avalia(c->condicao, esc);
    if (!cond.tipo || cond.tipo->valor != Tipo::BOOL)
      cerr << "Erro de tipo: condicao do if nao e booleana" << endl;
    bool exec = cond.tipo && cond.tipo->valor == Tipo::BOOL ? cond.valor_bool : (cond.valor_int != 0);
    if (exec)              return executa_lista(c->entao, esc, ult);
    if (!c->senao.empty()) return executa_lista(c->senao, esc, ult);
    return res;
  }

  if (auto* c = dynamic_cast<ComandoWhile*>(cmd)) {
    int limite = 100000;
    while (limite-- > 0) {
      ValorLiteral cond = avalia(c->condicao, esc);
      if (!cond.tipo || cond.tipo->valor != Tipo::BOOL) {
        cerr << "Erro de tipo: condicao do while nao e booleana" << endl;
        break;
      }
      if (!cond.valor_bool) break;
      ExecRes r = executa_lista(c->corpo, esc, ult);
      if (r.retornou) return r;
    }
    return res;
  }

  if (auto* c = dynamic_cast<ComandoLista*>(cmd)) {
    return executa_lista(c->lista_comandos, esc, ult);
  }

  cerr << "Erro: comando desconhecido em executa_cmd()" << endl;
  return res;
}

static ExecRes executa_lista(const vector<Comando*>& cmds, PilhaEscopos& esc, ValorLiteral& ult) {
  ExecRes res;
  for (int i = 0; i < (int)cmds.size(); ++i) {
    res = executa_cmd(cmds[i], esc, ult);
    if (res.retornou) return res;
  }
  return res;
}

// ---------------------------------------------------------------------------
// calcula_retorno — ponto de entrada público
int Analisador::calcula_retorno(Funcao* f, const vector<ValorLiteral>& params) {
  PilhaEscopos escopos;
  escopos.push_back(Escopo());

  // Inicializar parâmetros no escopo global da função
  for (int i = 0; i < (int)f->parametros.size() && i < (int)params.size(); ++i)
    escopos.back()[f->parametros[i]->nome->nome] = params[i];

  ValorLiteral ult;
  executa_lista(f->comandos, escopos, ult);

  // Formatar saída
  if (!ult.tipo) {
    cout << "0" << endl;
    return 0;
  }
  switch (ult.tipo->valor) {
  case Tipo::INT:
    cout << ult.valor_int << endl;
    break;
  case Tipo::FLOAT:
    cout << fixed << setprecision(2) << ult.valor_float << endl;
    break;
  case Tipo::BOOL:
    cout << (ult.valor_bool ? "true" : "false") << endl;
    break;
  }
  return 0;
}
