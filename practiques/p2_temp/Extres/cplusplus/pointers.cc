#include <iostream>
#include <cmath>
using namespace std;

void print_vector(double* v, int n) {
  for (int i = 0; i < n; ++i) cout << v[i] << (i < n-1 ? " " : "");
  cout << "\n";
}

void print_vector(int* v, int n) {
  for (int i = 0; i < n; ++i) cout << v[i] << (i < n-1 ? " " : "");
  cout << "\n";
}

void print_matrix(double** M, int n, int m) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << M[i][j] << (j < m-1 ? " " : "");
    }
    cout << "\n";
  }
}

void intercanvia(double** a, int n, int i, int j) {
  swap(a[i], a[j]); // New and better implementation
  //for (int k = 0; k < n; ++k) swap(a[i][k], a[j][k]); // Old implementation
}

// m: files m1, n: columnes m1/files m2, k: columnes m2
double** matrix_multiplication(double** m1, double** m2, int m, int n, int k) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(k, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      for (int k = 0; k < n; ++k) {
        r[i][j] += m1[i][k]*m2[k][j];
      }
    }
  }
  return r;
}

// return m1 - m2
double** matrix_subtraction(double** m1, double** m2, int m, int n) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(n, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j)
      r[i][j] = m1[i][j] - m2[i][j];
  }

  return r;
}

// return m1+m2
double** matrix_addition(double** m1, double** m2, int m, int n) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(n, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j)
      r[i][j] = m1[i][j] + m2[i][j];
  }

  return r;
}

double** matrix_transpose(double** M, int n, int m) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(n, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
       r[j][i] = M[i][j];

  return r;
}

double** matrix_opposite(double** M, int n, int m) {
  double** r;
  r = (double**) calloc(n, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < n; ++i) {
    r[i] = (double*) calloc(m, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
       r[i][j] = -M[i][j];

  return r;
}

double** matrix_escalate(double lambda, double** M, int n, int m) {
  double** r;
  r = (double**) calloc(n, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < n; ++i) {
    r[i] = (double*) calloc(m, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
       r[i][j] = lambda*M[i][j];

  return r;
}

double** copia_punter(double** a, int m, int n) {
  double** r;
  r = (double**) calloc(m, sizeof(double*));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  for (int i = 0; i < m; ++i) {
    r[i] = (double*) calloc(n, sizeof(double));
    if (r[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) r[i][j] = a[i][j];
  }

  return r;
}

double** create_pointer(int n, int m) {
  double** A;
  A = (double**) calloc(n, sizeof(double*));
  if (A == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }

  for (int i = 0; i < n; ++i) {
    A[i] = (double*) calloc(m, sizeof(double));
    if (A[i] == NULL) {
      cerr << "Error: memoria insuficient.\n";
      exit(1);
    }
    for (int j = 0; j < m; ++j) A[i][j] = 0;
  }

  return A;
}

double* create_pointer(int n) {
  double* v;
  v = (double*) calloc(n, sizeof(double));
  if (v == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }

  return v;
}

int* create_pointer_int(int n) {
  int* v;
  v = (int*) calloc(n, sizeof(int));
  if (v == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }

  return v;
}


double* copia_punter(double* v, int n) {
  double* r;
  r = (double*) calloc(n, sizeof(double));
  if (r == NULL) {
    cerr << "Error: memoria insuficient.\n";
    exit(1);
  }
  
  for (int i = 0; i < n; ++i) r[i] = v[i];

  return r;
}

double norma_m1(double** m, int n) {
  double max = -1;
  for (int j = 0; j < n; ++j) {
    double sum = 0;
    for (int i = 0; i < n; ++i) sum += abs(m[i][j]);
    if (sum > max) max = sum;
  }
  return max;
}

double norma_minf(double** m, int n) {
  double max = -1;
  for (int i = 0; i < n; ++i) {
    double sum = 0;
    for (int j = 0; j < n; ++j) sum += abs(m[i][j]);
    if (sum > max) max = sum;
  }
  return max;
}

double norma_1(double* v, int n) {
  double norma;
  for (int i = 0; i < n; ++i) norma += abs(v[i]);
  return norma;
}

double norma_inf(double* v, int n) {
  double max = -1;
  for (int i = 0; i < n; ++i) {
    if (abs(v[i]) > max) max = abs(v[i]);
  }
  return max;
}
