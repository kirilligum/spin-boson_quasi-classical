#include <tuple>
#include <vector>
#include <cmath>
#include <random>

#include "make_bath.hpp"

using namespace std;

pair<vector<double>,vector<double>> make_bath(vector<double> w, vector<double> c, double beta, int seed) {
  vector<double> p,q;
  //random_device rd;
  mt19937 gen(++seed);
  for (size_t i = 0; i < w.size(); ++i) {
    const double
      a = 2*tanh(0.5*beta*w[i]),
				/*** C++ Gaussian Distribution **************************************
				Gaussian(x) = 1/stddev * 1/sqrt(2*pi) * exp( -sq( (x-mean)/stddev ) )
				********************************************************************/
      mean_Q = -c[i]/(w[i]*w[i]),
      mean_P = 0.0,
      stddev_Q = 1/sqrt( a*w[i] ),
      stddev_P = sqrt( w[i]/a );
    q.emplace_back( normal_distribution<double>(mean_Q, stddev_Q )(gen));
    p.emplace_back( normal_distribution<double>(mean_P, stddev_P )(gen));
  }
  return make_pair(p,q);
}
