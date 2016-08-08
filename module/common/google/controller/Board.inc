<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_admin_jira."/API.inc");

class Board {
	
	public function __construct() {}
	
	public function get_boards() {
		$mod = new API();
		
		$data = json_decode($mod->get_boards(), TRUE);
		
		$boards = array();
		
		for ($i=0; $i<count($data["values"]); $i++) {
			$boards[] = array(
				'id' => $data["values"][$i]["id"],
				'name' => $data["values"][$i]["name"]
			);
		}
		
		return $boards;
	}
}

?>