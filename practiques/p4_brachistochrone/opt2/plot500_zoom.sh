#!/bin/sh
gnuplot << END

set terminal png size 1000,1000
set output "grafiques500_2_zoom.png"
set key on
set title "Braquistòcrona (model 2, n = 500 punts)"
show title
set xlabel "X"
set ylabel "Y"

plot [0.2:0.23][0.45:0.42] "../brac.dat" w lines title "Solució analítica", "plotuniform500.dat" w lines title "Uniforme", "plotquad500.dat" w lines title "Quadràtica"
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

