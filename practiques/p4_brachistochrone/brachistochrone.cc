#include <iostream>
#include <cmath>
using namespace std;

int main() {
  double r;
  double tf;
  cin >> r >> tf;

  int n = 5000;
  
  for (int i = 0; i <= n; ++i) {
    double t = i*tf/n;
    double x = r*(t - sin(t));
    double y = r*(1 - cos(t));
    cout << x << " " << y << endl;
  }
}
