<?php
namespace module\admin\access\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");

use PDO;
use module\common\Log;
use module\common\Database;

class Profile extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_profile($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'profile.id';
		
		$sql = "
			select profile.id,
			       profile.name,
			       profile.description,
			       profile.user_type_id,
			       user_type.name user_type_name
			  from profile,
			       user_type
			 where profile.user_type_id = user_type.id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'name' => $row->name,
						'description' => $row->description,
						'user_type_id' => $row->user_type_id,
						'user_type_name' => $row->user_type_name
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_profile_id($args, &$data) {
		$data = array();
		
		$sql = "
			select profile.id,
			       profile.name,
			       profile.description,
			       profile.user_type_id,
			       user_type.name user_type_name,
			       profile.created,
			       profile.modified,
			       profile.last_updated,
			       user.name last_updated_name,
			       profile.ip
			  from profile,
			       user_type,
			       user
			 where profile.user_type_id = user_type.id
			   and profile.last_updated = user.id
			   and profile.id = :id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'name' => $row->name,
						'description' => $row->description,
						'user_type_id' => $row->user_type_id,
						'user_type_name' => $row->user_type_name,
						'created' => strtotime($row->created),
						'modified' => strtotime($row->modified),
						'last_updated' => $row->last_updated,
						'last_updated_name' => $row->last_updated_name,
						'ip' => $row->ip
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_profile_page($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'profile.id';
		
		$sql = "
			select profile.id,
			       profile.name,
			       profile.user_type_id
			  from profile,
			       profile_page
			 where profile.id = profile_page.profile_id
			   and profile_page.page_id = :page_id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':page_id', $args["page_id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'name' => $row->name,
						'user_type_id' => $row->user_type_id
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function set_profile(&$data, &$stat) {
		if (is_null($data["id"])) {
			$st_insert = $this->connection->prepare("insert into profile (name, description, user_type_id, created, modified, last_updated, ip) values (:name, :description, :user_type_id, now(), now(), :last_updated, :ip)");
			$st_insert->bindParam(':name', $data["name"]);
			$st_insert->bindParam(':description', $data["description"]);
			$st_insert->bindParam(':user_type_id', $data["user_type_id"]);
			$st_insert->bindParam(':last_updated', $data["last_updated"]);
			$st_insert->bindParam(':ip', $data["ip"]);
			
			if (!$st_insert->execute()) {
				$this->log->save("Statement => " . print_r($st_insert->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_insert->errorInfo();
				return;
			}
			
			$stat["id"] = $this->connection->lastInsertId();
		}
		else {
			$st_update = $this->connection->prepare("update profile set name = :name, description = :description, user_type_id = :user_type_id, modified = now(), last_updated = :last_updated, ip = :ip where id = :id");
			$st_update->bindParam(':name', $data["name"]);
			$st_update->bindParam(':description', $data["description"]);
			$st_update->bindParam(':user_type_id', $data["user_type_id"]);
			$st_update->bindParam(':last_updated', $data["last_updated"]);
			$st_update->bindParam(':ip', $data["ip"]);
			$st_update->bindParam(':id', $data["id"]);
			
			if (!$st_update->execute()) {
				$this->log->save("Statement => " . print_r($st_update->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_update->errorInfo();
				return;
			}
			
			$st_delete = $this->connection->prepare("delete from profile_page where profile_id = :profile_id");
			$st_delete->bindParam(':profile_id', $data["id"]);
			
			if (!$st_delete->execute()) {
				$this->log->save("Statement => " . print_r($st_delete->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_delete->errorInfo();
				return;
			}
			
			$stat["id"] = $data["id"];
		}
		
		if (count($data["page"]) > 0) {
			for ($i=0; $i<count($data["page"]); $i++) {
				$st_insert_page = $this->connection->prepare("insert into profile_page (profile_id, page_id) values (:profile_id, :page_id)");
				$st_insert_page->bindParam(':profile_id', $data["id"]);
				$st_insert_page->bindParam(':page_id', $data["page"][$i]);
				
				if (!$st_insert_page->execute()) {
					$this->log->save("Statement => " . print_r($st_insert_page->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
					$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
						
					$stat["success"] = "false";
					$stat["message"] = $st_insert_page->errorInfo();
						
					return;
				}
			}
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public function delete_profile(&$data, &$stat) {
		$st_delete_profile_page = $this->connection->prepare("delete from profile_page where profile_id = :profile_id");
		$st_delete_profile_page->bindParam(':profile_id', $data["id"]);
		
		if (!$st_delete_profile_page->execute()) {
			$this->log->save("Statement => " . print_r($st_delete_profile_page->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			
			$stat["success"] = "false";
			$stat["message"] = $st_delete_profile_page->errorInfo();
			return;
		}
		
		$st_delete_profile = $this->connection->prepare("delete from profile where id = :id");
		$st_delete_profile->bindParam(':id', $data["id"]);
		
		if (!$st_delete_profile->execute()) {
			$this->log->save("Statement => " . print_r($st_delete_profile->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
			$stat["success"] = "false";
			$stat["message"] = $st_delete_profile->errorInfo();
			return;
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public static function get_user_type_id($id) {
		$args = array();
		$data = array();
		
		$args["id"] = $id;
		
		$dm = new Profile();
		$dm->get_profile_id(
			$args,
			$data
		);
		
		return $data["user_type_id"];
	}
}

?>