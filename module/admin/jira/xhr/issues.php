<?php

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_jira."/controller/Issue.inc");

$controller = new Issue();
$issues = $controller->get_issues($_GET["board_id"], $_GET["sprint_id"]);

//print_r($issues);
echo json_encode($issues, JSON_UNESCAPED_UNICODE);

?>