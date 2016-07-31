<?php

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_jira."/controller/Board.inc");

$controller = new Board();
$boards = $controller->get_boards();

//print_r($boards);
echo json_encode($boards, JSON_UNESCAPED_UNICODE);

?>