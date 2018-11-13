# Maximum flow problem
param n; # Number of nodes
set NODES:=1..n;
set ARCS within {NODES,NODES};
param capacity{ARCS}>=0;
var x {(i,j) in ARCS}>=0,<=capacity[i,j];

# Objective function
maximize total_flow:
  sum{(1,i) in ARCS}x[1,i];

# Constraints
subject to nodes_const{k in 2..(n-1)}:
  (sum{(k,j)in ARCS}x[k,j] - sum{(i,k)in ARCS} x[i,k])=0;
subject to equal:
  (sum{(1,i) in ARCS}x[1,i] - sum{(i,n) in ARCS}x[i,n]) = 0;
