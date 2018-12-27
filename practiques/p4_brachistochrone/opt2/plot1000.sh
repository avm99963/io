#!/bin/sh
gnuplot << END

set terminal png size 1000,1000
set output "grafiques1000.png"
set key on
set title "Braquistòcrona (model 2, n = 1000 punts)"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][1:0] "../brac.dat" w lines title "Solució analítica", "plotuniform1000.dat" w lines title "Uniforme", "plotquad1000.dat" w lines title "Quadràtica"
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

