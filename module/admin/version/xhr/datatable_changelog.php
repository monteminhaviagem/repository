<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_version."/dm/Changelog.inc");

use module\admin\version\dm\Changelog;

$args = array();
$data = array();
$return = array();

$dm = new Changelog();
$dm->get_changelog(
	$args,
	$data
);

$return["data"] = array();

for ($i = 0; $i<count($data); $i++) {
	$return["data"][] = Array($data[$i]["id"],$data[$i]["issue_key"],$data[$i]["issue_summary"],$data[$i]["issue_description"]);
}

echo json_encode($return, JSON_UNESCAPED_UNICODE);

?>