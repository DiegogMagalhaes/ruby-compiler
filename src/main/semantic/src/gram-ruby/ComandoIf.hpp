#ifndef _COMANDO_IF_HPP_
#define _COMANDO_IF_HPP_
#include "Comando.hpp"
#include "Expressao.hpp"
#include <vector>
using namespace std;

class ComandoIf : public Comando {
public:
  Expressao* condicao;
  vector<Comando*> entao;
  vector<Comando*> senao; // vazio se não houver else
  ComandoIf();
  void debug_com_tab(int tab);
};

#endif
