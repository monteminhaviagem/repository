<?php
namespace module\admin\menu\controller;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_admin_menu."/dm/Menu.inc");

use module\admin\menu\dm\Menu as dm_Menu;

class Category {
	
	protected $category;
	protected $category_nestable;
	protected $category_option;
	
	public function __construct() {}
	
	public function set_category(&$category, $parent_id) {
		$args = array();
		$data = array();
		
		$args["parent_id"] = $parent_id;
		
		$dm = new dm_Menu();
		$dm->get_category_parent(
			$args,
			$data
		);
		
		for ($i=0; $i<count($data); $i++) {
			$category[$data[$i]["id"]] = array();
			$category[$data[$i]["id"]]["id"] = $data[$i]["id"];
			$category[$data[$i]["id"]]["name"] = $data[$i]["name"];
			$category[$data[$i]["id"]]["menu_type_id"] = $data[$i]["menu_type_id"];
			$category[$data[$i]["id"]]["sequence"] = $data[$i]["sequence"];
			$category[$data[$i]["id"]]["parent_id"] = $data[$i]["parent_id"];
			$category[$data[$i]["id"]]["page_id"] = $data[$i]["page_id"];
			$category[$data[$i]["id"]]["target"] = $data[$i]["target"];
			$category[$data[$i]["id"]]["icon"] = $data[$i]["icon"];
			//$category[$data[$i]["id"]]["url"] = $data[$i]["url"];
			$category[$data[$i]["id"]]["itens"] = array();
			
			$this->set_category($category[$data[$i]["id"]]["itens"], $data[$i]["id"]);
		}
	}
	
	public function set_category_nestable(&$itens, $ident, $level) {
		if (count($itens) > 0) {
			$arrKeys = array_keys($itens);
			
			if ($level == 1)
				$this->category_nestable .= str_pad("", $ident+$level, " ", STR_PAD_LEFT) . "<ol class=\"dd-list\">\n";
			else
				$this->category_nestable .= str_pad("", $ident+$level, " ", STR_PAD_LEFT) . "<ol class=\"dd-list\">\n";
			
			for ($i = 0; $i<count($arrKeys); $i++) {
				if (count($itens[$arrKeys[$i]]["itens"]) > 0) {
					$this->category_nestable .= str_pad("", $ident+$level+2, " ", STR_PAD_LEFT) . "<li class=\"dd-item dd3-item\" data-id=\"".$itens[$arrKeys[$i]]["id"]."\"><div class=\"dd-handle dd3-handle\">Drag</div><div class=\"dd3-content\">".$itens[$arrKeys[$i]]["name"]." <a data-source=\"modal\" data-id=".$itens[$arrKeys[$i]]["id"]." href=\"#\"><i class=\"fa fa-edit\"></i></a></div>\n";
					$this->set_category_nestable($itens[$arrKeys[$i]]["itens"], $ident, ($level+4));
					$this->category_nestable .= str_pad("", $ident+$level+2, " ", STR_PAD_LEFT) . "</li>\n";
				}
				else
					$this->category_nestable .= str_pad("", $ident+$level+2, " ", STR_PAD_LEFT) . "<li class=\"dd-item dd3-item\" data-id=\"".$itens[$arrKeys[$i]]["id"]."\"><div class=\"dd-handle dd3-handle\">Drag</div><div class=\"dd3-content\">".$itens[$arrKeys[$i]]["name"]." <a data-source=\"modal\" data-id=".$itens[$arrKeys[$i]]["id"]." href=\"#\"><i class=\"fa fa-edit\"></i></a></div></li>\n";
			}
			
			$this->category_nestable .= str_pad("", $ident+$level, " ", STR_PAD_LEFT) . "</ol>";
			
			if ($level > 1)
				$this->category_nestable .= "\n";
		}
	}
	
	public function set_category_option(&$itens, $pad, $ident, $level, $parent_id) {
		if (count($itens) > 0) {
			$arrKeys = array_keys($itens);
			
			for ($i=0; $i<count($arrKeys); $i++) {
				$prefix = "";
				
				for($l=1; $l<$level; $l++) {
					$prefix .= "&nbsp;&nbsp;&nbsp;&nbsp;";
				}
				
				$selected = ($parent_id == $itens[$arrKeys[$i]]["id"]) ? "selected" : "";
				
				$this->category_option .= str_pad("", $pad+$ident, " ", STR_PAD_LEFT) . "<option value=\"".$itens[$arrKeys[$i]]["id"]."\" ".$selected.">".$prefix.$itens[$arrKeys[$i]]["name"]."</option>\n";
				
				if (count($itens[$arrKeys[$i]]["itens"]) > 0)
					$this->set_category_option($itens[$arrKeys[$i]]["itens"], $pad, $ident, ($level+1), $parent_id);
			}
		}
	}
	
	public function get_category_nestable() {
		$this->set_category($this->category, 1);
		
		$this->set_category_nestable($this->category[2]["itens"], 15, 1);
		
		return $this->category_nestable;
	}
	
	public function get_category_option($parent_id) {
		$this->set_category($this->category, 0);
		
		$this->set_category_option($this->category[1]["itens"], 40, 8, 1, $parent_id);
		
		return $this->category_option;
	}
}

?>