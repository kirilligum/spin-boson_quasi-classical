#include "make_wb.hpp"
#include <vector>
#include <boost/range/numeric.hpp>
using namespace std;

vector<double> make_wb(int n_modes, double dw) {
  vector<double> wb(n_modes,dw);
  boost::partial_sum(wb, wb.begin());
  return wb;
}
