#!/bin/sh
gnuplot << END

set terminal png size 1000,1000
set output "masterplot.png"
set key on
set title "Braquistòcrona (n = 1000 punts)"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][1:0] "brac.dat" w lines title "Solució analítica", "opt1/plotuniform1000.dat" w lines title "Model 1 (uniforme)", "opt2/plotuniform1000.dat" w lines title "Model 2 (uniforme)", "opt3/plot1000.dat" w lines title "Model 3"
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

