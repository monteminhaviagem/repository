<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_admin_jira."/API.inc");

class Issue {
	
	public function __construct() {}
	
	public function get_issues($board_id, $sprint_id) {
		$mod = new API();
		
		$data = json_decode($mod->get_issues($board_id, $sprint_id), TRUE);
		
		$issues = array();
		
		for ($i=0; $i<count($data["issues"]); $i++) {
			$issues[] = array(
				'id' => $data["issues"][$i]["id"],
				'key' => $data["issues"][$i]["key"],
				'summary' => $data["issues"][$i]["fields"]["summary"],
				'description' => $data["issues"][$i]["fields"]["description"]
			);
		}
		
		return $issues;
	}
	
	public function get_issue($issue_id) {
		$mod = new API();
		
		$data = json_decode($mod->get_issue($issue_id), TRUE);
		
		$issue = array();
		$issue["id"] = $data["id"];
		$issue["key"] = $data["key"];
		$issue["summary"] = $data["fields"]["summary"];
		$issue["description"] =$data["fields"]["description"];
		
		return $issue;
	}
}

?>