<?php
namespace module\admin\menu\controller;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_admin_menu."/dm/Menu.inc");
require_once($path_module_admin_access."/dm/Profile.inc");
require_once($path_module_admin_access."/dm/UserType.inc");

use PDO;
use Exception;
use module\common\Log;
use module\common\Database;
use module\admin\menu\dm\Menu;
use module\admin\menu\dm\MenuType;
use module\admin\access\dm\Profile;
use module\admin\access\dm\UserType;

class Menu extends Database {
	
	protected $menu;
	protected $menu_admin;
	protected $submenu;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function set_menu_profile_parent($profile_id, $parent_id) {
		$sql = "
			select id,
			       parent_id
			  from menu
			 where id = :parent_id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':parent_id', $parent_id);
		$rs->execute();
		
		$row = $rs->fetch(PDO::FETCH_OBJ);
		
		$sql_insert = "insert into menu_profile (profile_id, menu_id) values (:profile_id, :menu_id)";
		
		$rs_insert = $this->connection->prepare($sql_insert);
		$rs_insert->bindParam(':profile_id', $profile_id);
		$rs_insert->bindParam(':menu_id', $row->id);
		
		try {
			$rs_insert->execute();
		} catch (Exception $e) {}
		
		if ($row->parent_id > 0)
			$this->set_menu_profile_parent($profile_id, $row->parent_id);
	}
	
	public function set_menu_profile($profile_id) {
		$args = array();
		$data = array();
		
		$args["profile_id"] = $profile_id;
		
		$dm = new Menu();
		$dm->get_link_profile(
			$args,
			$data
		);
		
		$st_delete = $this->connection->prepare("delete from menu_profile where profile_id = :profile_id");
		$st_delete->bindParam(':profile_id', $profile_id);
		
		if (!$st_delete->execute()) {
			$this->log->save("Statement => " . print_r($st_delete->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
		
		$sql_insert = "insert into menu_profile (profile_id, menu_id) values (:profile_id, :menu_id)";
		$rs_insert = $this->connection->prepare($sql_insert);
		
		$this->connection->beginTransaction();
		
		for ($i=0; $i<count($data); $i++) {
			$rs_insert->bindParam(':profile_id', $profile_id);
			$rs_insert->bindParam(':menu_id', $data[$i]["id"]);
			$rs_insert->execute();
			
			$this->set_menu_profile_parent($profile_id, $data[$i]["parent_id"]);
		}
		
		$this->connection->commit();
	}
	
	public function set_menu(&$menu, $profile_id, $parent_id) {
		$sql = "
			select distinct
			       menu_view.id,
			       menu_view.name,
			       menu_view.menu_type_id,
			       menu_view.sequence,
			       menu_view.parent_id,
			       menu_view.page_id,
			       menu_view.target,
			       menu_view.icon,
			       page.url
			  from (select menu.id,
			               menu.name,
			               menu.menu_type_id,
			               menu.sequence,
			               menu.parent_id,
			               menu.page_id,
			               menu.target,
			               menu.icon
			          from menu,
			               menu_profile
			         where menu.id = menu_profile.menu_id
			           and menu_profile.profile_id = :profile_id) menu_view left join page on (menu_view.page_id = page.id)
			 where menu_view.parent_id = :parent_id
			 order by isnull(menu_view.sequence), menu_view.sequence";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':profile_id', $profile_id);
		$rs->bindParam(':parent_id', $parent_id);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					if ($row->menu_type_id == MenuType::CATEGORIA) {
						$menu[$row->id] = array();
						$menu[$row->id]["id"] = $row->id;
						$menu[$row->id]["name"] = $row->name;
						$menu[$row->id]["menu_type_id"] = $row->menu_type_id;
						$menu[$row->id]["sequence"] = $row->sequence;
						$menu[$row->id]["parent_id"] = $row->parent_id;
						$menu[$row->id]["page_id"] = $row->page_id;
						$menu[$row->id]["target"] = $row->target;
						$menu[$row->id]["icon"] = $row->icon;
						$menu[$row->id]["url"] = $row->url;
						$menu[$row->id]["itens"] = array();
						
						$this->set_menu($menu[$row->id]["itens"], $profile_id, $row->id);
					}
					else {
						$menu[$row->id] = array(
							"id" => $row->id,
							"name" => $row->name,
							"menu_type_id" => $row->menu_type_id,
							"sequence" => $row->sequence,
							"parent_id" => $row->parent_id,
							"page_id" => $row->page_id,
							"target" => $row->target,
							"icon" => $row->icon,
							"url" => $row->url,
							"itens" => array()
						);
					}
				}
			}
		}
	}
	
	public function set_menu_admin(&$itens, $pad, $space, $ident, $level) {
		if (count($itens) > 0) {
			$arrKeys = array_keys($itens);
			
			if ($level == 1)
				$this->menu_admin .= str_pad("", $pad+$space, " ", STR_PAD_LEFT) . "<ul class=\"nav\" id=\"side-menu\">\n";
			else if ($level == 2)
				$this->menu_admin .= str_pad("", $pad+$space, " ", STR_PAD_LEFT) . "<ul class=\"nav nav-second-level\">\n";
			else if ($level == 3)
				$this->menu_admin .= str_pad("", $pad+$space, " ", STR_PAD_LEFT) . "<ul class=\"nav nav-third-level\">\n";
			
			for ($i = 0; $i<count($arrKeys); $i++) {
				if ($itens[$arrKeys[$i]]["icon"] != "")
					$icon = "<i class=\"fa ".$itens[$arrKeys[$i]]["icon"]."\"></i>";
				else
					$icon = "";
				
				if (count($itens[$arrKeys[$i]]["itens"]) > 0) {
					$this->menu_admin .= str_pad("", $pad+$space+$ident, " ", STR_PAD_LEFT) . "<li><a href=\"#\">".$icon." ".$itens[$arrKeys[$i]]["name"]."<span class=\"fa arrow\"></span></a>\n";
					$this->set_menu_admin($itens[$arrKeys[$i]]["itens"], $pad, ($space+($ident*2)), $ident, ($level+1));
					$this->menu_admin .= str_pad("", $pad+$space+$ident, " ", STR_PAD_LEFT) . "</li>\n";
				}
				else
					$this->menu_admin .= str_pad("", $pad+$space+$ident, " ", STR_PAD_LEFT) . "<li><a href=\"".$itens[$arrKeys[$i]]["url"]."\" target=\"".$itens[$arrKeys[$i]]["target"]."\">".$icon." ".$itens[$arrKeys[$i]]["name"]."</a></li>\n";
			}
			
			// Add Logout
			if ($level == 1)
				$this->menu_admin .= str_pad("", $pad+$space+$ident, " ", STR_PAD_LEFT) . "<li><a href=\"/logout\"><i class=\"fa fa-sign-out\"></i> Sair</a></li>\n";
			
			$this->menu_admin .= str_pad("", $pad+$space, " ", STR_PAD_LEFT) . "</ul>";
			
			if ($level > 1)
				$this->menu_admin .= "\n";
		}
	}
	
	public function get_menu($profile_id) {
		$this->set_menu_profile($profile_id);
		
		$this->set_menu($this->menu, $profile_id, 1);
		
		$user_type_id = Profile::get_user_type_id($profile_id);
		
		if ($user_type_id == UserType::ADMIN) {
			$this->set_menu_admin($this->menu[2]["itens"], 48, 0, 4, 1);
			return $this->menu_admin;
		}
	}
	
	public function set_submenu(&$menu, $parent_id) {
		$sql = "
			select menu.id,
			       menu.name,
			       menu.menu_type_id,
			       menu.sequence,
			       menu.parent_id,
			       menu.page_id,
			       menu.target,
			       menu.icon,
			       page.url
			  from menu left join page on (menu.page_id = page.id)
			 where menu.parent_id = :parent_id
			 order by isnull(menu.sequence), menu.sequence";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':parent_id', $parent_id);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$menu[$row->id] = array();
					$menu[$row->id]["id"] = $row->id;
					$menu[$row->id]["name"] = $row->name;
					$menu[$row->id]["menu_type_id"] = $row->menu_type_id;
					$menu[$row->id]["sequence"] = $row->sequence;
					$menu[$row->id]["parent_id"] = $row->parent_id;
					$menu[$row->id]["page_id"] = $row->page_id;
					$menu[$row->id]["target"] = $row->target;
					$menu[$row->id]["icon"] = $row->icon;
					$menu[$row->id]["url"] = $row->url;
					$menu[$row->id]["itens"] = array();
				}
			}
		}
	}
	
	public function set_submenu_nestable(&$itens, $space) {
		if (count($itens) > 0) {
			$arrKeys = array_keys($itens);
			
			$this->submenu = str_pad("", $space, " ", STR_PAD_LEFT) . "<ol class=\"dd-list\">\n";
			
			for ($i=0; $i<count($arrKeys); $i++) {
				$this->submenu .= str_pad("", $space+2, " ", STR_PAD_LEFT) . "<li class=\"dd-item dd3-item\" data-id=\"".$itens[$arrKeys[$i]]["id"]."\"><div class=\"dd-handle dd3-handle\">Drag</div><div class=\"dd3-content\">".$itens[$arrKeys[$i]]["name"]."</div></li>\n";
			}
			
			$this->submenu .= str_pad("", $space, " ", STR_PAD_LEFT) . "</ol>";
		}
	}
	
	public function get_submenu($parent_id) {
		$this->set_submenu($this->menu, $parent_id);
		
		$this->set_submenu_nestable($this->menu, 32);
		
		return $this->submenu;
	}
}

?>