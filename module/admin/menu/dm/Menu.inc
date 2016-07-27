<?php
namespace module\admin\menu\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");
require_once($path_module_admin_menu."/dm/MenuType.inc");

use PDO;
use Exception;
use module\common\Log;
use module\common\Database;
use module\admin\menu\dm\MenuType;

class Menu extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_category_parent($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'menu.id';
		
		$sql = "
			select menu.id,
			       menu.name,
			       menu.menu_type_id,
			       menu.sequence,
			       menu.parent_id,
			       menu.page_id,
			       menu.target,
			       menu.icon
			  from menu
			 where menu.menu_type_id = :menu_type_id
			   and menu.parent_id = :parent_id
			 order by $order";
		
		$menu_type_id = MenuType::CATEGORIA;
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':menu_type_id', $menu_type_id);
		$rs->bindParam(':parent_id', $args["parent_id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'name' => $row->name,
						'menu_type_id' => $row->menu_type_id,
						'sequence' => $row->sequence,
						'parent_id' => $row->parent_id,
						'page_id' => $row->page_id,
						'target' => $row->target,
						'icon' => $row->icon
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_category_id($args, &$data) {
		$data = array();
		
		$sql = "
			select menu.id,
			       menu.name,
			       menu.menu_type_id,
			       menu.sequence,
			       menu.parent_id,
			       menu.page_id,
			       menu.target,
			       menu.icon,
			       menu.created,
			       menu.modified,
			       menu.last_updated,
			       user.name last_updated_name,
			       menu.ip
			  from menu,
			       user
			 where menu.last_updated = user.id
			   and menu.menu_type_id = :menu_type_id
			   and menu.id = :id";
		
		$menu_type_id = MenuType::CATEGORIA;
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':menu_type_id', $menu_type_id);
		$rs->bindParam(':id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'name' => $row->name,
						'menu_type_id' => $row->menu_type_id,
						'sequence' => $row->sequence,
						'parent_id' => $row->parent_id,
						'page_id' => $row->page_id,
						'target' => $row->target,
						'icon' => $row->icon,
						'created' => strtotime($row->created),
						'modified' => strtotime($row->modified),
						'last_updated' => $row->last_updated,
						'last_updated_name' => $row->last_updated_name,
						'ip' => $row->ip,
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_link($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $$args["order"] : 'menu.id';
		$include_page = (isset($args["include_page"]) && $args["include_page"] != "") ? $args["include_page"] : 'false';
		
		$sql = "
			select id,
			       name,
			       menu_type_id,
			       sequence,
			       parent_id,
			       page_id,
			       target,
			       icon
			  from menu
			 where menu_type_id = :menu_type_id
			 order by $order";
		
		$menu_type_id = MenuType::LINK;
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':menu_type_id', $menu_type_id);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$page = array();
						
					if ($include_page == 'true') {
						$sql = "
							select id,
							       name,
							       url,
							       file,
							       class,
							       namespace,
							       parent_id,
							       page_type_id
							  from page
							 where id = :page_id";
						
						$rs_page = $this->connection->prepare($sql);
						$rs_page->bindParam(':page_id', $row->page_id);
						
						if ($rs_page->execute()) {
							if ($rs_page->rowCount() > 0) {
								if ($row_page = $rs_page->fetch(PDO::FETCH_OBJ)) {
									$page = array(
										"id" => $row_page->id,
										"name" => $row_page->name,
										"url" => $row_page->url,
										"file" => $row_page->file,
										"class" => $row_page->class,
										"namespace" => $row_page->namespace,
										"parent_id" => $row_page->parent_id,
										"page_type_id" => $row_page->page_type_id
									);
								}
							}
						}
						else{
							$this->log->save("Statement => " . print_r($rs_page->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
							$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
						}
					}
					
					$data[] = array(
						'id' => $row->id,
						'name' => $row->name,
						'menu_type_id' => $row->menu_type_id,
						'sequence' => $row->sequence,
						'parent_id' => $row->parent_id,
						'page_id' => $row->page_id,
						'target' => $row->target,
						'icon' => $row->icon,
						'page' => $page
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_link_id($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $$args["order"] : 'menu.id';
		$include_page = (isset($args["include_page"]) && $args["include_page"] != "") ? $args["include_page"] : 'false';
		
		$sql = "
			select menu.id,
			       menu.name,
			       menu.menu_type_id,
			       menu.sequence,
			       menu.parent_id,
			       menu.page_id,
			       menu.target,
			       menu.icon,
			       menu.created,
			       menu.modified,
			       menu.last_updated,
			       user.name last_updated_name,
			       menu.ip
			  from menu,
			       user
			 where menu.last_updated = user.id
			   and menu.id = :id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				if ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$page = array();
					
					if ($include_page == 'true') {
						$sql = "
							select id,
							       name,
							       url,
							       file,
							       class,
							       namespace,
							       parent_id,
							       page_type_id
							  from page
							 where id = :page_id";
						
						$rs_page = $this->connection->prepare($sql);
						$rs_page->bindParam(':page_id', $row->page_id);
						
						if ($rs_page->execute()) {
							if ($rs_page->rowCount() > 0) {
								if ($row_page = $rs_page->fetch(PDO::FETCH_OBJ)) {
									$page = array(
											"id" => $row_page->id,
											"name" => $row_page->name,
											"url" => $row_page->url,
											"file" => $row_page->file,
											"class" => $row_page->class,
											"namespace" => $row_page->namespace,
											"parent_id" => $row_page->parent_id,
											"page_type_id" => $row_page->page_type_id
									);
								}
							}
						}
						else{
							$this->log->save("Statement => " . print_r($rs_page->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
							$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
						}
					}
					
					$data = array(
						'id' => $row->id,
						'name' => $row->name,
						'menu_type_id' => $row->menu_type_id,
						'sequence' => $row->sequence,
						'parent_id' => $row->parent_id,
						'page_id' => $row->page_id,
						'target' => $row->target,
						'icon' => $row->icon,
						'created' => strtotime($row->created),
						'modified' => strtotime($row->modified),
						'last_updated' => $row->last_updated,
						'last_updated_name' => $row->last_updated_name,
						'ip' => $row->ip,
						'page' => $page
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_link_profile($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $$args["order"] : 'menu.id';
		$include_page = (isset($args["include_page"]) && $args["include_page"] != "") ? $args["include_page"] : 'false';
		
		$sql = "
			select menu.id,
			       menu.name,
			       menu.menu_type_id,
			       menu.sequence,
			       menu.parent_id,
			       menu.page_id,
			       menu.target,
			       menu.icon
			  from menu,
			       profile_page
			 where menu.page_id = profile_page.page_id
			   and menu.menu_type_id = :menu_type_id
			   and profile_page.profile_id = :profile_id
			 order by $order";
		
		$menu_type_id = MenuType::LINK;
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':menu_type_id', $menu_type_id);
		$rs->bindParam(':profile_id', $args["profile_id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$page = array();
					
					if ($include_page == 'true') {
						$sql = "
							select id,
							       name,
							       url,
							       file,
							       class,
							       namespace,
							       parent_id,
							       page_type_id
							  from page
							 where id = :page_id";
						
						$rs_page = $this->connection->prepare($sql);
						$rs_page->bindParam(':page_id', $row->page_id);
						
						if ($rs_page->execute()) {
							if ($rs_page->rowCount() > 0) {
								if ($row_page = $rs_page->fetch(PDO::FETCH_OBJ)) {
									$page = array(
										"id" => $row_page->id,
										"name" => $row_page->name,
										"url" => $row_page->url,
										"file" => $row_page->file,
										"class" => $row_page->class,
										"namespace" => $row_page->namespace,
										"parent_id" => $row_page->parent_id,
										"page_type_id" => $row_page->page_type_id
									);
								}
							}
						}
						else{
							$this->log->save("Statement => " . print_r($rs_page->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
							$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
						}
					}
					
					$data[] = array(
						'id' => $row->id,
						'name' => $row->name,
						'menu_type_id' => $row->menu_type_id,
						'sequence' => $row->sequence,
						'parent_id' => $row->parent_id,
						'page_id' => $row->page_id,
						'target' => $row->target,
						'icon' => $row->icon,
						'page' => $page
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function set_sequence($data, &$stat) {
		$st_update = $this->connection->prepare("update menu set sequence = :sequence where id = :id");
		
		$this->connection->beginTransaction();
		
		for ($i=0; $i<count($data); $i++) {
			$sequence = ($i + 1);
			
			$st_update->bindParam(':sequence', $sequence);
			$st_update->bindParam(':id', $data[$i]["id"]);
			
			try {
				$st_update->execute();
			}
			catch (Exception $e) {
				$this->log->save("Statement => " . print_r($st_update->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_update->errorInfo();
				$this->connection->rollBack();
				return;
			}
		}
		
		$this->connection->commit();
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public function set_category_hierarchy($data, &$stat) {
		$st_update = $this->connection->prepare("update menu set parent_id = :parent_id, modified = now(), last_updated = :last_updated, ip = :ip where id = :id");
		
		$st_update->bindParam(':parent_id', $data["parent_id"]);
		$st_update->bindParam(':id', $data["id"]);
		$st_update->bindParam(':last_updated', $data["last_updated"]);
		$st_update->bindParam(':ip', $data["ip"]);
		
		try {
			$st_update->execute();
		}
		catch (Exception $e) {
			$this->log->save("Statement => " . print_r($st_update->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			
			$stat["success"] = "false";
			$stat["message"] = $st_update->errorInfo();
			return;
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public function set_category(&$data, &$stat) {
		if (is_null($data["id"])) {
			$menu_type_id = MenuType::CATEGORIA;
			$parent_id = 2;
			
			$st_insert = $this->connection->prepare("insert into menu (name, menu_type_id, parent_id, icon, created, modified, last_updated, ip) values (:name, :menu_type_id, :parent_id, :icon, now(), now(), :last_updated, :ip)");
			$st_insert->bindParam(':name', $data["name"]);
			$st_insert->bindParam(':menu_type_id', $menu_type_id);
			$st_insert->bindParam(':parent_id', $parent_id);
			$st_insert->bindParam(':icon', $data["icon"]);
			$st_insert->bindParam(':last_updated', $data["last_updated"]);
			$st_insert->bindParam(':ip', $data["ip"]);
			
			try {
				$st_insert->execute();
			}
			catch (Exception $e) {
				$this->log->save("Statement => " . print_r($st_insert->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_insert->errorInfo();
				return;
			}
			
			$stat["id"] = $this->connection->lastInsertId();
		}
		else {
			$st_update = $this->connection->prepare("update menu set name = :name, icon = :icon, modified = now(), last_updated = :last_updated, ip = :ip where id = :id");
			$st_update->bindParam(':name', $data["name"]);
			$st_update->bindParam(':icon', $data["icon"]);
			$st_update->bindParam(':last_updated', $data["last_updated"]);
			$st_update->bindParam(':ip', $data["ip"]);
			$st_update->bindParam(':id', $data["id"]);
			
			try {
				$st_update->execute();
			}
			catch (Exception $e) {
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
	
	public function set_link(&$data, &$stat) {
		if (is_null($data["id"])) {
			$menu_type_id = MenuType::LINK;
			
			$st_insert = $this->connection->prepare("insert into menu (name, menu_type_id, parent_id, page_id, target, icon, created, modified, last_updated, ip) values (:name, :menu_type_id, :parent_id, :page_id, :target, :icon, now(), now(), :last_updated, :ip)");
			$st_insert->bindParam(':name', $data["name"]);
			$st_insert->bindParam(':menu_type_id', $menu_type_id);
			$st_insert->bindParam(':parent_id', $data["parent_id"]);
			$st_insert->bindParam(':page_id', $data["page_id"]);
			$st_insert->bindParam(':target', $data["target"]);
			$st_insert->bindParam(':icon', $data["icon"]);
			$st_insert->bindParam(':last_updated', $data["last_updated"]);
			$st_insert->bindParam(':ip', $data["ip"]);
			
			try {
				$st_insert->execute();
			}
			catch (Exception $e) {
				$this->log->save("Statement => " . print_r($st_insert->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_insert->errorInfo();
				return;
			}
			
			$stat["id"] = $this->connection->lastInsertId();
		}
		else {
			$st_update = $this->connection->prepare("update menu set name = :name, parent_id = :parent_id, page_id = :page_id, target = :target, icon = :icon, modified = now(), last_updated = :last_updated, ip = :ip where id = :id");
			$st_update->bindParam(':name', $data["name"]);
			$st_update->bindParam(':parent_id', $data["parent_id"]);
			$st_update->bindParam(':page_id', $data["page_id"]);
			$st_update->bindParam(':target', $data["target"]);
			$st_update->bindParam(':icon', $data["icon"]);
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
			
			$stat["id"] = $data["id"];
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
}

?>