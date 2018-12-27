#!/bin/sh
gnuplot << END

set terminal png size 1000,1000
set output "grafiquesuniforme.png"
set key on
set title "Braquistòcrona (model 1, uniforme)"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][1:0] "../brac.dat" w lines title "Solució analítica", "plotuniform500.dat" w lines title "Uniforme (500 punts)", "plotuniform1000.dat" w lines title "Uniforme (1000 punts)"
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

