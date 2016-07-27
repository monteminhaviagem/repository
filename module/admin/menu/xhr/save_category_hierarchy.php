<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_menu."/dm/Menu.inc");

use module\admin\menu\dm\Menu;

$data = array();
$stat = array();

function _save_hierarchy($category, $parent_id = 2) {
	for ($i=0; $i<count($category); $i++) {
		$data["parent_id"] = $parent_id;
		$data["id"] = $category[$i]["id"];
		$data["last_updated"] = $_SESSION['user_id'];
		$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";
		
		$dm = new Menu();
		$dm->set_category_hierarchy(
			$data,
			$stat
		);
		
		if ($stat["success"] == "false") {
			echo json_encode($stat);
			return;
		}
		
		if (isset($category[$i]["children"]))
			_save_hierarchy($category[$i]["children"], $category[$i]["id"]);
	}
}

$category = json_decode($_POST["category"],true);

_save_hierarchy($category);

$stat["success"] = "true";
$stat["message"] = "";

echo json_encode($stat);

?>