#include <cmath>
#include "p_from_n.hpp"

double p_from_n::operator()(double n, double q) { return sqrt(2*(n+n_shift))*cos(q);}
