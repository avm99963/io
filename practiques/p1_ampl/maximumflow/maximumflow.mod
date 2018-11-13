# Maximum flow problem
param n; # Number of nodes
set NODES:=1..n;
set ARCS within {NODES,NODES};
param capacity{ARCS}>=0;
var x {(i,j) in ARCS}>=0,<=capacity[i,j];

# Objective function
maximize total_flow:
  x[n,1];

# Constraints
subject to nodes_const{k in NODES}:
  (sum{(k,j)in ARCS}x[k,j] - sum{(i,k)in ARCS} x[i,k]) = 0;
