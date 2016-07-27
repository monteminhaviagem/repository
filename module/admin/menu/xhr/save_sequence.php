<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_menu."/dm/Menu.inc");

use module\admin\menu\dm\Menu;

$data = array();
$stat = array();

$data = json_decode($_POST["submenu"],true);

$dm = new Menu();
$dm->set_sequence(
	$data,
	$stat
);

echo json_encode($stat);

?>