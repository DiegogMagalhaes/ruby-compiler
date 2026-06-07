#ifndef _EXPRESSAO_MAIOR_HPP_
#define _EXPRESSAO_MAIOR_HPP_
#include "Expressao.hpp"
using namespace std;

class ExpressaoMaior : public Expressao {
public:
  Expressao* esquerda;
  Expressao* direita;
  ExpressaoMaior();
  void debug_com_tab(int tab);
};

#endif
