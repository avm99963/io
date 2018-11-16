#include <iostream>
#include <cmath>
#include <fstream>
#include "pointers.h"
#include "simplex_primal.h"
using namespace std;

const double TOL = 1e-12;

int main(int argc, char *argv[]) {
  // file.open(argv[1]);
  if (argc < 5) {
    cout << "=== AJUDA ===:\n\nPer utilitzar el programa, executeu \"./program A.dat b.dat c.dat taxacio\", on A.dat\nes el fitxer amb la matriu A, i b.dat i c.dat fitxers amb els vectors b i c`.\n\nDespres del nom del fitxer, introduiu 'bland' per usar\nla regla de Bland, o 'rmin' per utilitzar la regla dels costos reduits minims.\n";
    return 0;
  }

  ifstream Af;
  ifstream bf;
  ifstream cf;
  Af.open(argv[1]);
  bf.open(argv[2]);
  cf.open(argv[3]);

  if (!Af.good() || !bf.good() || !cf.good()) {
    cout << "Error: algun dels fitxers d'entrada especificats no existeix.\n";
    return 3;
  }

  int n, m;
  Af >> m >> n;
  string trash;
  bf >> trash >> trash;
  cf >> trash >> trash;
  double** A = create_pointer(m, n);
  double** b = create_pointer(m, 2);
  double** c = create_pointer(n, 2);
  
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      Af >> A[i][j];

  for (int i = 0; i < m; ++i)
    bf >> b[i][0];

  for (int i = 0; i < n; ++i)
    cf >> c[i][0];

  bool bland = (string(argv[4]) == "bland");

  // Let's start the simplex party!  
  cout << "[simplexP] Inici simplex primal amb regla de " << (bland ? "Bland" : "costos reduits minims") << "\n";
  cout << "[simplexP]   Fase I\n";
  double** AI = create_pointer(m, n+m);
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      AI[i][j] = A[i][j];

  for (int i = 0; i < m; ++i)
    AI[i][n+i] = 1;

  double** invB = create_pointer(m, m);
  for (int i = 0; i < m; ++i)
    invB[i][i] = 1;

  double** cI = create_pointer(n+m, 1);
  for (int i = n; i < n+m; ++i)
    cI[i][0] = 1;

  int* vb = create_pointer_int(m);
  for (int i = 0; i < m; ++i)
    vb[i] = n+i;

  int* vn = create_pointer_int(n);
  for (int i = 0; i < n; ++i)
    vn[i] = i;

  double** xb = copia_punter(b, m, 1);

  double z = 0;
  //cout << "n: " << n << ", m: " << m << endl;
  for (int i = 0; i < m; ++i)
    z += cI[vb[i]][0]*xb[i][0];

  int ioutI = 0, niterI = 0;
  while (ioutI == 0) {
    ++niterI;
    ioutI = simplex_primal(cI, AI, invB, b, vb, vn, xb, z, bland, niterI, false, n+m, m);
  }

  int iout = -1;
  // Si hem pogut trobar SBF a la fase I, continuem amb fase II
  if (ioutI == 1 && abs(z) < TOL) {
    cout << "[simplexP]   Fase II\n";
    // Eliminem les variables artificials del vector de variables no bas.
    int* vnnew = create_pointer_int(n-m);
    int curr = 0;
    for (int i = 0; i < n; ++i)
      if (vn[i] < n) {
        vnnew[curr] = vn[i];
        ++curr;
      }

    vn = vnnew;

    // Actualitzem valor de z al corresponent a la SBF trobada
    z = 0;
    for (int i = 0; i < m; ++i)
      z += c[vb[i]][0]*xb[i][0];

    // Iterem pel simplex primal
    iout = 0;
    int niter = 0;
    while (iout == 0) {
      ++niter;
      iout = simplex_primal(c, A, invB, b, vb, vn, xb, z, bland, niter, true, n, m);
    }
  } else {
    if (ioutI == 1) {
      cout << "[simplexP] El problema no es factible perque a la fase I hem vist z > 0.\n";
    }
  }

  cout << "[simplexP] Fi simplex primal\n";

  if (iout == 1) {
    cout << "\nVB* =\n";
    for (int i = 0; i < m; ++i)
      printf(" %4i", vb[i]+1);
    cout << "\n\nxb* =\n";
    for (int i = 0; i < m; ++i)
      printf(" %8.4f", xb[i][0]);
    cout << "\n\nVNB* =\n";
    for (int i = 0; i < n-m; ++i)
      printf(" %4i", vn[i]+1);
    cout << "\n\nz* = " << z << "\n";
  }
}
