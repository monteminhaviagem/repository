<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common_system."/dm/Information.inc");

use module\common\system\dm\Information;

class API {
	
	public function __construct() {}
	
	public function get_token($code) {
		$args = array();
		$data = array();
		
		$dm = new Information();
		$dm->get_information(
			$args,
			$data
		);
		
		$url = $data["GOOGLE_OAUTH2.0_TOKEN_URL"];
		
		$post = "code=" . urlencode($code);
		$post .= "&client_id=" . urlencode($data["GOOGLE_CLIENT_ID"]);
		$post .= "&client_secret=" . urlencode($data["GOOGLE_CLIENT_SECRET"]);
		$post .= "&redirect_uri=" . urlencode($data["GOOGLE_OAUTH2.0_AUTHENTICATION_REDIRECT_URI"]);
		$post .= "&grant_type=" . urlencode($data["GOOGLE_OAUTH2.0_TOKEN_GRANT_TYPE"]);
		
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS,$post);
		//curl_setopt($ch, CURLOPT_PROXY, $proxy);
		//curl_setopt($ch, CURLOPT_PROXYUSERPWD, $proxyauth);
		//curl_setopt($ch, CURLOPT_HEADER, 0);
		//curl_setopt($ch, CURLOPT_HEADER, true);
		//curl_setopt($ch, CURLINFO_HEADER_OUT, true);
		//curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		//curl_setopt($ch, CURLOPT_USERPWD, API::userpwd);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		//print_r(curl_getinfo($ch));
		//echo $data;
		
		$data = curl_exec($ch);
		
		curl_close($ch);
		
		return $data;
	}
	
	public function get_userinfo($access_token) {
		$args = array();
		$data = array();
		
		$dm = new Information();
		$dm->get_information(
			$args,
			$data
		);
		
		$url = $data["GOOGLE_OAUTH2.0_USERINFO_URL"];
		$url .= "?access_token=" . $access_token;
		
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		//curl_setopt($ch, CURLOPT_POST, 1);
		//curl_setopt($ch, CURLOPT_POSTFIELDS,$post);
		//curl_setopt($ch, CURLOPT_PROXY, $proxy);
		//curl_setopt($ch, CURLOPT_PROXYUSERPWD, $proxyauth);
		//curl_setopt($ch, CURLOPT_HEADER, 0);
		//curl_setopt($ch, CURLOPT_HEADER, true);
		//curl_setopt($ch, CURLINFO_HEADER_OUT, true);
		//curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		//curl_setopt($ch, CURLOPT_USERPWD, API::userpwd);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		//print_r(curl_getinfo($ch));
		//echo $data;
		
		$data = curl_exec($ch);
		
		curl_close($ch);
		
		return $data;
	}
}

?>