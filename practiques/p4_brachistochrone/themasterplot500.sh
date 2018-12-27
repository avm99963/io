#!/bin/sh
gnuplot << END

set terminal png size 1000,1000
set output "masterplot500.png"
set key on
set title "Braquistòcrona (n = 500 punts)"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][1:0] "brac.dat" w lines title "Solució analítica", "opt1/plotuniform500.dat" w lines title "Model 1 (uniforme)", "opt2/plotuniform500.dat" w lines title "Model 2 (uniforme)", "opt3/plot500.dat" w lines title "Model 3"
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

