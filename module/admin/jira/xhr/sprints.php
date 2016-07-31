<?php

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_jira."/controller/Sprint.inc");

$controller = new Sprint();
$sprints = $controller->get_sprints($_GET["board_id"]);

//print_r($sprints);
echo json_encode($sprints, JSON_UNESCAPED_UNICODE);

?>