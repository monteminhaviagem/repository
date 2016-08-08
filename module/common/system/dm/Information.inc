<?php
namespace module\common\system\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");

use PDO;
use module\common\Log;
use module\common\Database;

class Information extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_information($args, &$data) {
		$data = array();
		$data2 = array();
		$key = (isset($args["key"]) && $args["key"] != "") ? $args["key"] : null;
		
		if (is_null($key)) {
			$sql = "
				select `key`,
				       `value`
				  from `system_information`";
			
			$rs = $this->connection->prepare($sql);
		}
		else {
			$sql = "
				select `key`,
				       `value`
				  from `system_information`
				 where `key` = :key";
			
			$rs = $this->connection->prepare($sql);
			$rs->bindParam(':key', $key);
		}
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					eval("\$data[\"".$row->key."\"] = \"".$row->value."\";");
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
}

?>