# Problema de flujo de coste mínimo
#Número de nodos
param n;
set NODES:=1..n;
set ARCS within {NODES,NODES};
param flow{NODES};
param cost{ARCS}>=0;
var x {(i,j) in ARCS}>=0;
#Función objectivo
minimize total_cost:
sum{(i,j) in ARCS} cost[i,j]*x[i,j];
# Restricciones
subject to res_nodos{k in NODES}:
(sum{(k,j)in ARCS}x[k,j]-sum{(i,k)in ARCS} x[i,k])=flow[k];
