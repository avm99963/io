% Simplex Primal
function [vb, vn, xb, z, invB, iout] = simplex_primal(c, A, invB, b, vb, vn, xb, z, bland, niter, faseII)
tol = 10^-12;

cn = c(vn, :);
cb = c(vb, :);
B = A(:, vb);
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

q = -1;
keyqit = 0;
keyq = -1;

if (bland)
  for i = vn
    keyqit++;
    if (r(keyqit) < 0 && (i < q || q == -1))
      keyq = keyqit;
      q = i;
    endif
  endfor
else
  [rq, keyq] = min(r);
  q = vn(keyq);
end

db = -invB*A(:, q);

% COPIAT PPT
if (min(db) >= -tol)
  printf('[simplexP]     Iteracio %4d : Problema il.limitat detectat.\n', niter);
  iout = 2; % Problema il·limitat detectat
  return;
end

if (0 == 1)
  vtheta = -xb./db;
  [theta, keyp] = min(vtheta(db < 0));
  p = vb(keyp);
  p
  vtheta
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
invB = actualitzacio_inversa(invB, db, keyp);

% COPIAT PPT
if (theta == 0 && !bland)
  printf('[simplexP]     Iteracio %4d : Solucio Basica Factible Degenerada detectada, no estem utilitzant la regla de Bland aixi que parem perque podria entrar en loop.\n', niter);
  iout = 3; % SBF degenerada
  return;
end

iout = 0;

printf('[simplexP]     Iteracio %4d : q = %3d, rq = %9.3f, B(p) = %3d, theta* = %9.3f, z = %9.3f\n', niter, q, r(keyq), p, theta, z);

endfunction
