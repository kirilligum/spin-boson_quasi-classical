#pragma once

struct j {
  double eta;
  double wc;
  j(double eta_, double wc_);
  double operator()(double w) ;
};

