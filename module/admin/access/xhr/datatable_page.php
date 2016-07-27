<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/Page.inc");

use module\admin\access\dm\Page;

$args = array();
$data = array();
$return = array();

$dm = new Page();
$dm->get_page(
	$args,
	$data
);

$return["data"] = array();

for ($i = 0; $i<count($data); $i++) {
	if ($data[$i]["page_type_id"] == 1)
		$color = "green";
	else if ($data[$i]["page_type_id"] == 2)
		$color = "blue";
	else if ($data[$i]["page_type_id"] == 3)
		$color = "dark";
	
	$page_type_name = " <span class=\"text-highlight-{$color}\">{$data[$i]["page_type_name"]}</span>";
	
	$return["data"][] = Array($data[$i]["id"],$data[$i]["name"],$data[$i]["url"],$page_type_name);
}

echo json_encode($return, JSON_UNESCAPED_UNICODE);

?>