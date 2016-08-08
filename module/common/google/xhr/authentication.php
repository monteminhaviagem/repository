<?php

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common_google."/controller/Authentication.inc");

$controller = new Authentication();
$url = $controller->get_url();

echo json_encode($url, JSON_UNESCAPED_UNICODE);

?>