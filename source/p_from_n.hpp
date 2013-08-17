#pragma once

struct p_from_n {
  double n_shift;
  double operator()(double n, double q);
};
