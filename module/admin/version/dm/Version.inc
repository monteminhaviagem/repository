<?php
namespace module\admin\version\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");

use PDO;
use module\common\Log;
use module\common\Database;

class Version extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_version($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'version.id';
		
		$sql = "
			select id,
			       tag,
			       current,
			       created,
			       checkout
			  from version
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'tag' => $row->tag,
						'current' => $row->current,
						'created' => strtotime($row->created),
						'checkout' => strtotime($row->checkout)
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_version_id($args, &$data) {
		$data = array();
		
		$sql = "
			select id,
			       tag,
			       current,
			       created,
			       checkout
			  from version
			 where id = :id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'tag' => $row->tag,
						'current' => $row->current,
						'created' => strtotime($row->created),
						'checkout' => strtotime($row->checkout)
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public static function get_tag($id) {
		$args = array();
		$data = array();
		
		$args["id"] = $id;
		
		$dm = new Version();
		$dm->get_version_id(
			$args,
			$data
		);
		
		return $data["tag"];
	}
}

?>