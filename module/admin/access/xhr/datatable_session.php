<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/Session.inc");

use module\admin\access\dm\Session;

$args = array();
$data = array();
$return = array();

$dm = new Session();
$dm->get_session_active(
	$args,
	$data
);

$return["data"] = array();

for ($i = 0; $i<count($data); $i++) {
	if ($data[$i]["user_type_id"] == 1)
		$color = "dark";
	else if ($data[$i]["user_type_id"] == 2)
		$color = "blue";
	else if ($data[$i]["user_type_id"] == 3)
		$color = "green";
	else if ($data[$i]["user_type_id"] == 4)
		$color = "red";
	
	$user_type_name = " <span class=\"text-highlight-{$color}\">{$data[$i]["user_type_name"]}</span>";
	
	$return["data"][] = Array($data[$i]["id"],$data[$i]["user_name"],$user_type_name,$data[$i]["token"]);
}

echo json_encode($return, JSON_UNESCAPED_UNICODE);

?>