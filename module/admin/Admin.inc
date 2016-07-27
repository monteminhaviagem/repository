<?php
namespace module\admin;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Page.inc");
require_once($path_module_admin_menu."/controller/Menu.inc");

use module\common\Page;
use module\admin\menu\controller\Menu;

class Admin extends Page {
	protected $page_id;
	
	public function __construct($page_id) {
		parent::__construct($page_id);
		
		$this->$page_id = $page_id;
	}
	
	public function set_container_id() {
		$this->container_id = "wrapper";
	}
	
	public function get_js_common() {
		return array(
			"jquery.js",
			"bootstrap.js",
			"metisMenu.js",
			"admin-global.js"
		);
	}
	
	public function get_css_common() {
		return array(
			"bootstrap.css",
			"metisMenu.css",
			"admin-global.css",
			"font-awesome.css"
		);
	}
	
	public function get_header() {
		$controller = new Menu();
		$menu = $controller->get_menu($_SESSION['profile_id']);
		
		return <<<EOD
			<!-- NAVIGATION - BEGIN -->
			<nav class="navbar navbar-default navbar-static-top" role="navigation" style="margin-bottom: 0">
				<div class="navbar-header">
					<button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
						<span class="sr-only">Toggle navigation</span>
						<span class="icon-bar"></span>
						<span class="icon-bar"></span>
						<span class="icon-bar"></span>
					</button>
				</div>
				
				<div class="navbar-default sidebar" role="navigation">
					<div class="sidebar-nav navbar-collapse">
{$menu}
					</div>
				</div>
			</nav>
			<!-- NAVIGATION - END -->

EOD;
	}
	
	public function get_footer() {}
}

?>