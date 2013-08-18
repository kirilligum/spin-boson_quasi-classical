#pragma once
using namespace std;


struct spin_boson {
  const double d,eps;
  vector<double> wb,cb;
  spin_boson( double delta_ecoup, double eps_, vector<double> wbath, vector<double> cbath);
  double operator() (const vector<double> &s);
};

struct eom_spin_boson {
  const double d,eps;
  vector<double> wb,cb;
  eom_spin_boson( double delta_ecoup, double eps_, vector<double> wbath, vector<double> cbath);
  void operator() (const vector<double> &s, vector<double> &ds, const double);
};
