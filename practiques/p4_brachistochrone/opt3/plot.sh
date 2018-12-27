#!/bin/sh
gnuplot << END

#set terminal png size 2160,1440
set terminal svg size 1000,1000
set output "grafiques.svg"
set key off
set title "Braquistòcrona"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][0:1] "plot.dat" with dots# linewidth 3
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

