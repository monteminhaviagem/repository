<?php
namespace module\admin\access\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");

use PDO;
use module\common\Log;
use module\common\Database;

class Passenger extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function set_passenger(&$data, &$stat) {
		$st_update = $this->connection->prepare("update itinerary set adult = :adult, child = :child, pet = :pet where id = :id");
		$st_update->bindParam(':adult', $data["adult"]);
		$st_update->bindParam(':child', $data["child"]);
		$st_update->bindParam(':pet', $data["pet"]);
		$st_update->bindParam(':id', $data["itinerary_id"]);
			
		if (!$st_update->execute()) {
			$this->log->save("Statement => " . print_r($st_update->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		
			$stat["success"] = "false";
			$stat["message"] = $st_update->errorInfo();
			return;
		}
		
		$st_delete = $this->connection->prepare("delete from passenger where itinerary_id = :id");
		$st_delete->bindParam(':id', $data["itinerary_id"]);
			
		if (!$st_delete->execute()) {
			$this->log->save("Statement => " . print_r($st_update->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		
			$stat["success"] = "false";
			$stat["message"] = $st_update->errorInfo();
			return;
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
}

?>