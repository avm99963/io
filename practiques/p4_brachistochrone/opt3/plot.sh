#!/bin/sh
gnuplot << END

#set terminal png size 2160,1440
set terminal png size 1000,1000
set output "grafiques.png"
set key off
set title "Braquistòcrona (model 3, n = 500 punts)"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][1:0] "../brac.dat" with dots title "Solució analítica", "plot500.dat" with dots title "Model 3"
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

