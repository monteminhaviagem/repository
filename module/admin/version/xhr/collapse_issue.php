<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_jira."/controller/Issue.inc");

$controller = new Issue();
$issues = $controller->get_issues($_POST["board_id"], $_POST["sprint_id"]);

echo json_encode($issues, JSON_UNESCAPED_UNICODE);

?>