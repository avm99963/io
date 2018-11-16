void print_vector(double* v, int n);
void print_vector(int* v, int n);
void print_matrix(double** M, int n, int m);
void intercanvia(double **a, int n, int i, int j);
double** matrix_multiplication(double** m1, double** m2, int m, int n, int k);
double** matrix_subtraction(double** m1, double** m2, int m, int n);
double** matrix_addition(double** m1, double** m2, int m, int n);
double** matrix_transpose(double** M, int n, int m);
double** matrix_opposite(double** M, int n, int m);
double** matrix_escalate(double lambda, double** M, int n, int m);
double** copia_punter(double** a, int m, int n);
double* copia_punter(double* v, int n);
double** create_pointer(int n, int m);
double* create_pointer(int n);
int* create_pointer_int(int n);
double norma_m1(double** m, int n);
double norma_minf(double** m, int n);
double norma_1(double* v, int n);
double norma_inf(double* v, int n);
