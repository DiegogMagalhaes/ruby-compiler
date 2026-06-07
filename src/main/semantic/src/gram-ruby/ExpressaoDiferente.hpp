#ifndef _EXPRESSAO_DIFERENTE_HPP_
#define _EXPRESSAO_DIFERENTE_HPP_
#include "Expressao.hpp"
using namespace std;

class ExpressaoDiferente : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  ExpressaoDiferente();
  void debug_com_tab(int tab);
};

#endif
