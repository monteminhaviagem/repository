<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_menu."/dm/Menu.inc");

use module\admin\menu\dm\Menu;

$args = array();
$data = array();
$return = array();

$args["include_page"] = "true";

$dm = new Menu();
$dm->get_link(
	$args,
	$data
);

$return["data"] = array();

for ($i = 0; $i<count($data); $i++) {
	$return["data"][] = Array($data[$i]["id"],$data[$i]["name"],$data[$i]["page"]["name"],$data[$i]["page"]["url"]);
}

echo json_encode($return, JSON_UNESCAPED_UNICODE);

?>