<?php
namespace module\admin\menu\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_menu."/controller/Category.inc");

use module\admin\Admin;
use module\admin\menu\controller\Category;

class Category extends Admin {
	
	const ID = '0bac2f1aee7059a5e6477980937f7b4c';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
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
				$('#category').nestable({
					maxDepth : 2
				});
				
				$('#add-category').click(function(event) {
					$('.modal-content').load("/module/admin/menu/xhr/modal_category.php", function() {
						$('#modal').modal('show');
					});
				});
				
				$('#save-hierarchy').click(function(event) {
					save_hierarchy();
				});
				
				$("a[data-source='modal']").click(function(event) {
					$('.modal-content').load("/module/admin/menu/xhr/modal_category.php?id=" + $(this).attr('data-id'), function() {
						$('#modal').modal('show');
					});
					
					return false;
				});
			});
			
			function save() {
				$.ajax({
					type: "POST",
					url: "/module/admin/menu/xhr/save_category.php",
					data: $("form").serialize(),
					dataType: "json"
				})
				.done(function(data) {
					if (data.success == "true")
						location.reload();
					else
						alert(data.message);
				});
			}
			
			function save_hierarchy() {
				$.ajax({
					type: "POST",
					url: "/module/admin/menu/xhr/save_category_hierarchy.php",
					data: {
						category: JSON.stringify($('#category.dd').nestable('serialize'))
					},
					dataType: "json"
				})
				.done(function(data) {
					if (data.success == "true")
						location.reload();
					else
						alert(data.message);
				});
			}
EOD;
	}
	
	public function get_content() {
		$service = new Category();
		$category_nestable = $service->get_category_nestable();
		
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="row">
					<div class="col-lg-12">
						<h1 class="page-header">Categorias</h1>
					</div>
				</div>
				
				<button type="button" class="btn btn-outline btn-primary" id="add-category">Adicionar</button>
				<button type="button" class="btn btn-outline btn-primary" id="save-hierarchy">Salvar</button>
				
				<br>
				<br>
				
				<div class="dd" id="category">
{$category_nestable}
				</div>
				
				<!-- BEGIN MODAL -->
				<div id="modal" class="modal fade">
					<!-- BEGIN MODAL-DIALOG -->
					<div class="modal-dialog">
						<!-- BEGIN MODAL-CONTENT -->
						<div class="modal-content"></div>
						<!-- END MODAL-CONTENT -->
					</div>
					<!-- END MODAL-DIALOG -->
				</div>
				<!-- END MODAL -->
			</div>
			<!-- PAGE CONTENT - END -->
EOD;
	}
	
	public function set_title() {
		$this->title = "Categorias";
	}
}

?>