<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_version."/dm/Version.inc");

use module\admin\version\dm\Version;

$args = array();
$data = array();
$return = array();

$dm = new Version();
$dm->get_version(
	$args,
	$data
);

$return["data"] = array();

for ($i = 0; $i<count($data); $i++) {
	if ($data[$i]["current"] == "N")
		$version_current = " <span class=\"text-highlight-dark\">Não</span>";
	else
		$version_current = " <span class=\"text-highlight-green\">Sim</span>";
	
	$created = date("d/m/Y - H:i:s",$data[$i]["created"]);
	$checkout = date("d/m/Y - H:i:s",$data[$i]["checkout"]);
	
	$return["data"][] = Array($data[$i]["id"],$data[$i]["tag"],$created,$checkout,$version_current);
}

echo json_encode($return, JSON_UNESCAPED_UNICODE);

?>