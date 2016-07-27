<?php
namespace module\admin\access\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");

use module\admin\Admin;

class Session extends Admin {
	
	const ID = 'ae7b0461e36583341dd5fde32ae6f183';
	
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
					"ajax": "/module/admin/access/xhr/datatable_session.php",
					"ordering": false,
					"paging": true,
					"searching": true,
					"info": true,
					"columnDefs": [
						{"targets": -1, "data": null, "defaultContent": '<button type="button" class="btn btn-outline btn-primary btn-xs">Finalizar</button>'}
					],
					"lengthMenu": [[5, 10, 15, -1], [5, 10, 15, "All"]]
				}).api();
			});
EOD;
	}
	
	public function get_content() {
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="row">
					<div class="col-lg-12">
						<h1 class="page-header">Sessões Ativas</h1>
					</div>
				</div>
				
				<table id="datatable" class="table table-striped table-condensed" cellspacing="0" width="100%">
					<thead>
						<tr>
							<th style="width: 40px;"><i class="fa fa-key"></i> ID</th>
							<th><i class="fa fa-pencil"></i> Nome</th>
							<th><i class="fa fa-tag"></i> Tipo</th>
							<th><i class="fa fa-lock"></i> Token</th>
							<th style="width: 100px;">&nbsp;</th>
						</tr>
					</thead>
				</table>
EOD;
	}
	
	public function set_title() {
		$this->title = "Sessões";
	}
}

?>