<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_version."/dm/Changelog.inc");

use module\admin\version\dm\Changelog;

$data = array();
$stat = array();

$data["id"] = $_POST["id"];
$data["issue_summary"] = is_null($_POST["issue_summary"]) ? "" : $_POST["issue_summary"];
$data["issue_description"] = is_null($_POST["issue_description"]) ? "" : $_POST["issue_description"];
$data["last_updated"] = $_SESSION['user_id'];
$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";

$dm = new Changelog();
$dm->set_changelog(
	$data,
	$stat
);

echo json_encode($stat, JSON_UNESCAPED_UNICODE);

?>