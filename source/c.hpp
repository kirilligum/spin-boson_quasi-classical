#pragma once
#include <functional>

using namespace std;

struct c {
  function<double(double)> j;
  double dw;
  c(function<double(double)> jj, double dww);
  double operator()(double w) ;
};

