#include <cmath>
#include <functional>

#include "c.hpp"

using namespace std;

c::c(function<double(double)> jj, double dww) : j(jj),dw(dww) {}  

double c::operator()(double w) {
  return sqrt(2/M_PI*w*j(w)*dw);
}

