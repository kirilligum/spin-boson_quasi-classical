#include <vector>
#include <functional>
//#include <iostream>
//#include <fstream>
//#include <boost/range/algorithm.hpp>
//#include <boost/range/algorithm_ext.hpp>
#include <boost/numeric/odeint.hpp>

#include "ode_step.hpp"

using namespace std;


ode_step::ode_step(double dt_,function<void(const vector<double>&,vector<double>&,const double)> eom_, function<double(const vector<double>&)> hamiltonian_energy): dt(dt_), eom(eom_), ham(hamiltonian_energy){}

vector<double> ode_step::operator()(vector<double> a, vector<double> b) {
  using namespace boost::numeric::odeint;
  vector<double> current(a);
  //boost::copy(current, ostream_iterator<double> (cout, " ")); cout << "** ";
  integrate(eom, current, a[0],a[0]+dt,dt*1e-3);
  //boost::copy(current, ostream_iterator<double> (cout, " ")); cout << "\n";
  current[0]+=dt;
  current.back()=ham(current);
  return current;
}
