<?php
namespace module\admin\log\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");

use module\admin\Admin;

class Log extends Admin {
	
	const ID = 'a6c7a82c8141a080c9c66bd52578d7cb';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {
		return array(
			"datepicker.css"
		);
	}
	
	public function get_js_page() {
		return array(
			"jquery-ui.js"
		);
	}
	
	public function get_js() {
		return <<<EOD
			function loadLog(date) {
				$.ajax({
					type: 'POST',
					url: '/module/admin/log/xhr/log.php',
					data: 'file_name=' + date + '.log',
					success: function(response) {
						$('textarea').val(response);
						$('textarea').scrollTop($('textarea')[0].scrollHeight - $('textarea').height());
					}
				});
			}
			
			$(function() {
				$("#datepicker").datepicker({
					dateFormat: "yymmdd",
					maxDate: 0,
					onSelect: function (date) {
						loadLog(date);
					}
				});
				
				loadLog($("#datepicker").datepicker().val());
			});
EOD;
	}
	
	public function get_css() {
		return <<<EOD
			textarea.form-control[readonly] {
				background-color: #21252b;
				color: #858d91;
				font-size: 11px;
				font-family: monospace !important;
			}
			
			.ui-datepicker { font-size: 9pt !important; }
EOD;
	}
	
	public function get_content() {
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="container-fluid">
					<div class="row">
						<div class="col-lg-12">
							<h1 class="page-header">Log</h1>
						</div>
					</div>
					
					<div class="row">
						<div class="col-lg-9">
							<textarea class="form-control" rows="25" readonly></textarea>
						</div>
						<div class="col-lg-3">
							<div id="datepicker"></div>
						</div>
					</div>
				</div>
			</div>
			<!-- PAGE CONTENT - END -->
EOD;
	}
	
	public function set_title() {
		$this->title = "Log";
	}
}

?>