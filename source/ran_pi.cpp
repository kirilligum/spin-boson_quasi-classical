#include "ran_pi.hpp"
#include <random>

double ran_pi(int seed) {
  std::mt19937 g(++seed);
  std::uniform_real_distribution<double> ran_pi(0.0,2*M_PI);
  return ran_pi(g);
}
