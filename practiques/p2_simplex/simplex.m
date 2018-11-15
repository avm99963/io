clear all
format short;
format compact;
tol = 10^-10;

if (nargin < 3)
  printf('=== Utilitzacio del programa ===\n\nExecuta "./simplex fileA fileb filec taxacio", on:\n* Els tres primers arguments son les rutes als arxius amb la matriu A i vectors b i c respectivament\n* taxacio és "bland" si vols utilitzar la regla de Bland o "rmin" si vols utilitzar la regla de costos reduits minims\n');
  exit(1);
end

arglist = argv();

% Aqui configurem si volem usar regla de Bland (true) o costos reduits minims (false)
bland = true;
if (nargin > 3)
  if (strcmp(arglist{4}, "rmin"))
    bland = false;
  else
    if (!strcmp(arglist{4}, "bland"))
      printf('ERROR: Has especificat un proces de taxacio no reconegut. Els unics implementats son "bland" i "rmin" (sense cometes).');
      exit(1);
    end
  end
end

if (bland)
  disp('[simplexP] Inici simplex primal amb regla de Bland');
else
  disp('[simplexP] Inici simplex primal amb regla de costos reduits minims');
end

% Carreguem la matriu A i els vectors b i c
A = load(arglist{1});
b = load(arglist{2});
c = load(arglist{3});
[m, bu] = size(b);
[n, cu] = size(c);
A = reshape(A, n, m)';

% Fase I del Símplex, configurem les variables que usarem
disp('[simplexP]   Fase I');
AI = [A eye(m)];
invB = eye(m);
cI = [zeros(n, 1); ones(m, 1)];
vb = (n+1):(n+m);
vn = 1:n;
xb = b;
z = cI(vb)'*xb;

% Iterem pel simplex primal
ioutI = 0;
niterI = 0;
while (ioutI == 0)
  niterI++;
  [vb, vn, xb, z, invB, ioutI] = simplex_primal(cI, AI, invB, b, vb, vn, xb, z, bland, niterI, false);
end

iout = -1;
% Si hem pogut trobar SBF a la fase I, continuem amb fase II
if (ioutI == 1 && abs(z) < tol)
  disp('[simplexP]   Fase II');
  % Eliminem les variables artificials del vector de variables no bas.
  corr = 0;
  for i = 1:n
    if (vn(i-corr) > n)
      vn(i-corr) = [];
      corr++;
    endif
  endfor

  % Actualitzem valor de z al corresponent a la SBF trobada
  z = c(vb)'*xb;

  % Iterem pel simplex primal
  iout = 0;
  niter = 0;
  while (iout == 0)
    niter++;
    [vb, vn, xb, z, invB, iout] = simplex_primal(c, A, invB, b, vb, vn, xb, z, bland, niter, true);
  end
else
  if (ioutI == 1)
    disp('[simplexP] El problema no es factible perque a la fase I hem vist z > 0.');
  else
  end
end

display('[simplexP] Fi simplex primal');
if (iout == 1)
  printf('VB* =\n');
  disp(vb);
  printf('\nxb* =\n');
  printf(' %8.4f', xb');
  printf('\n\nVNB* =\n');
  disp(vn);
  printf('\nz* = ');
  disp(z);
end
