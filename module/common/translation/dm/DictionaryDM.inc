<?php

require_once($_SERVER["DOCUMENT_ROOT"] . "/Path.inc");
//require_once($path_root."/ErrorHandler.inc");
//require_once($path_root_log."/Logger.inc");
require_once($path_root_common."/DatabaseDM.inc");

class DictionaryDM extends DatabaseDM {
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
	}
	
	public function get_en_pt($dm_args, &$dm_data, &$dm_stat) {
		$dm_data = array();
		
		$sql = "
			select text_en,
			       text_pt,
			       created,
			       modified
			  from dictionary_en_pt
			 where text_en = :text_en";
		
		$text_en = mb_strtoupper($dm_args["text"],'UTF-8');
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':text_en', $text_en);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$created_database = $row->created;
					$created_php = !is_null($row->created) ? strtotime($row->created) : null;
					$created_format = !is_null($row->created) ? date("d/m/Y H:i:s",strtotime($row->created)) : null;
					
					$modified_database = $row->modified;
					$modified_php = !is_null($row->modified) ? strtotime($row->modified) : null;
					$modified_format = !is_null($row->modified) ? date("d/m/Y H:i:s",strtotime($row->modified)) : null;
					
					if (!isset($dm_args["date_type"])) {
						$created = $created_php;
						$modified = $modified_php;
					}
					else if ($dm_args["date_type"] == 'database') {
						$created = $created_database;
						$modified = $modified_database;
					}
					else if ($dm_args["date_type"] == 'php') {
						$created = $created_php;
						$modified = $modified_php;
					}
					else if ($dm_args["date_type"] == 'format') {
						$created = $created_format;
						$modified = $modified_format;
					}
					else {
						$created = $created_php;
						$modified = $modified_php;
					}
					
					$dm_data = array(
						'text_en' => $row->text_en,
						'text_pt' => $row->text_pt,
						'created' => $created,
						'modified' => $modified
					);
				}
			}
		}
		//else{
		//	$this->logger->save_log(Logger::LEVEL_CRITICAL, "Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		//	$this->logger->save_log(Logger::LEVEL_CRITICAL, "Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		//}
	}
	
	public function set_en_pt(&$dm_data, &$dm_stat) {
		$st_insert = $this->connection->prepare("insert into dictionary_en_pt (text_en, text_pt, created, modified) values (:text_en, :text_pt, now(), now())");
		$st_insert->bindParam(':text_en', $dm_data["text_en"]);
		$st_insert->bindParam(':text_pt', $dm_data["text_pt"]);
		
		if (!$st_insert->execute()) {
			$dm_stat["success"] = "false";
			$dm_stat["message"] = $st_insert->errorInfo();
			return;
		}
		
		$dm_stat["success"] = "true";
		$dm_stat["message"] = "";
	}
}

?>