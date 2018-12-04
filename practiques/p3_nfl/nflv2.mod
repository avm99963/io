# Problema de la NFL
param n; # Nombre d'equips
param r; # Nombre de partits intradivisionals per cada equip
param s; # Nombre de partits interdivisionals per cada equip
param jactual; # Nombre de jornades

set EQUIPS:=1..n;
set JORNADES:=1..jactual;
set PARTITS within {EQUIPS,EQUIPS,JORNADES};
var x {(i, j, k) in PARTITS} binary;
param c {(i, j, k) in PARTITS};

# Funcio objectiu
maximize priority:
  sum{(i, j, k) in PARTITS}(c[i,j,k]*x[i,j,k]);

# Constraints
subject to partits_intraA_totals{i in 1..n/2, j in 1..n/2: i < j}:
  sum{k in JORNADES}x[i,j,k] = r;
  
subject to partits_intraB_totals{i in (n/2+1)..n, j in (n/2+1)..n: i < j}:
  sum{k in JORNADES}x[i,j,k] = r;

subject to partits_inter_totals{i in 1..n/2, j in (n/2+1)..n}:
  sum{k in JORNADES}x[i,j,k] = s;

subject to partits_per_jornada{i in EQUIPS, k in JORNADES}:
  (sum{j in 1..(i-1)}x[j,i,k]) + (sum{j in (i+1)..n}x[i,j,k]) <= 1;

#subject to no_juguis_amb_tu_mateix{i in EQUIPS, k in JORNADES}:
#  x[i,i,k] = 0;

