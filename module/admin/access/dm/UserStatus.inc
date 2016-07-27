<?php
namespace module\admin\access\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");

use PDO;
use module\common\Log;
use module\common\Database;

class UserStatus extends Database {
	
	const ATIVO = 1;
	const INATIVO = 2;
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_user_status($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'id';
		
		$sql = "
			select id,
			       name
			  from user_status
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'name' => $row->name
					);
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