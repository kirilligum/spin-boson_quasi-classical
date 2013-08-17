#include "state.hpp"

#include <vector>
using namespace std;

double get_n1::operator()(vector<double> s) {
  return 0.5*(s[1]*s[1]+s[2]*s[2])-n_shift;
}

double get_n2::operator()(vector<double> s) {
  return 0.5*(s[3]*s[3]+s[4]*s[4])-n_shift;
}
