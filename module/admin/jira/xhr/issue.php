<?php

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_jira."/controller/Issue.inc");

$controller = new Issue();
$issue = $controller->get_issue($_GET["issue_id"]);

//print_r($issue);
echo json_encode($issue, JSON_UNESCAPED_UNICODE);

?>