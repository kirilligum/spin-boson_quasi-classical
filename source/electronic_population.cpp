#include "electronic_population.hpp"
#include <cmath>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

#include "o.hpp"
#include "state.hpp"
#include "box.hpp"

  using namespace std;
  typedef vector<double> vd;
  typedef vector<vector<double>> vvd;
  typedef vector<vector<vector<double>>> vvvd;

vector<vector<double>> electronic_population(vector<vector<vector<double>>> trajs, double n1, double n2, double bin_end) {
  vvvd n1ts;
  transform(trajs.begin(),trajs.end(),back_inserter(n1ts),[=](vvd traj){
        vvd n1t;
        transform(traj.begin(),traj.end(),back_inserter(n1t), [=](vd point) {
          return vector<double>{point.front(), box(get_n1(point), n1, bin_end)};
          });
        return n1t;
      });

  vvd ave_n1_traj(n1ts.front());
  for_each(n1ts.begin()+1,n1ts.end(),[&](vvd a) { 
      for (size_t i = 0; i < a.size(); ++i) {
        ave_n1_traj[i][1]+=a[i][1];
      }
      });
  o(ave_n1_traj,"ave_n1_traj.dat");

  vvvd n2ts;
  transform(trajs.begin(),trajs.end(),back_inserter(n2ts),[=](vvd traj){
        vvd n2t;
        transform(traj.begin(),traj.end(),back_inserter(n2t), [=](vd point) {
          return vector<double>{point.front(), box(get_n2(point), n1, bin_end)};
          });
        return n2t;
      });

  vvd ave_n2_traj(n2ts.front());
  for_each(n2ts.begin()+1,n2ts.end(),[&](vvd a) { 
      for (size_t i = 0; i < a.size(); ++i) {
        ave_n2_traj[i][1]+=a[i][1];
      }
      });
  o(ave_n2_traj,"ave_n2_traj.dat");

  vvd ave_nn_traj(n1ts.front().size(),vd(2,0.0));
  for (size_t j = 0; j < n1ts.size(); ++j) {
      for (size_t i = 0; i < n1ts[j].size(); ++i) {
        ave_nn_traj[i][1]+=n1ts[j][i][1]-n2ts[j][i][1];
        if(j==0) ave_nn_traj[i][0]=n1ts[j][i][0];
      }
  }
  return ave_nn_traj;
}
