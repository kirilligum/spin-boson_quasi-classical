#pragma once
#include <vector>
#include <functional>
//#include <iostream>
//#include <fstream>
//#include <boost/range/algorithm.hpp>
//#include <boost/range/algorithm_ext.hpp>
#include <boost/numeric/odeint.hpp>


using namespace std;


struct ode_step {
  const double dt;
  function<void(const vector<double>&,vector<double>&,const double)> eom;
  function<double(const vector<double>&)> ham;
  ode_step(double dt_,function<void(const vector<double>&,vector<double>&,const double)> eom_, function<double(const vector<double>&)> hamiltonian_energy);
  vector<double> operator()(vector<double> a, vector<double> b);
};

