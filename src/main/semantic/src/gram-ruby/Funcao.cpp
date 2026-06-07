#include "Funcao.hpp"
#include "debug-util.hpp"
#include <iostream>

Funcao::Funcao() {
  tipo_retorno = NULL;
}

// Regra 1: S -> RW_DEF ID_LOCAL OP_LPAREN LP OP_RPAREN SL RW_END
//               [0]    [1]       [2]        [3][4]       [5][6]
Funcao* Funcao::extrai_funcao(No_arv_parse *no) {
  if (no->regra != 1) return NULL;
  Funcao* res = new Funcao();
  res->tipo_retorno = NULL; // Ruby não possui tipo de retorno
  res->nome_funcao  = ID::extrai_ID(no->filhos[1]); // ID_LOCAL
  res->parametros   = Variavel::extrai_lista_parametros(no->filhos[3]); // LP
  res->comandos     = Comando::extrai_lista_comandos(no->filhos[5]);    // SL
  return res;
}

void debug_comandos(const vector<Comando*> &coms, int tab) {
  for (int ic = 0; ic < (int)coms.size(); ++ic)
    coms[ic]->debug_com_tab(tab + 1);
}

void Funcao::debug() {
  if (nome_funcao == NULL) { cerr << "NF NULL" << endl; return; }
  cerr << "Funcao:[retorno=dinamico][nome=" << nome_funcao->nome << "]" << endl;
  cerr << "      (Params:(";
  for (int i = 0; i < (int)parametros.size(); ++i)
    cerr << "dinamico " << parametros[i]->nome->nome << ", ";
  cerr << ") do" << endl;
  debug_comandos(comandos, 1);
  cerr << "end" << endl;
}
