#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <functional>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/numeric.hpp>
#include <random>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/odeint.hpp>

using namespace std;

double ran_pi(int seed) {
  std::mt19937 g(++seed);
  std::uniform_real_distribution<double> ran_pi(0.0,2*boost::math::double_constants::pi);
  return ran_pi(g);
}


double p_from_n(double n, double q) { return sqrt(2*n+1)*cos(q);}
double x_from_n(double n, double q) { return sqrt(2*n+1)*cos(q);}

struct spin_boson {
  double operator() (const vector<double> &s){
    double ham=0.0;
    for_each(s.begin()+1, s.end(), [&](double si) { ham+=si*si*0.5;});
    return ham;
  }
};

struct d_spin_boson {
  d_spin_boson(){}
  void operator() (const vector<double> &s, vector<double> &ds, const double){
    for (int i = 1; i < s.size(); ++(++i)) {
      ds[i]=-s[i+1];
      ds[i+1]=s[i];
    }
  }
};


struct ode_step {
  const double dt;
  ode_step(double dt_): dt(dt_){}
  vector<double> operator()(vector<double> a, vector<double> b) {
    using namespace boost::numeric::odeint;
    vector<double> current(a);
    integrate(d_spin_boson(), current, a[0],a[0]+dt,dt*1e-3);
    current[0]+=dt;
    return current;
  }
};

int main(int argc, const char *argv[])
{
  using namespace std;
  cout << "Reading parameters within main.cpp \n";
  const double 
    alpha = 0.1,
    wc = 7.5,
    wmax_factor = 1,
    beta = 5 ,
    delta = 1,
    eps = 1,
    n_modes = 10,
    //n_modes = 100,
    n_trajs = 2,
    end_time = 15 ,
    n_times = 100,
    L = 0.3,
    n_threads = 1;
  double seed = 2345;
  vector<double> param = { alpha, wc, wmax_factor, beta, delta, eps, n_modes, n_trajs, end_time, n_times, L, n_threads, seed };
  boost::copy(param,ostream_iterator<double>(cout,"  ")); cout << "\n";
  
  cout << "Initializing the State \n";
  std::mt19937 g(++seed);
  std::uniform_real_distribution<double> ran_pi(0.0,2*boost::math::double_constants::pi);
  const double n1=1.0, n2=1.0-n1, nbin=0.0;
  const double q1=ran_pi(g),q2=ran_pi(g);
  vector<double> state (1+4+2*n_modes,0.0);
  state[0]=0.0;
  state[1]=p_from_n(n1,q1);
  state[2]=x_from_n(n1,q1);
  state[3]=p_from_n(n2,q2);
  state[4]=x_from_n(n2,q2);
  boost::copy(state,ostream_iterator<double>(cout,"  ")); cout << "\n";
  cout <<"initial state energy = " << spin_boson()(state) << "\n";

  cout << "Integrating a trajectory \n";
  vector<vector<double>> traj(static_cast<int>(n_times),vector<double>(state));
  boost::partial_sum(traj, traj.begin(),ode_step(end_time/n_times));
  ofstream oft("traj.dat");
  for(auto i: traj) { boost::copy(i, ostream_iterator<double>(oft," ")); oft <<"\n";}

  
  return 0;
}
