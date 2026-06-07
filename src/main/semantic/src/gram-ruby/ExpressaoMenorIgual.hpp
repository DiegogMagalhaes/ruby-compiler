#ifndef _EXPRESSAO_MENORIGUAL_HPP_
#define _EXPRESSAO_MENORIGUAL_HPP_
#include "Expressao.hpp"
using namespace std;

class ExpressaoMenorIgual : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  ExpressaoMenorIgual();
  void debug_com_tab(int tab);
};

#endif
