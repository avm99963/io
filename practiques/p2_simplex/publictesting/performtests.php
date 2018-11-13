<?php
// Fitxer que serveig com a test
$folder = "publictesting/simplextest";

echo "Test dels casos públics\n\n";

$solutions = json_decode(file_get_contents("solutions.json"), true);

if (file_exists($folder)) {
  die("Ja existeix la carpeta ".$folder.". Esborra-la i torna a executar el programa.\n");
}

mkdir($folder);

$accepted = 0;

$testcases = 79;
for ($t = 1; $t <= $testcases; ++$t) {
  if (file_exists($folder."/A.dat")) unlink($folder."/A.dat");
  copy("data_octave/".$t."/prob1_A.dat", $folder."/A.dat");
  if (file_exists($folder."/b.dat")) unlink($folder."/b.dat");
  copy("data_octave/".$t."/prob1_b.dat", $folder."/b.dat");
  if (file_exists($folder."/c.dat")) unlink($folder."/c.dat");
  copy("data_octave/".$t."/prob1_c.dat", $folder."/c.dat");

  $output = [];
  $return;
  exec("octave simplex.m 2> /dev/null", $output, $return);
  //echo implode($output, "\n")."\n";
  if ($return != 0) {
    die("Hi ha hagut un error desconegut amb l'alumne $t (error ".$return.").\n");
  }
  preg_match('/ptima trobada.+z = ([\d\-\.]+)/', implode("\n", $output), $matches);
  if (!isset($matches[1])) {
    die("No s'ha pogut determinar el valor de la funcio optima. Aquest es l'output:\n\n".implode($output, "\n"));
  }
  $ok = ($matches[1] - $solutions[$t] < 1e-6);
  if ($ok) $accepted++;
  echo "Alumne ".$t.": Programa: ".$matches[1]."; Real: ".$solutions[$t]."; ".($ok ? "AC" : "WA")."\n";
}

echo "Resultat: hem obtingut ".$accepted."/".$testcases." respostes correctes.\n";
