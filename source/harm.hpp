#include <vector>
#include <algorithm>
using namespace std;

struct harm {
  const double d;
  vector<double> wb,cb;
  harm( double delta_ecoup, vector<double> wbath, vector<double> cbath): d(delta_ecoup), wb(wbath), cb(cbath) {}
  double energy(const vector<double> &s){
    double ham=0.0;
    for_each(s.begin()+1, s.end()-1, [&](double si) { ham+=si*si*0.5;});
    return ham;
  }
  void eom(const vector<double> &s, vector<double> &ds, const double){
    ds.front()=0.0;
    ds.back()=0.0;
    for (int i = 1; i < s.size()-1; ++(++i)) {
      ds[i]=-s[i+1];
      ds[i+1]=s[i];
    }
  }
};

//struct harm {
  //const double d;
  //vector<double> wb,cb;
  //harm( double delta_ecoup, vector<double> wbath, vector<double> cbath): d(delta_ecoup), wb(wbath), cb(cbath) {}
  //double operator() (const vector<double> &s){
    //double ham=0.0;
    //for_each(s.begin()+1, s.end()-1, [&](double si) { ham+=si*si*0.5;});
    //return ham;
  //}
//};

//struct eom_harm {
  //const double d;
  //vector<double> wb,cb;
  //eom_harm( double delta_ecoup, vector<double> wbath, vector<double> cbath): d(delta_ecoup), wb(wbath), cb(cbath) {}
  //void operator() (const vector<double> &s, vector<double> &ds, const double){
    //ds.front()=0.0;
    //ds.back()=0.0;
    //for (int i = 1; i < s.size()-1; ++(++i)) {
      //ds[i]=-s[i+1];
      //ds[i+1]=s[i];
    //}
  //}
//};
