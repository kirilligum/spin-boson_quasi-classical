#pragma once
#include <vector>

using namespace std;

vector<vector<double>> integrate_traj(vector<double> state, int n_times, double end_time, double delta, double eps, vector<double> wb, vector<double> cb) ;

