<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common_system."/dm/Information.inc");

use module\common\system\dm\Information;

$args = array();
$data = array();
$return = array();

$args["key"] = $_POST["key"] ?? "";

$dm = new Information();
$dm->get_information(
	$args,
	$data
);

echo json_encode($data, JSON_UNESCAPED_UNICODE);

?>