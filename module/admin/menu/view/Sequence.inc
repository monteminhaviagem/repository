<?php
namespace module\admin\menu\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_menu."/controller/Category.inc");

use module\admin\Admin;
use module\admin\menu\controller\Menu;
use module\admin\menu\controller\Category;

class Sequence extends Admin {
	
	const ID = '14e9ac6fa6ff3d5a0e3f41a5c2c186df';
	
	protected $parent_id;
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
		
		$this->init();
	}
	
	public function get_css_page() {
		return array(
			"nestable.css",
		);
	}
	
	public function get_js_page() {
		return array(
			"nestable.js"
		);
	}
	
	public function get_js() {
		return <<<EOD
			$(document).ready(function() {
				$('#submenu').nestable({
					maxDepth : 1
				});
				
				$("button").click(function(event) {
					$.ajax({
						type: 'POST',
						url: '/module/admin/menu/xhr/save_sequence.php',
						data: {
							submenu: JSON.stringify($('#submenu.dd').nestable('serialize'))
						},
						dataType: "json"
					})
					.done(function(data) {
						if (data.success == "true")
							location.reload();
						else
							alert(data.message);
					})
				});
				
				$('select').change(function() {
					reloadPage();
				});
			});
			
			function reloadPage() {
				$("form").submit();
			}
EOD;
	}
	
	public function get_content() {
		$controller = new Category();
		$category_option = $controller->get_category_option($this->parent_id);
		
		$service = new Menu();
		$submenu = $service->get_submenu($this->parent_id);
		
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="row">
					<div class="col-lg-12">
						<h1 class="page-header">Ordenação</h1>
					</div>
				</div>
				
				<form method="POST">
					<select name="parent_id">
{$category_option}
					</select>
				</form>
				
				<br>
				
				<button type="button" class="btn btn-outline btn-primary">Salvar</button>
				
				<br><br>
				
				<div class="dd" id="submenu">
{$submenu}
				</div>
			</div>
			<!-- PAGE CONTENT - END -->
EOD;
	}
	
	public function set_title() {
		$this->title = "Ordenação";
	}
	
	private function init() {
		$this->parent_id = $_POST["parent_id"] ?? 2;
	}
}

?>