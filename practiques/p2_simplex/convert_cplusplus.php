<?php
// Constants:
$folder = "data_cplusplus"; // Folder in which the converted data is going to be saved

function write_matrix($m, &$file) {
  fwrite($file, count($m)." ".count($m[0])."\n");
  foreach ($m as $r)
    foreach ($r as $i => $e) fwrite($file, $e."\n");
}

function finish_problem($write = true) {
  global $data;
  global $row;
  global $reading;
  global $folder;
  global $est;
  global $prob;

  if ($write) {
    $basefolder = $folder.DIRECTORY_SEPARATOR.$est.DIRECTORY_SEPARATOR;
    $filec = fopen($basefolder."prob".$prob."_c.dat", "w");
    write_matrix($data['c'], $filec);
    fclose($filec);
    $filea = fopen($basefolder."prob".$prob."_A.dat", "w");
    write_matrix($data['A'], $filea);
    fclose($filea);
    $fileb = fopen($basefolder."prob".$prob."_b.dat", "w");
    write_matrix($data['b'], $fileb);
    fclose($fileb);
  }

  $data = array(
    'c' => [],
    'A' => [],
    'b' => []
  );
  $row = 0;
  $reading = false;
}

if (file_exists($folder)) {
  die("Sorry, the folder or file $folder already exists.\n");
}
mkdir($folder);

$est = 0;
$prob = 0;
$start = false;
$reading = false;
while ($input = fgets(STDIN)) {
  $input = trim($input);
  if (empty($input)) continue;
  if ($input[0] == ':') {
    if ($start == false) {
      finish_problem(($est > 0));

      $prob = 0;
      ++$est;
      $start = true;
      mkdir($folder.DIRECTORY_SEPARATOR.$est);
    }
  } else {
    $start = false;
    if ($input[0] == 'P') {
      finish_problem(($prob > 0));

      $prob++;
    } elseif ($input[0] == 'c' || $input[0] == 'A' || $input[0] == 'b') {
      if (!count($data[$input[0]])) {
        $reading = true;
        $readingvar = $input[0];
        $row = 0;
      } else $reading = false;
    } elseif ($reading) {
      if ($input[0] == 'C') $row = 0;
      elseif (($input[0] == '-' && $input[1] == '-') || $input[0] == '[') {
        $reading = false;
      } else {
        $explode = array_map('intval', preg_split("/\s+/", $input));
        if (!isset($data[$readingvar][$row])) $data[$readingvar][$row] = [];
        $data[$readingvar][$row] = array_merge($data[$readingvar][$row], $explode);
        $row++;
      }
    }
  }
}

finish_problem(($prob > 0));
