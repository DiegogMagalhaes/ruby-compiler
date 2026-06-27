#ifndef _FRAME_ACESSO_TEMP_HPP_
#define _FRAME_ACESSO_TEMP_HPP_
#include "FrameAcesso.hpp"

class FrameAcessoTemp : public FrameAcesso {
public:
  int id; // id unico do pseudo-registrador/temporario.
  FrameAcessoTemp();

  void debug();
};

#endif
