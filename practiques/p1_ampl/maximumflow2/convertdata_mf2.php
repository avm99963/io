<?php
for ($i = 0; $i < 4; $i++) {
  fgets(STDIN);
}

$array = array();
$input;
do {
  $input = trim(fgets(STDIN));
  if (!empty($input)) {
    $array[] = str_split(($input[0] == "-" ? "" : " ").$input, 2);
  }
} while (!empty($input));

echo "param n:=".count($array).";\n";

$bl = trim(fgets(STDIN));
preg_match('/\( (.*)\)/', $bl, $be);
$bb = explode(", ", $be[1]);

$cl = trim(fgets(STDIN));
preg_match('/\( (.*)\)/', $cl, $ce);
$c = explode(", ", $ce[1]);

echo "param: ARCS: capacity:=";
for ($i = 0; $i < count($array[0]); ++$i) {
  $a = -1;
  $b = -1;
  for ($j = 0; $j < count($array); ++$j) {
    if ($a > -1 && $b > -1) break;
    if ($array[$j][$i] == " 1") $a = $j;
    if ($array[$j][$i] == "-1") $b = $j;
  }
  if ($a == -1 || $b == -1) echo "\n#SOMETHING WENT VERY WRONG";
  echo "\n".($a+1)." ".($b+1)." ".$bb[$i];
}
echo ";\n";

