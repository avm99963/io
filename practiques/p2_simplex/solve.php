<?php
/** Script que serveig com a test per tots els casos publics
  * (en el fitxer de dades originals), on hi ha un exemple de
  * les iteracions del Simplex.
  *
  * Basicament compara el valor z* de l'exemple amb el que dona
  * el nostre programa.
  */

// Configuracio:
$folder = "data_octave/"; // Carpeta on estan les dades generades
$save_folder = "solutions/"; // Carpeta on volem guardar les solucions

if (file_exists($save_folder)) {
  die("Ja existeix la carpeta '".$save_folder."'. Esborra-la per poder guardar les solucions alla.\n");
}

mkdir($save_folder);

echo "Benvolgut a l'ajudant per solucionar els problemes!\n\nEscriu els alumnes dels quals vols resoldre els problemes, separats amb comes (p. ex: 44, 79): ";
$problemes = array_map('intval', explode(",", fgets(STDIN)));

for ($bland = 0; $bland <= 1; ++$bland) {
  foreach ($problemes as $t) {
    for ($i = 1; $i <= 4; ++$i) {
      $t_file = "{$folder}{$t}/prob{$i}_";

      $output = [];
      $return;
      exec("./simplex {$t_file}A.dat {$t_file}b.dat {$t_file}c.dat ".($bland ? "bland" : "rmin"), $output, $return);
      $outputtxt = implode($output, "\n")."\n";
      if ($return != 0) {
        die("Hi ha hagut un error desconegut amb l'alumne $t i problema $i (error ".$return.").\n");
      }
      echo "Guardant el problema {$i} de l'alumne {$t} fet amb la regla '".($bland ? "bland" : "rmin")."'\n";
      file_put_contents($save_folder."alumne{$t}_prob{$i}_".($bland ? "bland" : "rmin")."_output.txt", $outputtxt);
    }
  }
}

echo "Ja hem acabat!\n";
