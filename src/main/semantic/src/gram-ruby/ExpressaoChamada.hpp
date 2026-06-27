#ifndef _EXPRESSAO_CHAMADA_HPP_
#define _EXPRESSAO_CHAMADA_HPP_
#include <vector>
#include "ID.hpp"
#include "Expressao.hpp"

class ExpressaoChamada : public Expressao{
    public:
        ID* nome_funcao;
        vector<Expressao*> arglist;

        ExpressaoChamada();
        void debug_com_tab(int tab);
};

#endif