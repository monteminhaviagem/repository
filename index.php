<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_info."/view/Login.inc");
require_once($path_module_info."/view/Home.inc");
require_once($path_module_admin_dashboard."/view/Dashboard.inc");
require_once($path_module_operation."/itinerary/view/Passenger.inc");
require_once($path_module_admin_access."/dm/Page.inc");
require_once($path_module_admin_access."/dm/PageType.inc");
require_once($path_module_admin_access."/dm/Session.inc");

use module\common\Log;
use module\info\view\Home;
use module\admin\access\dm\Page;
use module\admin\dashboard\view\Dashboard;
use module\info\view\Error;
use module\admin\access\dm\Session;
use module\admin\access\dm\PageType;
use module\operation\itinerary\view\Passenger;

$args = array();
$data = array();

$args["url"] = $_SERVER["REQUEST_URI"];

if ($args["url"] == "/") {
	session_start();
	
	if (!isset($_SESSION['id'])) {
		$page = new Home();
		print($page->get_page());
	}
	else {
		if ($_SESSION['page_type_id'] == PageType::ADMINISTRATIVA)
			header("Location: " . Page::get_url(Dashboard::ID));
		else if ($_SESSION['page_type_id'] == PageType::OPERACIONAL)
			header("Location: " . Page::get_url(Passenger::ID));
	}
}
else if ($args["url"] == "/logout") {
	session_start();
	
	if (isset($_SESSION['id'])) {
		$stat["finalize_session"] = array();
		$data["finalize_session"] = array();
		$data["finalize_session"]["id"] = $_SESSION['id'];
		$data["finalize_session"]["last_updated"] = $_SESSION['user_id'];
		$data["finalize_session"]["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";
		
		$dm = new Session();
		$dm->finalize_session(
			$data["finalize_session"],
			$stat["finalize_session"]
		);
	}
	
	$_SESSION['id'] = null;
	$_SESSION['token'] = null;
	$_SESSION['user_id'] = null;
	$_SESSION['profile_id'] = null;
	$_SESSION['user_type_id'] = null;
	$_SESSION['page_type_id'] = null;
	
	unset($_SESSION['id']);
	unset($_SESSION['token']);
	unset($_SESSION['user_id']);
	unset($_SESSION['profile_id']);
	unset($_SESSION['user_type_id']);
	unset($_SESSION['page_type_id']);
	
	header('Location: /');
}
else {
	$dm = new Page();
	$dm->get_page_url(
		$args,
		$data["page"]
	);
	
	if (count($data["page"]) > 0) {
		require_once($path. $data["page"]["file"]);
		eval("\$page = new " . $data["page"]["namespace"] . "\\" . $data["page"]["class"] . "();");
	}
	else {
		require_once($path. Page::get_file(Error::ID));
		eval("\$page = new " . Page::get_class(Error::ID) . "(3);");
	}
	
	print($page->get_page());
}

?>