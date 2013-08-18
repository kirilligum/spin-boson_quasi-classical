#include <vector>
#include <algorithm>

#include "spin_boson.hpp"

using namespace std;


spin_boson::spin_boson( double delta_ecoup, double eps_, vector<double> wbath, vector<double> cbath): d(delta_ecoup), eps(eps_), wb(wbath), cb(cbath) {}
double spin_boson::operator() (const vector<double> &s){
  double ecoup = s[1]*s[3]+s[2]*s[4];
  double bcoup=0.0;
  double bham=0.0;
  for (int i = 5; i < s.size()-1; ++(++i)) {
    int ib=(i-5)/2;
    bcoup +=cb[ib]*s[i+1];
    bham+= s[i]*s[i]+s[i+1]*s[i+1]*wb[ib]*wb[ib];
  }
  ecoup*=d;
  auto pauli_z =0.5*(s[1]*s[1]+s[2]*s[2]-s[3]*s[3]-s[4]*s[4]);
  bcoup+=eps;
  bcoup*=pauli_z;
  bham*=0.5;
  
  return bham+bcoup+ecoup;
  //return bham+bcoup+ecoup+eps*pauli_z;
}

eom_spin_boson::eom_spin_boson( double delta_ecoup, double eps_, vector<double> wbath, vector<double> cbath): d(delta_ecoup), eps(eps_), wb(wbath), cb(cbath) {}

void eom_spin_boson::operator() (const vector<double> &s, vector<double> &ds, const double){

  double nmn2 = 0.5*( s[1]*s[1] + s[2]*s[2] - s[3]*s[3] - s[4]*s[4]);
  double sum_cq = 0.0;

  for (int i = 5; i < s.size()-1; ++(++i)) {
    int ib=(i-5)/2;
    sum_cq += cb[ib]* s[i+1];
    ds[i]=-(wb[ib]*wb[ib]*s[i+1]+cb[ib]*nmn2);
    ds[i+1]= s[i];
  }
  sum_cq +=eps; // not sure about this yet. Steve has it

  ds[1]=-(d*s[4]+s[2]*sum_cq);
  ds[2]=(d*s[3]+s[1]*sum_cq);
  ds[3]=-(d*s[2]-s[4]*sum_cq);
  ds[4]=(d*s[1]-s[3]*sum_cq);

  ds[0]=0.0;
  ds.back()=0.0;

}
