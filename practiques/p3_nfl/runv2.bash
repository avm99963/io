#!/bin/bash
pn=$1
pr=$2
ps=$3
jmin=$(( (pn/2)*(pr+ps) - pr - 1 ))
rm -f ampl_result.out

while [ ! -f ampl_result.out ]
do
  ((jmin++))
  echo "Provant amb jmin=$jmin"
  echo "Generant fitxer de dades..."
  rm -f nflv2.dat
  ./datageneratorv2 $pn $pr $ps $jmin
  echo "Executant ampl..."
  ampl nflv2.run
done

echo "Hem trobat la minima solucio amb $jmin jornades"
./prettycalendar < ampl_result.out
