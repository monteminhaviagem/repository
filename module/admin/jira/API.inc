<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");

class API {
	
	const userpwd = 'daniel@grupotwo.com.br:sqsescd10mf';
	const url_boards = 'https://monteminhaviagem.atlassian.net/rest/agile/1.0/board';
	const url_sprints = 'https://monteminhaviagem.atlassian.net/rest/agile/1.0/board/[[board_id]]/sprint';
	const url_issues = 'https://monteminhaviagem.atlassian.net/rest/agile/1.0/board/[[board_id]]/sprint/[[sprint_id]]/issue?fields=summary,description,creator';
	const url_issue = 'https://monteminhaviagem.atlassian.net/rest/agile/1.0/issue/[[issue_id]]?fields=summary,description,creator';
	
	public function __construct() {}
	
	public function get_boards() {
		$url = API::url_boards;
		
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		//curl_setopt($ch, CURLOPT_PROXY, $proxy);
		//curl_setopt($ch, CURLOPT_PROXYUSERPWD, $proxyauth);
		//curl_setopt($ch, CURLOPT_HEADER, 0);
		//curl_setopt($ch, CURLOPT_HEADER, true);
		//curl_setopt($ch, CURLINFO_HEADER_OUT, true);
		curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_setopt($ch, CURLOPT_USERPWD, API::userpwd);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		//print_r(curl_getinfo($ch));
		//echo $data;
		
		$data = curl_exec($ch);
		
		curl_close($ch);
		
		return $data;
	}
	
	public function get_sprints($board_id) {
		$url = str_replace('[[board_id]]', $board_id, API::url_sprints);
		
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_setopt($ch, CURLOPT_USERPWD, API::userpwd);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		$data = curl_exec($ch);
		
		curl_close($ch);
		
		return $data;
	}
	
	public function get_issues($board_id, $sprint_id) {
		$url = str_replace('[[sprint_id]]',$sprint_id,str_replace('[[board_id]]', $board_id, API::url_issues));
		
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_setopt($ch, CURLOPT_USERPWD, API::userpwd);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		$data = curl_exec($ch);
		
		curl_close($ch);
		
		return $data;
	}
	
	public function get_issue($issue_id) {
		$url = str_replace('[[issue_id]]', $issue_id, API::url_issue);
		
		$ch = curl_init();
		
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		curl_setopt($ch, CURLOPT_USERPWD, API::userpwd);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		
		$data = curl_exec($ch);
		
		curl_close($ch);
		
		return $data;
	}
}

?>