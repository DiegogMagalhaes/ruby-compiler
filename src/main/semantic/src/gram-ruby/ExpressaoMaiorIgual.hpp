#ifndef _EXPRESSAO_MAIORIGUAL_HPP_
#define _EXPRESSAO_MAIORIGUAL_HPP_
#include "Expressao.hpp"
using namespace std;

class ExpressaoMaiorIgual : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  ExpressaoMaiorIgual();
  void debug_com_tab(int tab);
};

#endif
