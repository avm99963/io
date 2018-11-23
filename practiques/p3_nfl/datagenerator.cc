#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
  cout << "Benvingut al generador de dades.\n\nIntrodueix el nombre n: ";
  int n, r, s;
  cin >> n;
  if (n%2 != 0 || n < 4) {
    cout << "Error: n ha de ser parell i major o igual que 4.";
    return 1;
  }
  cout << "Introdueix el nombre r: ";
  cin >> r;
  cout << "Introdueix el nombre s: ";
  cin >> s;
  string filename = "nfl.dat";
  
  ofstream file;
  file.open(filename);
  
  file << "param n:=" << n << ";\nparam r:=" << r << ";\nparam s:=" << s << ";\n\nparam: PARTITS: c:=\n";

  for (int i = 1; i <= n; ++i)
    for (int j = i+1; j <= n; ++j)
      for (int k = 1; k <= (n/2)*(r+s) - r; ++k) {
        int v;
        if (i > n/2 || j <= n/2) {
          // Partits INTRAdivisionals
          if (k == 1) v = 0;
          else v = pow(2, k-2);
        } else v = 0; // Partits INTERdivisionals
        file << i << " " << j << " " << k << " " << v << (i == n-1 && j == n && k == (n/2)*(r+s) - r ? ";" : "") << endl;
      }
}
