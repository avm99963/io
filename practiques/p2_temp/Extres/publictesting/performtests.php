<?php
/** Script que serveig com a test per tots els casos publics
  * (en el fitxer de dades originals), on hi ha un exemple de
  * les iteracions del Simplex.
  *
  * Basicament compara el valor z* de l'exemple amb el que dona
  * el nostre programa.
  */

// Configuracio:
$folder_octave = "Extres/data_octave/"; // Carpeta on estan les dades generades per Octave
$folder_cc = "Extres/data_cplusplus/"; // Carpeta on estan les dades generades per C++
$solutions_file = "Extres/solutions.json"; // Fitxer json on tenim les solucions dels exemples (generat per exportsolutions.php)

if ($argc < 3) die("\n== Utilitzacio del programa de testeig de casos publics ==\n\nExecuta el programa amb la seguent comanda des del directori principal: \"php publictesting/performtests.php variant taxacio\", on variant es el programa que es vol usar (octave si es vol usar la implementacio a l'Octave o cc si es vol usar la implementacio al C++) i taxacio es el metode de taxacio que usara el simplex (bland o rmin).\n");
$bland = ($argv[2] == "bland");
$octave = ($argv[1] == "octave");
$folder = ($octave ? $folder_octave : $folder_cc);

echo "Test dels casos públics\n\n";

$solutions = json_decode(file_get_contents($solutions_file), true);

$accepted = 0;

$testcases = 79;
for ($t = 1; $t <= $testcases; ++$t) {
  $t_file = $folder.$t."/prob1_";

  $output = [];
  $return;
  exec(($octave ? "./simplex" : "Extres/cplusplus/program")." {$t_file}A.dat {$t_file}b.dat {$t_file}c.dat ".($bland ? "bland" : "rmin"), $output, $return);
  //echo implode($output, "\n")."\n";
  if ($return != 0) {
    die("Hi ha hagut un error desconegut amb l'alumne $t (error ".$return.").\n");
  }
  preg_match('/ptima trobada.+z = ([\d\-\.]+)/', implode("\n", $output), $matches);
  if (!isset($matches[1])) {
    if (preg_match('/Solucio Basica Factible Degenerada detectada/', implode("\n", $output))) echo "Alumne ".$t.": Solucio Basica Factible Degenerada detectada; EE\n";
    else die("No s'ha pogut determinar el valor de la funcio optima. Aquest es l'output:\n\n".implode($output, "\n"));
  } else {
    $ok = ($matches[1] - $solutions[$t] < 1e-6);
    if ($ok) $accepted++;
    echo "Alumne ".$t.": Programa: ".$matches[1]."; Real: ".$solutions[$t]."; ".($ok ? "AC" : "WA")."\n";
  }
}

echo "Resultat: hem obtingut ".$accepted."/".$testcases." respostes correctes.\n";
