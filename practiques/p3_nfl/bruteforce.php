<?php
$nlessthan = 16;
$rlessthan = 7;
$slessthan = 7;

function shoulddoit($n, $r, $s) {
  return ($n % 4 == 0 || $s >= $r);
}

for ($n = 4; $n <= $nlessthan; $n += 2) {
  for ($r = 1; $r <= $rlessthan; $r++) {
    for ($s = 1; $s <= $slessthan; $s++) {
      $output = [];
      $return;
      
      exec("sh run.sh $n $r $s", $output, $return);
      
      $didit = (strpos(implode("\n", $output), "No es possible programar") === false);

      echo (!(shoulddoit($n, $r, $s) == $didit) ? "!!" : "  ")." ($n, $r, $s) (didit: ".($didit ? "true" : "false").", shoulddoit: ".(shoulddoit($n, $r, $s) ? "true" : "false").")\n";
    }
  }
}
