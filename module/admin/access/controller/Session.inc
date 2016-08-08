<?php

namespace module\admin\access\controller;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_admin_access."/dm/User.inc");
require_once($path_module_admin_access."/dm/Session.inc");

use module\admin\access\dm\Session;
use module\admin\access\dm\User;

class Session {
	
	public function __construct() {}
	
	public function create_session($user_id, $session_authentication_id, &$stat) {
		$args = array();
		$data = array();
		$stat = array();
		
		$data["get_session_user_active"] = array();
		$args["get_session_user_active"] = array();
		$args["get_session_user_active"]["user_id"] = $user_id;
		
		$dm = new Session();
		$dm->get_session_user_active(
			$args["get_session_user_active"],
			$data["get_session_user_active"]
		);
		
		$stat["finalize_session"] = array();
		$data["finalize_session"] = array();
		
		for ($i=0; $i<count($data["get_session_user_active"]); $i++) {
			$data["finalize_session"]["id"] = $data["get_session_user_active"][$i]["id"];
			$data["finalize_session"]["last_updated"] = $user_id;
			$data["finalize_session"]["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";
			
			$dm->finalize_session(
				$data["finalize_session"],
				$stat["finalize_session"]
			);
		}
		
		$stat["create_session"] = array();
		$data["create_session"] = array();
		$data["create_session"]["user_id"] = $user_id;
		$data["create_session"]["session_authentication_id"] = $session_authentication_id;
		$data["create_session"]["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";
		
		$dm->create_session(
			$data["create_session"],
			$stat["create_session"]
		);
		
		$data["get_session_id"] = array();
		$args["get_session_id"] = array();
		$args["get_session_id"] = array();
		$args["get_session_id"]["id"] = $stat["create_session"]["id"];
		
		$dm->get_session_id(
			$args["get_session_id"],
			$data["get_session_id"]
		);
		
		$stat["success"] = "true";
		$stat["message"] = "";
		$stat["session"] = array();
		$stat["session"]["id"] = $data["get_session_id"]["id"];
		$stat["session"]["user_id"] = $data["get_session_id"]["user_id"];
		$stat["session"]["user_name"] = $data["get_session_id"]["user_name"];
		$stat["session"]["profile_id"] = $data["get_session_id"]["profile_id"];
		$stat["session"]["profile_name"] = $data["get_session_id"]["profile_name"];
		$stat["session"]["user_type_id"] = $data["get_session_id"]["user_type_id"];
		$stat["session"]["user_type_name"] = $data["get_session_id"]["user_type_name"];
		$stat["session"]["page_type_id"] = $data["get_session_id"]["page_type_id"];
		$stat["session"]["token"] = $data["get_session_id"]["token"];
		$stat["session"]["begin"] = $data["get_session_id"]["begin"];
		$stat["session"]["expire"] = $data["get_session_id"]["expire"];
		$stat["session"]["end"] = $data["get_session_id"]["end"];
		$stat["session"]["session_status_id"] = $data["get_session_id"]["session_status_id"];
		$stat["session"]["session_status_name"] = $data["get_session_id"]["session_status_name"];
		$stat["session"]["last_updated"] = $data["get_session_id"]["last_updated"];
		$stat["session"]["ip"] = $data["get_session_id"]["ip"];
	}
}

?>