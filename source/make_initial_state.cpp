#include "make_initial_state.hpp"
#include <vector>
#include <random>
#include <cmath>
#include "p_from_n.hpp"
#include "x_from_n.hpp"

using namespace std;

vector<double> make_initial_state(double n1, double bin_start, double n_shift, vector<double> pb, vector<double> qb, int seed) {
  std::mt19937 g(++seed);
  std::uniform_real_distribution<double> ran_pi(0.0,2*M_PI);
  uniform_real_distribution<double> ran_bin(-bin_start,bin_start);
  double n2=1.0-n1;
  n1+=ran_bin(g);
  n2+=ran_bin(g);
  const double q1=ran_pi(g),q2=ran_pi(g);
  vector<double> state (1+4+2*pb.size()+1,0.0);// time+pxpx+PQ+energy
  state[0]=0.0;
  state.back()=0.0;
  state[1]=p_from_n{n_shift}(n1,q1);
  state[2]=x_from_n{n_shift}(n1,q1);
  state[3]=p_from_n{n_shift}(n2,q2);
  state[4]=x_from_n{n_shift}(n2,q2);
  for (size_t i = 0; i < pb.size(); ++i) {
    state[5+2*i]=pb[i];
    state[5+2*i+1]=qb[i];
  }
  return state;
}
