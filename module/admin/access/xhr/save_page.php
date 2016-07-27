<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/Page.inc");

use module\admin\access\dm\Page;

$data = array();
$stat = array();

$data["id"] = (isset($_POST["id"]) && $_POST["id"] != "") ? $_POST["id"] : null;
$data["url"] = (isset($_POST["url"]) && $_POST["url"] != "") ? $_POST["url"] : null;
$data["last_updated"] = $_SESSION['user_id'];
$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";
$data["profile"] = $_POST["profile"] ?? null;

$dm = new Page();
$dm->set_page(
	$data,
	$stat
);

echo json_encode($stat);

?>