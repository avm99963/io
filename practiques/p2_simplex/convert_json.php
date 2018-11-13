<?php
// Constants:
$folder = "data_json"; // Folder in which the converted data is going to be saved

function finish_problem($write = true) {
  global $data;
  global $row;
  global $reading;
  global $folder;
  global $est;
  global $prob;

  if ($write) {
    $file = fopen($folder.DIRECTORY_SEPARATOR.$est.DIRECTORY_SEPARATOR.$prob.".json", "w");
    fwrite($file, json_encode($data));
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
