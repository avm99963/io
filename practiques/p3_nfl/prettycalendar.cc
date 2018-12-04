#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<VVB> VVVB;

void print_vector(VVB &v) {
  for (int i = 0; i < (int)v.size(); ++i) {
    for (int j = 0; j < (int)v[0].size(); ++j) {
      cout << (v[i][j] ? "1" : "0") << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  int n, r, s, j;
  cin >> n >> r >> s >> j;
  //cout << n << " "<< r << " " << s << " " << j << endl;
  int lines = j*(n*(n-1))/2;
  VVVB x(j+1, VVB(n+1, VB(n+1)));
  for (int it = 0; it < lines; ++it) {
    int i, j, k, b;
    cin >> i >> j >> k >> b;
    //cout << i << " " << j << " " << k << " " << k << " " << (b==1 ? "1" : "0") << endl;
    x[k][i][j] = (b == 1);
  }

  for (int k = 1; k <= j; ++k) {
    //print_vector(x[k]);
    cout << "=== JORNADA " << k << " ===" << endl;
    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < n; ++j) {
        if (x[k][i][j]) cout << "* Equip " << i << " - Equip " << j << endl;
      }
    }
    cout << endl;
  }
}
