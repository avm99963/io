#!/bin/sh
./uniformgen $1 1 1 > bc.dat
ampl bc.run
sh plot.sh
