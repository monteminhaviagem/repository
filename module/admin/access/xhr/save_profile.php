<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/Profile.inc");

use module\admin\access\dm\Profile;

$data = array();
$stat = array();

$data["id"] = (isset($_POST["id"]) && $_POST["id"] != "") ? $_POST["id"] : null;
$data["name"] = (isset($_POST["name"]) && $_POST["name"] != "") ? $_POST["name"] : null;
$data["user_type_id"] = $_POST["user_type_id"] ?? null;
$data["description"] = $_POST["description"] ?? null;
$data["last_updated"] = $_SESSION['user_id'];
$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";
$data["page"] = $_POST["page"] ?? null;

$dm = new Profile();
$dm->set_profile(
	$data,
	$stat
);

echo json_encode($stat);

?>