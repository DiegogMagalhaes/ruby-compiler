#include "ComandoWhile.hpp"
#include <iostream>
#include "debug-util.hpp"
using namespace std;

ComandoWhile::ComandoWhile() { condicao = NULL; }

void ComandoWhile::debug_com_tab(int tab) {
  tab3(tab); cerr << "WHILE" << endl;
  condicao->debug_com_tab(tab + 1);
  tab3(tab); cerr << "DO" << endl;
  for (int i = 0; i < (int)corpo.size(); ++i) corpo[i]->debug_com_tab(tab + 1);
  tab3(tab); cerr << "END" << endl;
}
