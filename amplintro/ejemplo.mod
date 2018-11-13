set PRODUCTOS;
set RECURSOS;

param beneficio{PRODUCTOS}>=0;

param recursos_requeridos{PRODUCTOS, RECURSOS} >=0;
param max_recurso{RECURSOS} >=0;

var X {PRODUCTOS}>=0, integer;

# Función objetivo

maximize total:
	sum {i in PRODUCTOS} (beneficio[i]*X[i]);

# Restricciones

# Recursos
subject to recursos_disponibles {j in RECURSOS}:
   sum {i in PRODUCTOS} (recursos_requeridos[i,j]*X[i]) <= max_recurso[j];
   
