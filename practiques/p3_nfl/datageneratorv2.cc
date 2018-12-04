#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[]) {
  int n, r, s, jactual;

  if (argc >= 5) {
    n = atoi(argv[1]);
    r = atoi(argv[2]);
    s = atoi(argv[3]);
    jactual = atoi(argv[4]);
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
    cout << "Introdueix el nombre j: ";
    cin >> jactual;
  }
  string filename = "nflv2.dat";
  
  ofstream file;
  file.open(filename);
  
  file << "param n:=" << n << ";\nparam r:=" << r << ";\nparam s:=" << s << ";\nparam jactual:=" << jactual << ";\n\nparam: PARTITS: c:=\n";

  for (int i = 1; i <= n; ++i)
    for (int j = i+1; j <= n; ++j)
      for (int k = 1; k <= jactual; ++k) {
        int v;
        if (i > n/2 || j <= n/2) {
          // Partits INTRAdivisionals
          if (k == 1) v = 0;
          else v = pow(2, k-2);
        } else v = 0; // Partits INTERdivisionals
        file << i << " " << j << " " << k << " " << v << (i == n-1 && j == n && k == jactual ? ";" : "") << endl;
      }
}
