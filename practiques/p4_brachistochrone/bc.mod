# Problema de la Brachistocrona
param n; # Nombre de punts
param a;
param b;

set PUNTS:= 0..n;
param x {i in PUNTS};

var y {i in PUNTS};

# Funcio objectiu
minimize time_elapsed:
  (1/sqrt(2*9.8)) * (sum{i in 0..(n-1)}(sqrt((1 + (( y[i+1] - y[i] )/( x[i+1] - x[i] ))^2 )/max(y[i], 1e-5))*(x[i+1] - x[i]) ));

# Constraints
subject to inici:
  y[0] = 0;
subject to terme:
  y[n] = b;
#subject to nonzero{k in 1..n}:
#  y[k] >= 1e-10
