#include "ExpressaoMaior.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

ExpressaoMaior::ExpressaoMaior() { }

void ExpressaoMaior::debug_com_tab(int tab) {
  tab3(tab); cerr << "> [ INI Maior" << endl;
  esquerda->debug_com_tab(tab + 1);
  tab3(tab); cerr << ">" << endl;
  direita->debug_com_tab(tab + 1);
  tab3(tab); cerr << "> ] FIM Maior" << endl;
}
