#pragma once
#include <vector>
using namespace std;


struct get_n1 {
  double n_shift;
  double operator()(vector<double> s) ;
};

struct get_n2 {
  double n_shift;
  double operator()(vector<double> s) ;
};
