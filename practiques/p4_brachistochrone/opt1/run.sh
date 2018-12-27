#!/bin/sh
./altregen $1 1 1 > bc.dat
ampl bc.run
sh plot.sh
