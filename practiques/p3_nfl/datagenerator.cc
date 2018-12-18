#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[]) {
  int n, r, s;

  if (argc >= 4) {
    n = atoi(argv[1]);
    r = atoi(argv[2]);
    s = atoi(argv[3]);
  } else {
    cout << "Benvingut al generador de dades.\n\nIntrodueix el nombre n: ";
    cin >> n;
    if (n%2 != 0 || n < 4) {
      cout << "Error: n ha de ser parell i major o igual que 4.";
      return 1;
    }
    cout << "Introdueix el nombre r: ";
    cin >> r;
    cout << "Introdueix el nombre s: ";
    cin >> s;
  }
  string filename = "nfl.dat";
  
  ofstream file;
  file.open(filename);
  
  file << "param n:=" << n << ";\nparam r:=" << r << ";\nparam s:=" << s << ";\n\nparam: PARTITS: c:=\n";

  for (int i = 1; i <= n; ++i)
    for (int j = i+1; j <= n; ++j)
      for (int k = 1; k <= (n/2)*(r+s) - r; ++k) {
        long double v;
        if (i > n/2 || j <= n/2) {
          // Partits INTRAdivisionals
          if (k == 1) v = 0;
          else v = pow((long long)2, (long long)k-2);
        } else v = 0; // Partits INTERdivisionals
        if (v < 0) {
          cerr << "NOOOO" << endl;
        }
        file << i << " " << j << " " << k << " " << v << (i == n-1 && j == n && k == (n/2)*(r+s) - r ? ";" : "") << endl;
      }
}
