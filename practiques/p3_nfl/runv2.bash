#!/bin/bash

# Definim les variables n, r, s i jmin
pn=$1
pr=$2
ps=$3
jmin=$(( (pn*(pr+ps))/2 - pr - 1 ))

# Eliminem el fitxer de resultats si existeix
rm -f ampl_result.out

# Mentre no existeixi el fitxer de resultats (es
# a dir, mentre no haguem trobat una solucio)
# itera incrementat cada iteracio la jmin per 1
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
