<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common_system."/dm/Information.inc");

use module\common\system\dm\Information;

class Authentication {
	
	public function __construct() {}
	
	public function get_url() {
		$args = array();
		$data = array();
		
		$dm = new Information();
		$dm->get_information(
			$args,
			$data
		);
		
		$url = array();
		$url["url"] = $data["GOOGLE_OAUTH2.0_AUTHENTICATION_URL"];
		$url["scope"] = $data["GOOGLE_OAUTH2.0_AUTHENTICATION_SCOPE"];
		$url["state"] = $data["GOOGLE_OAUTH2.0_AUTHENTICATION_STATE"];
		$url["redirect_uri"] = $data["GOOGLE_OAUTH2.0_AUTHENTICATION_REDIRECT_URI"];
		$url["response_type"] = $data["GOOGLE_OAUTH2.0_AUTHENTICATION_RESPONSE_TYPE"];
		$url["client_id"] = $data["GOOGLE_CLIENT_ID"];
		
		return $url;
	}
}

?>