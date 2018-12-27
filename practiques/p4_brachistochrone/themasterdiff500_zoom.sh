#!/bin/sh
gnuplot << END

set terminal png size 1000,1000
set output "masterdiff500_zoom.png"
set key on
set title "Comparació de la braquistòcrona"
show title
set xlabel "X"
set ylabel "Y"

plot [0.2:0.23][0.45:0.42] "brac.dat" w lines title "Solució analítica", "opt2/plotquad1000.dat" w lines title "Model 2 (quadràtica,n = 1000)", "opt3/plot500.dat" w lines title "Model 3 (n = 500)"
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

