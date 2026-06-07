#ifndef _COMANDO_WHILE_HPP_
#define _COMANDO_WHILE_HPP_
#include "Comando.hpp"
#include "Expressao.hpp"
#include <vector>
using namespace std;

class ComandoWhile : public Comando {
public:
  Expressao* condicao;
  vector<Comando*> corpo;
  ComandoWhile();
  void debug_com_tab(int tab);
};

#endif
