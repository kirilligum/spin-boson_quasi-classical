#include "boxcar.hpp"

double boxcar (double x, double a, double b, double ac) {
  if(x>=a && x<=b) return ac;
  else return 0.0;
}
