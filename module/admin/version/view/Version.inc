<?php
namespace module\admin\version\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");

use module\admin\Admin;

class Version extends Admin {
	
	const ID = '83412d99b65a3efb27cd08e25e24469d';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {
		return array(
			"dataTables.bootstrap.css",
			"responsive.bootstrap.css",
			"picklist.css"
		);
	}
	
	public function get_js_page() {
		return array(
			"jquery.dataTables.js",
			"dataTables.bootstrap.js",
			"dataTables.responsive.js",
			"jquery-ui.js",
			"picklist.js"
		);
	}
	
	public function get_js() {
		return <<<EOD
			$(document).ready(function() {
				var datatable = $('#datatable').dataTable({
					"ajax": "/module/admin/version/xhr/datatable_version.php",
					"ordering": false,
					"paging": true,
					"searching": true,
					"info": true,
					"columnDefs": [
						{"targets": -1, "data": null, "defaultContent": '<button type="button" class="btn btn-outline btn-primary btn-xs">Changelog</button>'}
					],
					"lengthMenu": [[5, 10, 15, -1], [5, 10, 15, "All"]]
				}).api();
				
				$('#datatable tbody').on('click', 'button', function () {
					var data = datatable.row($(this).parents('tr')).data();
					
					$('#frm_changelog #version_id').val(data[0]);
					$('#frm_changelog').attr('action', '/admin/version/changelog');
					$('#frm_changelog').submit();
				});
			});
			
			function save() {
				$.ajax({
					type: "POST",
					url: "/module/admin/access/xhr/save_user.php",
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
				<form id="frm_changelog" method="post">
					<input type="hidden" id="version_id" name="version_id">
				</form>
				
				<div class="row">
					<div class="col-lg-12">
						<h1 class="page-header">Versões</h1>
					</div>
				</div>
				
				<table id="datatable" class="table table-striped table-condensed" cellspacing="0" width="100%">
					<thead>
						<tr>
							<th style="width: 40px;">ID</th>
							<th><i class="fa fa-code-fork"></i> Tag</th>
							<th><i class="fa fa-calendar"></i> Recebida</th>
							<th><i class="fa fa-calendar"></i> Checkout</th>
							<th><i class="fa fa-check-square-o"></i> Versão Atual</th>
							<th style="width: 100px;">&nbsp;</th>
						</tr>
					</thead>
				</table>
				
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
		$this->title = "Versões";
	}
}

?>