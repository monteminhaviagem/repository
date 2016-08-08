<?php
namespace module\admin\access\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");
require_once($path_module_admin_access."/dm/SessionStatus.inc");

use PDO;
use Exception;
use module\common\Log;
use module\common\Database;

class Session extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_session_active($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'session.begin desc';
		
		$sql = "
			select session.id,
			       session.user_id,
			       user.name user_name,
			       profile.user_type_id,
			       user_type.name user_type_name,
			       session.token,
			       session.begin,
			       session.expire,
			       session.end,
			       session.session_status_id,
			       session_status.name session_status_name,
			       session.last_updated,
			       session.ip
			  from session,
			       session_status,
			       user,
			       profile,
			       user_type
			 where session.session_status_id = session_status.id
			   and session.user_id = user.id
			   and user.profile_id = profile.id
			   and profile.user_type_id = user_type.id
			   and session.session_status_id = :session_status_id
			 order by $order";
		
		$session_status_id = SessionStatus::ATIVA;
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':session_status_id', $session_status_id);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'user_id' => $row->user_id,
						'user_name' => $row->user_name,
						'user_type_id' => $row->user_type_id,
						'user_type_name' => $row->user_type_name,
						'token' => $row->token,
						'begin' => strtotime($row->begin),
						'expire' => strtotime($row->expire),
						'end' => strtotime($row->end),
						'session_status_id' => $row->session_status_id,
						'session_status_name' => $row->session_status_name,
						'last_updated' => $row->last_updated,
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
	
	public function get_session_user_active($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'session.id';
		
		$sql = "
			select session.id,
			       session.user_id,
			       user.name user_name,
			       profile.user_type_id,
			       user_type.name user_type_name,
			       session.token,
			       session.begin,
			       session.expire,
			       session.end,
			       session.session_status_id,
			       session_status.name session_status_name,
			       session.last_updated,
			       session.ip
			  from session,
			       session_status,
			       user,
			       profile,
			       user_type
			 where session.session_status_id = session_status.id
			   and session.user_id = user.id
			   and user.profile_id = profile.id
			   and profile.user_type_id = user_type.id
			   and session.session_status_id = :session_status_id
			   and session.user_id = :user_id
			 order by $order";
		
		$session_status_id = SessionStatus::ATIVA;
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':session_status_id', $session_status_id);
		$rs->bindParam(':user_id', $args["user_id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'user_id' => $row->user_id,
						'user_name' => $row->user_name,
						'user_type_id' => $row->user_type_id,
						'user_type_name' => $row->user_type_name,
						'token' => $row->token,
						'begin' => strtotime($row->begin),
						'expire' => strtotime($row->expire),
						'end' => strtotime($row->end),
						'session_status_id' => $row->session_status_id,
						'session_status_name' => $row->session_status_name,
						'last_updated' => $row->last_updated,
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
	
	public function get_session_id($args, &$data) {
		$data = array();
		
		$sql = "
			select session.id,
			       session.user_id,
			       user.name user_name,
			       user.profile_id,
			       profile.name profile_name,
			       profile.user_type_id,
			       user_type.name user_type_name,
			       user_type.page_type_id,
			       session.token,
			       session.begin,
			       session.expire,
			       session.end,
			       session.session_status_id,
			       session_status.name session_status_name,
			       session.last_updated,
			       session.ip
			  from session,
			       session_status,
			       user,
			       profile,
			       user_type
			 where session.session_status_id = session_status.id
			   and session.user_id = user.id
			   and user.profile_id = profile.id
			   and profile.user_type_id = user_type.id
			   and session.id = :id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'user_id' => $row->user_id,
						'user_name' => $row->user_name,
						'profile_id' => $row->profile_id,
						'profile_name' => $row->profile_name,
						'user_type_id' => $row->user_type_id,
						'user_type_name' => $row->user_type_name,
						'page_type_id' => $row->page_type_id,
						'token' => $row->token,
						'begin' => strtotime($row->begin),
						'expire' => strtotime($row->expire),
						'end' => strtotime($row->end),
						'session_status_id' => $row->session_status_id,
						'session_status_name' => $row->session_status_name,
						'last_updated' => $row->last_updated,
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
	
	public function get_session_token($args, &$data) {
		$data = array();
		
		$sql = "
			select session.id,
			       session.user_id,
			       user.name user_name,
			       session.token,
			       session.begin,
			       session.expire,
			       session.end,
			       session.session_status_id,
			       session_status.name session_status_name,
			       session.last_updated,
			       session.ip
			  from session,
			       session_status,
			       user
			 where session.session_status_id = session_status.id
			   and session.user_id = user.id
			   and session.token = :token";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':token', $args["token"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'user_id' => $row->user_id,
						'user_name' => $row->user_name,
						'token' => $row->token,
						'begin' => strtotime($row->begin),
						'expire' => strtotime($row->expire),
						'end' => strtotime($row->end),
						'session_status_id' => $row->session_status_id,
						'session_status_name' => $row->session_status_name,
						'last_updated' => $row->last_updated,
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
	
	public function finalize_session(&$data, &$stat) {
		$session_status_id = SessionStatus::FINALIZADA;
		
		$st_update = $this->connection->prepare("update session set end = now(), session_status_id = :session_status_id, last_updated = :last_updated, ip = :ip where id = :id");
		$st_update->bindParam(':session_status_id', $session_status_id);
		$st_update->bindParam(':last_updated', $data["last_updated"]);
		$st_update->bindParam(':ip', $data["ip"]);
		$st_update->bindParam(':id', $data["id"]);
		
		try {
			$st_update->execute();
		}
		catch (Exception $e) {
			$this->log->save("Statement => " . print_r($st_update->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Exception => " . $e->getMessage(), __FILE__, __METHOD__, __LINE__);
			
			$stat["success"] = "false";
			$stat["message"] = $e->getMessage();
			return;
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public function create_session(&$data, &$stat) {
		$session_status_id = SessionStatus::ATIVA;
		$token = md5(uniqid($data["user_id"], true));
		
		$st_insert = $this->connection->prepare("insert into session (user_id, token, begin, expire, session_status_id, session_authentication_id, last_updated, ip) values (:user_id, :token, now(), now(), :session_status_id, :session_authentication_id, :last_updated, :ip)");
		$st_insert->bindParam(':user_id', $data["user_id"]);
		$st_insert->bindParam(':token', $token);
		$st_insert->bindParam(':session_status_id', $session_status_id);
		$st_insert->bindParam(':session_authentication_id', $data["session_authentication_id"]);
		$st_insert->bindParam(':last_updated', $data["user_id"]);
		$st_insert->bindParam(':ip', $data["ip"]);
		
		try {
			$st_insert->execute();
		}
		catch (Exception $e) {
			$this->log->save("Statement => " . print_r($st_insert->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Exception => " . $e->getMessage(), __FILE__, __METHOD__, __LINE__);
			
			$stat["success"] = "false";
			$stat["message"] = $e->getMessage();
			return;
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
		$stat["id"] = $this->connection->lastInsertId();
	}
	
	public function get_session_count() {
		$session_status_id = SessionStatus::ATIVA;
		
		$sql = "
			select count(*) count
			  from session
			 where session_status_id = :session_status_id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':session_status_id', $session_status_id);
		
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
		$dm = new Session();
		return $dm->get_session_count();
	}
}

?>