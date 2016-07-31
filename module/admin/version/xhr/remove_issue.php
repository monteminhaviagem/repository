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

$id = $_POST["id"];

$data["id"] = $id;

$dm = new Changelog();
$dm->remove_changelog(
	$data,
	$stat
);

echo json_encode($stat, JSON_UNESCAPED_UNICODE);

?>