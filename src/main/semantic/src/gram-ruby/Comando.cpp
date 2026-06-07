#include "Comando.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoIf.hpp"
#include "ComandoLista.hpp"
#include "ComandoRetorno.hpp"
#include "ComandoWhile.hpp"
#include "Expressao.hpp"
#include "ID.hpp"
#include <iostream>
#include "debug-util.hpp"

// SL -> ''     (regra 6)
// SL -> C SL   (regra 7)
vector<Comando*> Comando::extrai_lista_comandos(No_arv_parse* no) {
  if (no->regra == 6) return vector<Comando*>();
  vector<Comando*> res;
  res.push_back(extrai_comando(no->filhos[0]));           // C
  vector<Comando*> restante = extrai_lista_comandos(no->filhos[1]); // SL
  res.insert(res.end(), restante.begin(), restante.end());
  return res;
}

Comando* Comando::extrai_comando(No_arv_parse* no) {
  switch (no->regra) {

  case 8: {
    // C -> ID_LOCAL OP_ASSIGN Ea
    //      [0]      [1]       [2]
    ComandoAtribuicao* cmd = new ComandoAtribuicao();
    cmd->esquerda = ID::extrai_ID(no->filhos[0]);
    cmd->direita  = Expressao::extrai_expressao(no->filhos[2]);
    return cmd;
  }

  case 9: {
    // C -> RW_RETURN Ea
    //      [0]       [1]
    ComandoRetorno* cmd = new ComandoRetorno();
    cmd->expressao = Expressao::extrai_expressao(no->filhos[1]);
    return cmd;
  }

  case 10: {
    // C -> RW_IF Ea SL RW_END
    //      [0]   [1][2][3]
    ComandoIf* cmd = new ComandoIf();
    cmd->condicao = Expressao::extrai_expressao(no->filhos[1]);
    cmd->entao    = extrai_lista_comandos(no->filhos[2]);
    return cmd;
  }

  case 11: {
    // C -> RW_IF Ea SL RW_ELSE SL RW_END
    //      [0]   [1][2][3]     [4][5]
    ComandoIf* cmd = new ComandoIf();
    cmd->condicao = Expressao::extrai_expressao(no->filhos[1]);
    cmd->entao    = extrai_lista_comandos(no->filhos[2]);
    cmd->senao    = extrai_lista_comandos(no->filhos[4]);
    return cmd;
  }

  case 12: {
    // C -> RW_WHILE Ea SL RW_END
    //      [0]      [1][2][3]
    ComandoWhile* cmd = new ComandoWhile();
    cmd->condicao = Expressao::extrai_expressao(no->filhos[1]);
    cmd->corpo    = extrai_lista_comandos(no->filhos[2]);
    return cmd;
  }

  case 13: {
    // C -> RW_BEGIN SL RW_END
    //      [0]      [1][2]
    ComandoLista* cmd = new ComandoLista();
    cmd->lista_comandos = extrai_lista_comandos(no->filhos[1]);
    return cmd;
  }

  default:
    cerr << "Erro: regra de comando desconhecida: " << no->regra << endl;
    return NULL;
  }
}

void Comando::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "Comando generico" << endl;
}
