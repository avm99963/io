int simplex_primal(double** c, double** A, double** &invB, double** b, int* &vb, int* &vn, double** &xb, double &z, bool bland, int &niter, bool faseII, int n, int m);
double** actualitza_inversa(double** &invB, double** db, int keyp, int m);
