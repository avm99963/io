clear all;
format long;

global a
global b
a = 1/2;
b = 1;

%y = r(t - sin(t))
%x = r(1 - cos(t))

fun = @freturn;

x0 = [1 1];
x = fsolve(fun, x0)

