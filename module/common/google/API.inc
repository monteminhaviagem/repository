<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/Path.inc");
//require_once($path_root."/ErrorHandler.inc");
//require_once($path_root_log."/Logger.inc");

class API {
	
	const token = 'AIzaSyCW9BtHbi5gyQLtElk98YKFVHiVWfMwPRg';
	const url_translate = 'https://www.googleapis.com/language/translate/v2';
	
	public function __construct() {}
	
	public function translate($source, $target, $text) {
		$url = API::url_translate . '?key=' . API::token . '&source=' . $source . '&target=' . $target . '&q=' . urlencode($text);
		
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		//curl_setopt($ch, CURLOPT_PROXY, $proxy);
		//curl_setopt($ch, CURLOPT_PROXYUSERPWD, $proxyauth);
		curl_setopt($ch, CURLOPT_HEADER, 0);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		$data = curl_exec($ch);
		
		curl_close($ch);
		
		return $data;
	}
}

?>