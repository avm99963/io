<?php
$input = file_get_contents("php://stdin");

preg_match_all('/^\[jh_simplexP\]     Soluci.+, iteraci.+, z = ([0-9\-.]+)/m', $input, $matches);

$solutions = [];
foreach ($matches[1] as $i => $sol) {
  $solutions[$i+1] = (double)$sol;
}

echo json_encode($solutions)."\n";
