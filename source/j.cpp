#include <cmath>

#include "j.hpp"

j::j(double eta_, double wc_) : eta(eta_), wc(wc_) {}

double j::operator()(double w) {
  return eta*w*exp(-w/wc);
}


