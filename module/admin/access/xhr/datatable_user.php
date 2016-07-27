<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/User.inc");
require_once($path_module_admin_access."/dm/UserType.inc");

use module\admin\access\dm\User;
use module\admin\access\dm\UserType;

$args = array();
$data = array();
$return = array();

$dm = new User();
$dm->get_user(
	$args,
	$data
);

$return["data"] = array();

for ($i = 0; $i<count($data); $i++) {
	if ($data[$i]["user_type_id"] == UserType::ADMIN)
		$color = "dark";
	else if ($data[$i]["user_type_id"] == UserType::PADRAO)
		$color = "blue";
	else if ($data[$i]["user_type_id"] == UserType::AGENCIA)
		$color = "green";
	else if ($data[$i]["user_type_id"] == UserType::VENDEDOR)
		$color = "red";
	
	$user_type_name = " <span class=\"text-highlight-{$color}\">{$data[$i]["user_type_name"]}</span>";
	
	$return["data"][] = Array($data[$i]["id"],$data[$i]["name"],$data[$i]["email"],$user_type_name,$data[$i]["profile_name"]);
}

echo json_encode($return, JSON_UNESCAPED_UNICODE);

?>