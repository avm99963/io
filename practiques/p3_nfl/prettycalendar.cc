#include <iostream>
#include <vector>
using namespace std;

typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<VVB> VVVB;

int main() {
  int n, r, s, j;
  cin >> n >> r >> s >> j;
  int lines = j*(n*(n-1))/2;
  VVVB x(j+1, VVB(n+1, VB(n+1)));
  for (int it = 0; it < lines; ++it) {
    int i, j, k, b;
    cin >> i >> j >> k >> b;
    x[k][i][j] = (b == 1);
  }

  for (int k = 1; k <= j; ++k) {
    cout << "=== JORNADA " << k << " ===" << endl;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (x[k][i][j]) cout << "* Equip " << i << " - Equip " << j << endl;
      }
    }
    cout << endl;
  }
}
