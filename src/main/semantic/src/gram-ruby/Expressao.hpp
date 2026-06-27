#ifndef _EXPRESSAO_HPP_
#define _EXPRESSAO_HPP_
#include "Arvore.hpp"
using namespace std;

class Expressao {
public:
  static Expressao* extrai_expressao(No_arv_parse* no);
  static void extrai_lista_argumentos(No_arv_parse* no, vector<Expressao*> &lista);
  virtual void debug_com_tab(int tab);
};

#endif
