#include <cmath>
#include "x_from_n.hpp"

double x_from_n::operator()(double n, double q) { return -sqrt(2*(n+n_shift))*sin(q);}
