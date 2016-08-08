<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/Path.inc");
//require_once($path_root."/ErrorHandler.inc");
//require_once($path_root_log."/Logger.inc");
//require_once($path_root_module_google."/API.inc");
//require_once($path_root_module_translate."/dm/DictionaryDM.inc");

class Information {
	
	public function __construct() {}
	
	/*
	public function get_translation($source, $target, $text, $cache = true) {
		$dm_args = array();
		$dm_data = array();
		$dm_stat = array();
		
		$return = Array();
		
		$dm = new DictionaryDM();
		
		if ($cache) {
			$dm_args["search"] = array();
			$dm_data["search"] = array();
			$dm_stat["search"] = array();
			
			$dm_args["search"]["text"] = $text;
			
			$dm->get_en_pt(
				$dm_args["search"],
				$dm_data["search"],
				$dm_stat["search"]
			);
			
			$translated = (isset($dm_data["search"]["text_pt"])) ? $dm_data["search"]["text_pt"] : null;
		}
		
		if (isset($translated)) {
			$return["translated"] = $translated;
			$return["cache"] = "true";
		}
		else {
			$mod = new API();
			$data = json_decode($mod->translate($source, $target, $text),true);
			$translated = $data["data"]["translations"][0]["translatedText"];
			
			$dm_data["save"] = array();
			$dm_stat["save"] = array();
			
			$dm_data["save"]["text_en"] = mb_strtoupper($text,'UTF-8');
			$dm_data["save"]["text_pt"] = mb_strtoupper($translated,'UTF-8');
			
			$dm->set_en_pt(
				$dm_data["save"],
				$dm_stat["save"]
			);
			
			$return["translated"] = $translated;
			$return["cache"] = "false";
		}
		
		return $return;
	}
	*/
}

?>