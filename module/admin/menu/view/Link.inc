<?php
namespace module\admin\menu\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");

use module\admin\Admin;

class Link extends Admin {
	
	const ID = '9d9798003a89ab321c8bff83c88a8ecb';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {
		return array(
			"dataTables.bootstrap.css",
			"responsive.bootstrap.css"
		);
	}
	
	public function get_js_page() {
		return array(
			"jquery.dataTables.js",
			"dataTables.bootstrap.js",
			"dataTables.responsive.js"
		);
	}
	
	public function get_js() {
		return <<<EOD
			$(document).ready(function() {
				var datatable = $('#datatable').dataTable({
					"ajax": "/module/admin/menu/xhr/datatable_link.php",
					"ordering": false,
					"paging": true,
					"searching": true,
					"info": true,
					"columnDefs": [
						{"targets": -1, "data": null, "defaultContent": '<button type="button" class="btn btn-outline btn-primary btn-xs">Editar</button>'}
					],
					"lengthMenu": [[5, 10, 15, -1], [5, 10, 15, "All"]]
				}).api();
				
				$('#datatable tbody').on('click', 'button', function () {
					var data = datatable.row($(this).parents('tr')).data();
					
					$('.modal-content').load("/module/admin/menu/xhr/modal_link.php?link_id=" + data[0], function() {
						$('#modal').modal('show');
					});
				});
				
				$('#add-link').click(function(event) {
					$('.modal-content').load("/module/admin/menu/xhr/modal_link.php", function() {
						$('#modal').modal('show');
					});
				});
			});
			
			function save() {
				$.ajax({
					type: "POST",
					url: "/module/admin/menu/xhr/save_link.php",
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
EOD;
	}
	
	public function get_content() {
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="row">
					<div class="col-lg-12">
						<h1 class="page-header">Links</h1>
					</div>
				</div>
				
				<table id="datatable" class="table table-striped table-condensed" cellspacing="0" width="100%">
					<thead>
						<tr>
							<th><i class="fa fa-key"></i> ID</th>
							<th><i class="fa fa-pencil"></i> Nome</th>
							<th><i class="fa fa-laptop"></i> Página</th>
							<th><i class="fa fa-link"></i> URL</th>
							<th>&nbsp;</th>
						</tr>
					</thead>
				</table>
				
				<button type="button" class="btn btn-outline btn-primary" id="add-link">Adicionar</button>
				
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
		$this->title = "Links";
	}
}

?>