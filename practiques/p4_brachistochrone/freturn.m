function F = freturn(x) % x(1) = r, x(2) = t
global a
global b
F(1) = x(1)*(x(2) - sin(x(2))) - a;
F(2) = x(1)*(1 - cos(x(2))) - b;
