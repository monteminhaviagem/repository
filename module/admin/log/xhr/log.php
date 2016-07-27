<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");

$file_name = $_POST["file_name"] ?? "";

if ($file_name != "") {
	if (file_exists($path_log . "/" . $file_name)) {
		$file = fopen($path_log . "/" . $file_name, "r");
		
		$out = fgets($file);
		
		while(!feof($file)) {
			$out .= fgets($file);
		}
		
		fclose($file);
		echo $out;
	}
}

?>