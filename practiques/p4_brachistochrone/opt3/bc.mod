# Problema de la Brachistocrona
param n; # Nombre de punts
param a;
param b;

set PUNTS:= 0..n;
var x {i in PUNTS} := a*i/n;
var y {i in PUNTS};

# Funcio objectiu
minimize time_elapsed:
  (1/sqrt(2*9.8)) * (sum{i in 0..(n-1)}(sqrt( ((x[i+1] - x[i])^2 + (y[i+1] - y[i])^2)/max(y[i], 1e-12) )));

# Constraints
subject to inici:
  x[0] = 0;
subject to inici2:
  y[0] = 0;
subject to terme:
  x[n] = a;
subject to terme2:
  y[n] = b;
subject to creixement{i in 1..n}:
  x[i] >= x[i-1] + 1e-8;
subject to creixement2{i in 1..n}:
  y[i] >= y[i-1] + 1e-8;
