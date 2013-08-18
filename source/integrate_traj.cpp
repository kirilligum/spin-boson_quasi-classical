#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <functional>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/numeric.hpp>
#include <boost/numeric/odeint.hpp>

#include "integrate_traj.hpp"
#include "ran_pi.hpp"
#include "p_from_n.hpp"
#include "x_from_n.hpp"
#include "spin_boson.hpp"
#include "ode_step.hpp"
#include "j.hpp"
#include "c.hpp"
#include "o.hpp"

using namespace std;

vector<vector<double>> integrate_traj(vector<double> state, int n_times, double end_time, double delta, double eps, vector<double> wb, vector<double> cb) {
  vector<vector<double>> traj(n_times,vector<double>(state));
  auto energy = spin_boson(delta,eps,wb,cb);
  boost::partial_sum(traj, traj.begin(),ode_step(end_time/n_times,eom_spin_boson(delta,eps,wb,cb),energy));
  traj.front().back()= energy(state);
  return traj;
}

