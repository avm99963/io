% Simplex Primal
function [vb, vn, xb, z, iout] = simplex_primal(c, A, b, vb, vn, xb, z, bland, niter, faseII)
tol = 10^-12;

cn = c(vn, :);
cb = c(vb, :);
B = A(:, vb);
invB = inv(B);
An = A(:, vn);

r = (cn' - cb'*invB*An)';

% COPIAT PP
if (min(r) >= 0)
  if (faseII)
    printf('[simplexP]     Iteracio %4d : Solucio optima trobada! z = %9.6f\n', niter, z);
  else
    printf('[simplexP]     Iteracio %4d : Solucio Basica Factible trobada!\n', niter);
  end
  iout = 1; % Es una SBF òptima
  return;
end

if (bland)
  q = -1;
  keyqit = 0;
  keyq = -1;
  for i = vn % Regla de bland (ens ha sortit de casualitat)
    keyqit++;
    if (r(keyqit) < 0 && (i < q || q == -1))
      keyq = keyqit;
      q = i;
    endif
  endfor
else
  minrq = 0;
  minkeyq = 0;
  for i = vn
    keyq++;
    if (r(keyq) < minrq)
      q = i;
      minrq = r(keyq);
      minkeyq = keyq;
    endif
  endfor
  keyq = minkeyq;
end

db = -invB*A(:, q);

% COPIAT PPT
if (min(db) >= -tol)
  printf('[simplexP]     Iteracio %4d : Problema il.limitat detectat.\n', niter);
  iout = 2; % Problema il·limitat detectat
  return;
end

theta = -1;
p = -1;
keypit = 0;
keyp = -1;

for bel = vb
  keypit++;
  if (db(keypit) < 0)
    promisingtheta = -xb(keypit)/db(keypit);
    if (promisingtheta < theta || theta == -1)
      theta = promisingtheta;
      keyp = keypit;
      p = bel;
    endif
  endif
endfor

vb(keyp) = q;
vn(keyq) = p;

xb += theta*db;
xb(keyp) = theta;
z += theta*r(keyq);
xb;

% COPIAT PPT
if (theta == 0 && !bland)
  printf('[simplexP]     Iteracio %4d : Solucio Basica Factible Degenerada detectada, no estem utilitzant la regla de Bland aixi que parem perque podria entrar en loop.\n', niter);
  iout = 3; % SBF degenerada
  return;
end

iout = 0;

printf('[simplexP]     Iteracio %4d : q = %3d, rq = %9.3f, B(p) = %3d, theta* = %9.3f, z = %9.3f\n', niter, q, r(keyq), p, theta, z);

endfunction
