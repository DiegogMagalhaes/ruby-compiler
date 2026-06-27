#include "FrameAcessoTemp.hpp"
#include <iostream>
using namespace std;

FrameAcessoTemp::FrameAcessoTemp() {
    id = 0;
}

void FrameAcessoTemp::debug() {
  cerr << "Temp[t" << id << "]";
}