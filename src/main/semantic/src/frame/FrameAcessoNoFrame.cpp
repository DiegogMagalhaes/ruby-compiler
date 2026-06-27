#include "FrameAcessoNoFrame.hpp"
#include <iostream>
using namespace std;

FrameAcessoNoFrame::FrameAcessoNoFrame() {
    posicao_no_frame = 0;
}

void FrameAcessoNoFrame::debug() {
  cerr << "Frame[FP" << (posicao_no_frame >= 0 ? "+" : "")
       << posicao_no_frame << "]";
}