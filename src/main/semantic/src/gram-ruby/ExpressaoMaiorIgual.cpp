#include "ExpressaoMaiorIgual.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

ExpressaoMaiorIgual::ExpressaoMaiorIgual() { }

void ExpressaoMaiorIgual::debug_com_tab(int tab) {
  tab3(tab); cerr << ">= [ INI MaiorIgual" << endl;
  esquerda->debug_com_tab(tab + 1);
  tab3(tab); cerr << ">=" << endl;
  direita->debug_com_tab(tab + 1);
  tab3(tab); cerr << ">= ] FIM MaiorIgual" << endl;
}
