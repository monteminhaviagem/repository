<?php
namespace module\admin\access\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");

use PDO;
use module\common\Log;
use module\common\Database;

class Page extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_page($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'page.id';
		
		$sql = "
			select page.id,
			       page.name,
			       page.url,
			       page.file,
			       page.class,
			       page.namespace,
			       page.parent_id,
			       page.page_type_id,
			       page_type.name page_type_name
			  from page,
			       page_type
			 where page.page_type_id = page_type.id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						"id" => $row->id,
						"name" => $row->name,
						"url" => $row->url,
						"file" => $row->file,
						"class" => $row->class,
						"namespace" => $row->namespace,
						"parent_id" => $row->parent_id,
						"page_type_id" => $row->page_type_id,
						"page_type_name" => $row->page_type_name
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_page_available($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'page.id';
		
		$sql = "
			select page.id,
			       page.name,
			       page.url,
			       page.file,
			       page.class,
			       page.namespace,
			       page.parent_id,
			       page.page_type_id,
			       page_type.name page_type_name
			  from page,
			       page_type
			 where page.page_type_id = page_type.id
			   and not exists (select 1
			                     from menu
			                    where menu.page_id = page.id)
			 order by $order";
	
		$rs = $this->connection->prepare($sql);
	
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
							"id" => $row->id,
							"name" => $row->name,
							"url" => $row->url,
							"file" => $row->file,
							"class" => $row->class,
							"namespace" => $row->namespace,
							"parent_id" => $row->parent_id,
							"page_type_id" => $row->page_type_id,
							"page_type_name" => $row->page_type_name
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_page_id($args, &$data) {
		$data = array();
		
		$sql = "
			select page.id,
			       page.name,
			       page.url,
			       page.file,
			       page.class,
			       page.namespace,
			       page.parent_id,
			       page.page_type_id,
			       page_type.name page_type_name,
			       page.created,
			       page.modified,
			       page.last_updated,
			       user.name last_updated_name,
			       page.ip
			  from page,
			       page_type,
			       user
			 where page.page_type_id = page_type.id
			   and page.last_updated = user.id
			   and page.id = :id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						"id" => $row->id,
						"name" => $row->name,
						"url" => $row->url,
						"file" => $row->file,
						"class" => $row->class,
						"namespace" => $row->namespace,
						"parent_id" => $row->parent_id,
						"page_type_id" => $row->page_type_id,
						"page_type_name" => $row->page_type_name,
						"created" => strtotime($row->created),
						"modified" => strtotime($row->modified),
						"last_updated" => $row->last_updated,
						"last_updated_name" => $row->last_updated_name,
						"ip" => $row->ip
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_page_url($args, &$data) {
		$data = array();
		
		$sql = "
			select id,
			       name,
			       url,
			       file,
			       class,
			       namespace,
			       parent_id
			  from page
			 where url = :url";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':url', $args["url"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						"id" => $row->id,
						"name" => $row->name,
						"url" => $row->url,
						"file" => $row->file,
						"class" => $row->class,
						"namespace" => $row->namespace,
						"parent_id" => $row->parent_id
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_page_profile($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'page.id';
		
		$sql = "
			select page.id,
			       page.name,
			       page.url,
			       page.file,
			       page.class,
			       page.namespace,
			       page.parent_id
			  from page,
			       profile_page
			 where page.id = profile_page.page_id
			   and profile_page.profile_id = :profile_id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':profile_id', $args["profile_id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						"id" => $row->id,
						"name" => $row->name,
						"url" => $row->url,
						"file" => $row->file,
						"class" => $row->class,
						"namespace" => $row->namespace,
						"parent_id" => $row->parent_id
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_page_user($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'page.id';
		
		$sql = "
			select page.id,
			       page.name,
			       page.url,
			       page.file,
			       page.class,
			       page.namespace,
			       page.parent_id,
			       page.module_id
			  from page,
			       profile_page,
			       user
			 where page.id = profile_page.page_id
			   and profile_page.profile_id = user.profile_id
			   and user.id = :user_id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':user_id', $args["user_id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						"id" => $row->id,
						"name" => $row->name,
						"url" => $row->url,
						"file" => $row->file,
						"class" => $row->class,
						"namespace" => $row->namespace,
						"parent_id" => $row->parent_id
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function set_page(&$data, &$stat) {
		$st_update = $this->connection->prepare("update page set url = :url, modified = now(), last_updated = :last_updated, ip = :ip where id = :id");
		$st_update->bindParam(':url', $data["url"]);
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
		
		$st_delete = $this->connection->prepare("delete from profile_page where page_id = :page_id");
		$st_delete->bindParam(':page_id', $data["id"]);
			
		if (!$st_delete->execute()) {
			$this->log->save("Statement => " . print_r($st_delete->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			
			$stat["success"] = "false";
			$stat["message"] = $st_delete->errorInfo();
			return;
		}
		
		if (count($data["profile"]) > 0) {
			for ($i=0; $i<count($data["profile"]); $i++) {
				$st_insert_profile = $this->connection->prepare("insert into profile_page (profile_id, page_id) values (:profile_id, :page_id)");
				$st_insert_profile->bindParam(':profile_id', $data["profile"][$i]);
				$st_insert_profile->bindParam(':page_id', $data["id"]);
				
				if (!$st_insert_profile->execute()) {
					$this->log->save("Statement => " . print_r($st_insert_profile->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
					$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
					
					$stat["success"] = "false";
					$stat["message"] = $st_insert_profile->errorInfo();
					
					return;
				}
			}
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public static function get_url($id) {
		$args = array();
		$data = array();
		
		$args["id"] = $id;
		
		$dm = new Page();
		$dm->get_page_id(
			$args,
			$data
		);
		
		return $data["url"];
	}
	
	public static function get_file($id) {
		$args = array();
		$data = array();
		
		$args["id"] = $id;
		
		$dm = new Page();
		$dm->get_page_id(
			$args,
			$data
		);
		
		return $data["file"];
	}
	
	public static function get_class($id) {
		$args = array();
		$data = array();
		
		$args["id"] = $id;
		
		$dm = new Page();
		$dm->get_page_id(
			$args,
			$data
		);
		
		return $data["class"];
	}
}

?>