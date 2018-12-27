#!/bin/sh
gnuplot << END

#set terminal png size 2160,1440
set terminal png size 1440,1440
set output "grafiques.png"
set key off
set title "Braquistòcrona"
show title
set xlabel "X"
set ylabel "Y"

plot [0:1][0:1] "plot.dat" with lines linewidth 3
#plot [0:1][0:1] "plot.dat" using 2:1 with points

END

