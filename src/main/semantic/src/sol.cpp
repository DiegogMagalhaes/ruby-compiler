#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
using namespace std;

#include "Gramatica.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"
#include "Funcao.hpp"
#include "Analisador.hpp"
#include "Tipo.hpp"
#include "ValorLiteral.hpp"

// ------------------------------------------------------------
// Le parametros de um arquivo .params
// Formato: um valor por linha
//   true / false  - BOOL
//   contem '.'    - FLOAT
//   resto         - INT
vector<ValorLiteral> le_params(const string& caminho) {
  vector<ValorLiteral> params;
  ifstream arq(caminho);
  if (arq.fail()) {
    cerr << "Aviso: arquivo de params '" << caminho << "' nao encontrado." << endl;
    return params;
  }
  string linha;
  while (getline(arq, linha)) {
    if (linha.empty()) continue;
    ValorLiteral v;
    if (linha == "true" || linha == "false") {
      v.tipo       = new Tipo(Tipo::BOOL);
      v.valor_bool = (linha == "true");
    } else if (linha.find('.') != string::npos) {
      v.tipo        = new Tipo(Tipo::FLOAT);
      v.valor_float = stof(linha);
    } else {
      v.tipo      = new Tipo(Tipo::INT);
      v.valor_int = stoi(linha);
    }
    params.push_back(v);
  }
  return params;
}

int main(int argc, char* argv[]) {
  if (argc != 1 && argc != 3 && argc != 4) {
    cerr << "Uso: " << argv[0]
         << " [gramatica.site tabela_lr1.conf [arquivo.params]]" << endl;
    return 1;
  }

  string nome_gramatica = "gramatica-ruby.site";
  string nome_tab_lr1   = "tabela_lr1.conf";
  string nome_params    = "";

  if (argc >= 3) {
    nome_gramatica = argv[1];
    nome_tab_lr1   = argv[2];
  }
  if (argc == 4) {
    nome_params = argv[3];
  }

  ifstream arq_gramatica(nome_gramatica);
  ifstream arq_tabela_lr1(nome_tab_lr1);
  if (arq_gramatica.fail() || arq_tabela_lr1.fail()) {
    cerr << "Falha ao abrir: "
         << (arq_gramatica.fail()  ? nome_gramatica : "") << " "
         << (arq_tabela_lr1.fail() ? nome_tab_lr1   : "") << endl;
    return 1;
  }

  Parser parser(arq_gramatica, arq_tabela_lr1);
  parser.tabela.debug();
  parser.gram.debug();

  Arvore_parse arv = parser.executa_parse(cin);
  cerr << "Parse executado" << endl;
  arv.debug();

  Funcao* func = Funcao::extrai_funcao(arv.raiz);
  if (!func) { cerr << "Erro: funcao nao extraida" << endl; return 1; }
  func->debug();

  // Lê parâmetros do .params (se fornecido)
  vector<ValorLiteral> parametros_passados;
  if (!nome_params.empty()) {
    parametros_passados = le_params(nome_params);
  }

  Analisador ana;
  ana.calcula_retorno(func, parametros_passados);
  return 0;
}
