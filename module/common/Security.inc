<?php
namespace module\common;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_access."/dm/Profile.inc");
require_once($path_module_admin_access."/dm/Session.inc");
require_once($path_module_admin_access."/dm/SessionStatus.inc");

use module\admin\access\dm\Profile;
use module\admin\access\dm\Session;
use module\admin\access\dm\SessionStatus;

class Security {
	
	public static function get_authorization($page_id, $profile_id) {
		$args = array();
		$data = array();
		
		$args["page_id"] = $page_id;
		
		$dm = new Profile();
		$dm->get_profile_page(
			$args,
			$data
		);
		
		for ($i=0; $i<count($data); $i++) {
			if ($data[$i]["id"] == $profile_id)
				return true;
		}
		
		return false;
	}
	
	public static function validate_token($token, $user_id) {
		$args = array();
		$data = array();
		
		$args["token"] = $token;
		
		$dm = new Session();
		$dm->get_session_token(
			$args,
			$data
		);
		
		if ((isset($data["id"])) &&
			($data["user_id"] == $user_id) &&
			($data["session_status_id"] == SessionStatus::ATIVA))
			return true;
		else
			return false;
	}
}

?>