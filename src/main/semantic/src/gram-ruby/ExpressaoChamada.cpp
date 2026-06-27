#include "ExpressaoChamada.hpp"
#include "debug-util.hpp"
#include <iostream>

ExpressaoChamada::ExpressaoChamada(){

}

void ExpressaoChamada::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "CHAMADA[" << nome_funcao->nome << "](" << endl;
  for (int i = 0; i < (int)arglist.size(); ++i) {
    arglist[i]->debug_com_tab(tab + 1);
    if (i < (int)arglist.size() - 1) {
      tab3(tab + 1);
      cerr << "," << endl;
    }
  }
  tab3(tab);
  cerr << ")" << endl;
}