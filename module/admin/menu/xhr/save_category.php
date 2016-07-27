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

$data["id"] = (isset($_POST["id"]) && $_POST["id"] != "") ? $_POST["id"] : null;
$data["name"] = (isset($_POST["name"]) && $_POST["name"] != "") ? $_POST["name"] : null;
$data["icon"] = $_POST["icon"] ?? null;
$data["last_updated"] = $_SESSION['user_id'];
$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";

$dm = new Menu();
$dm->set_category(
	$data,
	$stat
);

echo json_encode($stat);

?>