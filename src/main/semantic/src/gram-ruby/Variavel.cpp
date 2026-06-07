#include "Variavel.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

// LPx -> ID_LOCAL        (regra 4)
// LPx -> ID_LOCAL , LPx  (regra 5)
vector<Variavel*> Variavel::extrai_lista_nao_vazia_parametros(No_arv_parse* no) {
  vector<Variavel*> res;
  res.push_back(extrai_variavel_P(no->filhos[0])); // filho[0] = ID_LOCAL
  if (no->regra == 4) return res;
  // regra 5: filho[2] = próximo LPx
  vector<Variavel*> restante = extrai_lista_nao_vazia_parametros(no->filhos[2]);
  res.insert(res.end(), restante.begin(), restante.end());
  return res;
}

// LP -> ''    (regra 2)
// LP -> LPx   (regra 3)
vector<Variavel*> Variavel::extrai_lista_parametros(No_arv_parse* no) {
  if (no->regra == 2) return vector<Variavel*>();
  return extrai_lista_nao_vazia_parametros(no->filhos[0]);
}

// P -> ID_LOCAL  (Ruby não possui declaração de tipo)
Variavel* Variavel::extrai_variavel_P(No_arv_parse* no) {
  Variavel* res = new Variavel();
  res->tipo = NULL; // tipo inferido em runtime
  res->nome = ID::extrai_ID(no); // no IS o nó ID_LOCAL
  return res;
}

void Variavel::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "[" << nome->nome << ":dinamico] Variavel" << endl;
}
