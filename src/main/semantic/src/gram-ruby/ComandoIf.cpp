#include "ComandoIf.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

ComandoIf::ComandoIf() { condicao = NULL; }

void ComandoIf::debug_com_tab(int tab) {
  tab3(tab); cerr << "IF" << endl;
  condicao->debug_com_tab(tab + 1);
  tab3(tab); cerr << "THEN" << endl;
  for (int i = 0; i < (int)entao.size(); ++i) entao[i]->debug_com_tab(tab + 1);
  if (!senao.empty()) {
    tab3(tab); cerr << "ELSE" << endl;
    for (int i = 0; i < (int)senao.size(); ++i) senao[i]->debug_com_tab(tab + 1);
  }
  tab3(tab); cerr << "END" << endl;
}
