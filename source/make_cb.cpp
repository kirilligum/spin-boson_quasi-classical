#include "make_cb.hpp"
#include <vector>
#include <boost/range/algorithm.hpp>
#include "j.hpp"
#include "c.hpp"

vector<double> make_cb (vector<double> wb, double eta, double wc, double dw) {
  vector<double> cb;
  boost::transform(wb,back_inserter(cb), c{j(eta,wc),dw});
  return cb;
}
