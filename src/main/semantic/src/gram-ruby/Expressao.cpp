#include "Expressao.hpp"
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
#include "ID.hpp"
#include "ValorLiteral.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

Expressao* Expressao::extrai_expressao(No_arv_parse* no) {
  switch (no->regra) {

  case 14: { // Ea -> OP_NOT Ea
    ExpressaoNegacao* res = new ExpressaoNegacao();
    res->expressao = extrai_expressao(no->filhos[1]);
    return res;
  }
  case 15:   // Ea -> Eb
  case 18:   // Eb -> Ec
  case 23:   // Ec -> E
  case 26:   // E  -> T
  case 30: { // T  -> F
    return extrai_expressao(no->filhos[0]);
  }

  case 16: { // Eb -> Ec OP_EQUAL Ec
    ExpressaoIgualdade* res = new ExpressaoIgualdade();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 17: { // Eb -> Ec OP_NOT_EQUAL Ec
    ExpressaoDiferente* res = new ExpressaoDiferente();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }

  case 19: { // Ec -> E OP_LESS E
    ExpressaoMenor* res = new ExpressaoMenor();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 20: { // Ec -> E OP_LESS_EQUAL E
    ExpressaoMenorIgual* res = new ExpressaoMenorIgual();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 21: { // Ec -> E OP_GREATER E
    ExpressaoMaior* res = new ExpressaoMaior();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 22: { // Ec -> E OP_GREATER_EQUAL E
    ExpressaoMaiorIgual* res = new ExpressaoMaiorIgual();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }

  case 24: { // E -> E OP_PLUS T
    ExpressaoSoma* res = new ExpressaoSoma();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 25: { // E -> E OP_MINUS T
    ExpressaoSubtracao* res = new ExpressaoSubtracao();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }

  case 27: { // T -> T OP_MULTIPLY F
    ExpressaoMultiplicacao* res = new ExpressaoMultiplicacao();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 28: { // T -> T OP_DIVIDE F
    ExpressaoDivisao* res = new ExpressaoDivisao();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }
  case 29: { // T -> T OP_MOD F
    ExpressaoMod* res = new ExpressaoMod();
    res->esquerda = extrai_expressao(no->filhos[0]);
    res->direita  = extrai_expressao(no->filhos[2]);
    return res;
  }

  case 31: { // F -> OP_LPAREN Ea OP_RPAREN
    return extrai_expressao(no->filhos[1]);
  }

  case 32: { // F -> ID_LOCAL OP_LPAREN ArgList OP_RPAREN
    ExpressaoChamada* res = new ExpressaoChamada();
    res->nome_funcao = ID::extrai_ID(no->filhos[0]);
    extrai_lista_argumentos(no->filhos[2], res->arglist);
    return res;
  }

  case 33: { // F -> ID_LOCAL
    ExpressaoVariavel* res = new ExpressaoVariavel();
    res->nome = ID::extrai_ID(no->filhos[0]);
    return res;
  }

  case 34: // F -> NUM_INT
  case 35: // F -> NUM_DEC
  case 36: // F -> RW_TRUE
  case 37: { // F -> RW_FALSE
    ExpressaoValor* res = new ExpressaoValor();
    res->valor = ValorLiteral::extrai_valor_literal(no->filhos[0]);
    return res;
  }

  default:
    cerr << "Erro: expressao desconhecida regra=" << no->regra << endl;
    return NULL;
  }
}

void Expressao::extrai_lista_argumentos(No_arv_parse* no, vector<Expressao*>& lista) {
  if (!no) return;
  switch (no->regra) {
  case 38: // ArgList -> ''
    return;
  case 39: // ArgList -> ArgListx
    extrai_lista_argumentos(no->filhos[0], lista);
    return;
  case 40: // ArgListx -> Ea
    lista.push_back(extrai_expressao(no->filhos[0]));
    return;
  case 41: // ArgListx -> Ea OP_COMMA ArgListx
    lista.push_back(extrai_expressao(no->filhos[0]));
    extrai_lista_argumentos(no->filhos[2], lista);
    return;
  default:
    cerr << "Erro: regra desconhecida em extrai_lista_argumentos=" << no->regra << endl;
    return;
  }
}

void Expressao::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "Expressao generica" << endl;
}
