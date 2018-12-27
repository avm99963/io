#!/bin/sh
gnuplot << END

#set terminal png size 2160,1440
set terminal svg size 1440,1440
set output "grafiques.svg"
set key off
set title "Braquistòcrona"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][-0.2:1.2] "../brac.dat" with dots, "plot.dat" with dots
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

