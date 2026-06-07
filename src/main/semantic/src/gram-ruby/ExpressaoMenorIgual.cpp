#include "ExpressaoMenorIgual.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

ExpressaoMenorIgual::ExpressaoMenorIgual() { }

void ExpressaoMenorIgual::debug_com_tab(int tab) {
  tab3(tab); cerr << "<= [ INI MenorIgual" << endl;
  esquerda->debug_com_tab(tab + 1);
  tab3(tab); cerr << "<=" << endl;
  direita->debug_com_tab(tab + 1);
  tab3(tab); cerr << "<= ] FIM MenorIgual" << endl;
}
