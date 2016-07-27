<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_operation_itinerary."/dm/Passenger.inc");

use module\admin\access\dm\Passenger;

$data = array();
$stat = array();

$data["itinerary_id"] = $_POST["itinerary_id"];
$data["adult"] = (isset($_POST["adult"]) && $_POST["adult"] != "") ? $_POST["adult"] : "0";
$data["child"] = (isset($_POST["child"]) && $_POST["child"] != "") ? $_POST["child"] : "0";
$data["pet"] = (isset($_POST["pet"]) && $_POST["pet"] != "") ? $_POST["pet"] : "0";
$data["last_updated"] = $_SESSION['user_id'];
$data["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";

$dm = new Passenger();
$dm->set_passenger(
	$data,
	$stat
);

echo json_encode($stat);

?>