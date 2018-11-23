#include <iostream>
#include <cmath>
#include <stdio.h>
#include "pointers.h"
using namespace std;

const int TOL = 1e-10;

// Funcio que actualitza la inversa eficientment
void actualitza_inversa(double** &invB, double** db, int indexp, int m) {
  double** E = create_pointer(m, m);
  for (int i = 0; i < m; ++i)
    E[i][i] = 1;

  for (int i = 0; i < m; ++i)
    E[i][indexp] = (i == indexp ? -1/db[indexp][0] : -db[i][0]/db[indexp][0]);

  invB = matrix_multiplication(E, invB, m, m, m);
}

int simplex_primal(double** c, double** A, double** &invB, double** b, int* &vb, int* &vn, double** &xb, double &z, bool bland, int &niter, bool faseII, int n, int m) {
  double** cn = create_pointer(n-m, 1);
  for (int i = 0; i < n-m; ++i)
    cn[i][0] = c[vn[i]][0];

  double** cb = create_pointer(m, 1);
  for (int i = 0; i < m; ++i)
    cb[i][0] = c[vb[i]][0];

  double** B = create_pointer(m, m);
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      B[i][j] = A[i][vb[j]];

  double** An = create_pointer(m, n-m);
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n-m; ++j)
      An[i][j] = A[i][vn[j]];

  double** r = matrix_subtraction(cn, matrix_transpose(matrix_multiplication(matrix_transpose(cb, m, 1), matrix_multiplication(invB, An, m, m, n-m), 1, m, n-m), 1, n-m), n-m, 1);

  // Detectem si tenim una solucio optima.
  bool sbfo = true;
  for (int i = 0; i < n-m; ++i)
    if (r[i][0] < 0) {
      sbfo = false;
      break;
    }

  if (sbfo) {
    if (faseII)
      printf("[simplexP]     Iteracio %4d : Solucio optima trobada! z = %9.6f\n", niter, z);
    else
      printf("[simplexP]     Iteracio %4d : Solucio Basica Factible trobada!\n", niter);

    return 1;
  }

  // Escollim quina variable no basica entra a la base
  int q = -1;
  int indexq = 0;

  if (bland) {
    for (int i = 0; i < n-m; ++i)
      if (r[i][0] < 0 && (vn[i] < q || q == -1)) {
        indexq = i;
        q = vn[i];
      }
  } else {
    double minrq = 0;
    for (int i = 0; i < n-m; ++i)
      if (r[i][0] < minrq) {
        indexq = i;
        q = vn[i];
        minrq = r[i][0];
      }
  }

  double** Aq = create_pointer(m, 1);
  for (int i = 0; i < m; ++i)
    Aq[i][0] = A[i][q];

  double** db = matrix_multiplication(invB, matrix_opposite(Aq, m, 1), m, m, 1);

  // Detectem problema il·limitat
  bool ili = true;
  for (int i = 0; i < m; ++i)
    if (db[i][0] < 0) {
      ili = false;
      break;
    }

  if (ili) {
    printf("[simplexP]     Iteracio %4d : Problema il.limitat detectat.\n", niter);
    return 2;
  }

  // Calculem valor de theta
  double theta = -1;
  int p = -1;
  int indexp = -1;

  for (int i = 0; i < m; ++i)
    if (db[i][0] < 0) {
      double promisingtheta = -xb[i][0]/db[i][0];
      if (promisingtheta < theta || theta == -1) {
        theta = promisingtheta;
        indexp = i;
        p = vb[i];
      }
    }

  // Fem actualitzacions:
  vb[indexp] = q;
  vn[indexq] = p;

  xb = matrix_addition(xb, matrix_escalate(theta, db, m, 1), m, 1);
  xb[indexp][0] = theta;
  z += theta*r[indexq][0];
  actualitza_inversa(invB, db, indexp, m);

  // Detectem SBF degenerada, en cas que no estiguem utilitzant Bland,
  // perque aixo podria fer que el nostre algorisme es quedes buclat
  if (theta == 0 && !bland) {
    printf("[simplexP]     Iteracio %4d : Solucio Basica Factible Degenerada detectada, no estem utilitzant la regla de Bland aixi que parem perque podria entrar en loop.\n", niter);
    print_matrix(xb, m, 1);
    cout << "(p, q) = (" << p << ", " << q << ")\n";
    return 3;
  }

  printf("[simplexP]     Iteracio %4d : q = %3d, rq = %9.3f, B(p) = %3d, theta* = %9.3f, z = %9.3f\n", niter, q+1, r[indexq][0], p+1, theta, z);

  return 0;
}
