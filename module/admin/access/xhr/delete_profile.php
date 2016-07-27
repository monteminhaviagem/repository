<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/Profile.inc");

use module\admin\access\dm\Profile;

$data = array();
$stat = array();

$data["id"] = (isset($_POST["id"]) && $_POST["id"] != "") ? $_POST["id"] : null;

$dm = new Profile();
$dm->delete_profile(
	$data,
	$stat
);

echo json_encode($stat);

?>