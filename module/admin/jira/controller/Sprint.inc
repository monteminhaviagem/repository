<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_admin_jira."/API.inc");

class Sprint {
	
	public function __construct() {}
	
	public function get_sprints($board_id) {
		$mod = new API();
		
		$data = json_decode($mod->get_sprints($board_id), TRUE);
		
		$sprints = array();
		
		for ($i=0; $i<count($data["values"]); $i++) {
			$sprints[] = array(
				'id' => $data["values"][$i]["id"],
				'name' => $data["values"][$i]["name"],
				'state' => $data["values"][$i]["state"]
			);
		}
		
		return $sprints;
	}
}

?>