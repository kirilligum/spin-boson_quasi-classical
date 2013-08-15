#include <iostream>
//#include <fstream>
#include <cmath>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
//#include <boost/range/algorithm.hpp>
//#include <boost/range/algorithm_ext.hpp>
//#include <boost/range/numeric.hpp>
//#include <boost/math/constants/constants.hpp>
//#include <boost/numeric/odeint.hpp>

#include "o.hpp"
#include "make_wb.hpp"
#include "make_cb.hpp"
#include "make_bath.hpp"
#include "make_initial_state.hpp"
#include "state.hpp"
#include "integrate_traj.hpp"
#include "box.hpp"
#include "electronic_population.hpp"

using namespace std;
using namespace std::placeholders;

int main(int argc, const char *argv[]) {
  using namespace std; 
  typedef vector<double> vd; typedef vector<vector<double>> vvd; typedef vector<vector<vector<double>>> vvvd;
  cout << "Reading parameters within main.cpp \n";
  const double 
    alpha = 0.09,
    wc = 2.5,
    wmax_factor = 1,
    beta = 5 ,
    delta = 1,
    eps = 0,
    end_time = 15 ,
    n1 = 1.0,
    n2 = 0.0,
    bin_start = 0.35,
    bin_end = 0.35;
  double seed = 2345;
  const int  
    n_threads = 1,
    n_times = 100, 
    n_modes = 100,
    n_trajs = 1000;
  vector<double> param = { alpha, wc, wmax_factor, beta, delta, eps, n_modes, n_trajs, end_time, n_times, n_threads, seed }; o("param",param);
  double eta = alpha*M_PI_2;
  double dw =wmax_factor*wc/n_modes;
  


  cout << "Dealing with bath ... \n";
  auto wb = make_wb(n_modes, dw);  o(wb,"wb.dat"); o("wb",wb);
  auto cb = make_cb(wb,eta,wc,dw); o(cb,"cb.dat"); o("cb",cb);

  cout << "Making initial states ... \n";
  vector<vector<double>> states(n_trajs);
  for(auto &i:states) {
    vector<double> pb,qb; tie(pb,qb) = make_bath(wb,cb,beta,++seed);
    i= make_initial_state(n1, bin_start,pb,qb,++seed); 
  }
  o(states,"states.dat");

  cout << "Integrating trajectories \n";
  vector<vector<vector<double>>> trajs;
  transform(states.begin(),states.end(),back_inserter(trajs), bind(integrate_traj,_1,n_times,end_time,delta,wb,cb));
  auto traj = trajs.front();
  for(auto &i:traj) {
    i.push_back(get_n1(i));
    i.push_back(get_n2(i));
  }
  o(traj,"traj.dat");

  cout << "binning ... \n";
  auto el_pop = electronic_population(trajs,n1,n2,bin_end);
  o(el_pop ,"el_pop.dat");
  
  return 0;
}
