clear all
format short;
format compact;
tol = 10^-12;

% Aqui configurem si volem usar regla de Bland (true) o costos reduits minims (false)
bland = true;

if (bland)
  disp('[simplexP] Inici simplex primal amb regla de Bland');
else
  disp('[simplexP] Inici simplex primal amb regla de costos reduits minims');
end

% Carreguem la matriu A i els vectors b i c
A = load('data_octave/79/prob4_A.dat');
b = load('data_octave/79/prob4_b.dat');
c = load('data_octave/79/prob4_c.dat');
%A = load('publictesting/simplextest/A.dat');
%b = load('publictesting/simplextest/b.dat');
%c = load('publictesting/simplextest/c.dat');
[m, bu] = size(b);
[n, cu] = size(c);
A = reshape(A, n, m)';

% Fase I del Símplex, configurem les variables que usarem
disp('[simplexP]   Fase I');
AI = [A eye(m)];
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
  [vb, vn, xb, z, ioutI] = simplex_primal(cI, AI, b, vb, vn, xb, z, bland, niterI, false);
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
    [vb, vn, xb, z, iout] = simplex_primal(c, A, b, vb, vn, xb, z, bland, niter, true);
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
