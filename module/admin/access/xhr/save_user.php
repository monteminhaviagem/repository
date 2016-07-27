<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/User.inc");

use module\admin\access\dm\User;

$data = array();
$stat = array();

$data["id"] = (isset($_POST["id"]) && $_POST["id"] != "") ? $_POST["id"] : null;
$data["name"] = (isset($_POST["name"]) && $_POST["name"] != "") ? $_POST["name"] : null;
$data["email"] = (isset($_POST["email"]) && $_POST["email"] != "") ? $_POST["email"] : null;
$data["password"] = md5("123456");
$data["profile_id"] = $_POST["profile_id"] ?? null;
$data["last_updated"] = $_SESSION['user_id'];
$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";

$dm = new User();
$dm->set_user(
	$data,
	$stat
);

echo json_encode($stat);

?>