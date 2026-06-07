#include "ExpressaoDiferente.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

ExpressaoDiferente::ExpressaoDiferente() { }

void ExpressaoDiferente::debug_com_tab(int tab) {
  tab3(tab); cerr << "!= [ INI Diferente" << endl;
  esquerda->debug_com_tab(tab + 1);
  tab3(tab); cerr << "!=" << endl;
  direita->debug_com_tab(tab + 1);
  tab3(tab); cerr << "!= ] FIM Diferente" << endl;
}
