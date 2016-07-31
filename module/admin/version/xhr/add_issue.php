<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_version."/dm/Changelog.inc");
require_once($path_module_admin_jira."/controller/Issue.inc");

use module\admin\version\dm\Changelog;

$data = array();
$stat = array();

$version_id = $_POST["version_id"];
$issue_id = $_POST["issue_id"];

$controller = new Issue();
$issue = $controller->get_issue($issue_id);

$data["id"] = null;
$data["version_id"] = $version_id;
$data["issue_id"] = $issue["id"];
$data["issue_key"] = $issue["key"];
$data["issue_summary"] = is_null($issue["summary"]) ? "" : $issue["summary"];
$data["issue_description"] = is_null($issue["description"]) ? "" : $issue["description"];
$data["last_updated"] = $_SESSION['user_id'];
$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";

$dm = new Changelog();
$dm->set_changelog(
	$data,
	$stat
);

echo json_encode($stat, JSON_UNESCAPED_UNICODE);

?>