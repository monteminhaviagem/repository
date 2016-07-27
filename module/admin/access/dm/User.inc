<?php
namespace module\admin\access\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");
require_once($path_module_admin_access."/dm/UserStatus.inc");

use PDO;
use module\common\Log;
use module\common\Database;
use module\admin\access\dm\UserStatus;

class User extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_user($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'user.id';
		
		$sql = "
			select user.id,
			       user.name,
			       user.email,
			       user.user_status_id,
			       user_status.name user_status_name, 
			       user.profile_id,
			       profile.name profile_name,
			       profile.user_type_id,
			       user_type.name user_type_name
			  from user,
			       user_status,
			       profile,
			       user_type
			where user.user_status_id = user_status.id
			  and user.profile_id = profile.id
			  and profile.user_type_id = user_type.id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'name' => $row->name,
						'email' => $row->email,
						'user_status_id' => $row->user_status_id,
						'user_status_name' => $row->user_status_name,
						'profile_id' => $row->profile_id,
						'profile_name' => $row->profile_name,
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
	
	public function get_user_id($args, &$data) {
		$data = array();
		
		$sql = "
			select user.id,
			       user.name,
			       user.email,
			       user.user_status_id,
			       user_status.name user_status_name, 
			       user.profile_id,
			       profile.name profile_name,
			       profile.user_type_id,
			       user_type.name user_type_name,
			       user.created,
			       user.modified,
			       user.last_updated,
			       user_reference.name last_updated_name,
			       profile.ip
			  from user,
			       user_status,
			       profile,
			       user_type,
			       user user_reference
			where user.user_status_id = user_status.id
			  and user.profile_id = profile.id
			  and profile.user_type_id = user_type.id
			  and user.last_updated = user_reference.id
			  and user.id = :id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'name' => $row->name,
						'email' => $row->email,
						'user_status_id' => $row->user_status_id,
						'user_status_name' => $row->user_status_name,
						'profile_id' => $row->profile_id,
						'profile_name' => $row->profile_name,
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
	
	public function get_user_credential($args, &$data) {
		$data = array();
		
		$sql = "
			select id,
			       profile_id
			  from user
			 where email = :email
			   and password = :password";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':email', $args["email"]);
		$rs->bindParam(':password', $args["password"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'profile_id' => $row->profile_id
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function set_user(&$data, &$stat) {
		if (is_null($data["id"])) {
			$user_status_id = UserStatus::ATIVO;
			
			$st_insert = $this->connection->prepare("insert into user (name, email, password, user_status_id, profile_id, created, modified, last_updated, ip) values (:name, :email, :password, :user_status_id, :profile_id, now(), now(), :last_updated, :ip)");
			$st_insert->bindParam(':name', $data["name"]);
			$st_insert->bindParam(':email', $data["email"]);
			$st_insert->bindParam(':password', $data["password"]);
			$st_insert->bindParam(':user_status_id', $user_status_id);
			$st_insert->bindParam(':profile_id', $data["profile_id"]);
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
			$st_update = $this->connection->prepare("update user set name = :name, email = :email, profile_id = :profile_id, modified = now(), last_updated = :last_updated, ip = :ip where id = :id");
			$st_update->bindParam(':name', $data["name"]);
			$st_update->bindParam(':email', $data["email"]);
			$st_update->bindParam(':profile_id', $data["profile_id"]);
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
			
			$stat["id"] = $data["id"];
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public function get_user_count() {
		$sql = "
			select count(*) count
			  from user
			   use index(`user_id`)";
		
		$rs = $this->connection->prepare($sql);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					return $row->count;
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
		
		return 0;
	}
	
	public static function get_count() {
		$dm = new User();
		return $dm->get_user_count();
	}
}

?>