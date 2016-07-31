<?php
namespace module\admin\version\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_version."/dm/Version.inc");

use module\admin\Admin;
use module\admin\version\dm\Version;

class Changelog extends Admin {
	
	const ID = 'df384f01d5fd1817c9b36fd9ba0c94d8';
	
	protected $version_id;
	protected $version_tag;
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
		
		$this->init();
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
	
	public function get_css() {
		return <<<EOD


/* The div inside modal-body is the key; there's where we put the content (which may need the vertical scrollbar) */
 .modal-body {
    min-height: 300px;
}
	.jira-issues  {
    max-height: 300px;
    overflow: auto;
}
EOD;
	}
	
	public function get_js() {
		return <<<EOD
			var version_id = "{$this->version_id}";
			var board_id = "";
			var sprint_id = "";
					var datatable;
			
			$(document).ready(function() {
				datatable = $('#datatable').dataTable({
					"ajax": "/module/admin/version/xhr/datatable_changelog.php",
					"ordering": false,
					"paging": false,
					"searching": false,
					"info": false,
					"columnDefs": [
						{"targets": -1, "data": null, "defaultContent": '<button type="button" class="btn btn-outline btn-primary btn-xs">Editar</button>'},
						{"targets": 0, "visible": false}
					]
				}).api();
				
				$('#datatable tbody').on('click', 'button', function () {
					var data = datatable.row($(this).parents('tr')).data();
					
					$('.modal-content').load("/module/admin/version/xhr/modal_issue.php?id=" + data[0], function() {
						$('#modal').modal('show');
					});
				});
				
				$('#add-issue').click(function(event) {
					$('.modal-content').load("/module/admin/version/xhr/modal_jira.php", function() {
						updateOptionBoard();
						
						$('#modal').modal('show');
						
						$("#board_id").change(function() {
							board_id = $(this).val();
							sprint_id = "";
							updateOptionSprint();
							updateJiraIssues();
						});
						
						$("#sprint_id").change(function() {
							sprint_id = $(this).val();
							updateJiraIssues();
						});
					});
				});
			});
			
			function updateOptionBoard() {
				$.ajax({
					type: 'POST',
					url: '/module/admin/version/xhr/option_board.php',
					dataType: 'json',
					success: function(data) {
						$.each(data, function(key, val) {
							$('#board_id').append('<option value="' + val.id + '">' + val.name + '</option>');
						})
						$('#board_id').removeAttr("disabled");
					}
				});
			}
			
			function updateOptionSprint() {
				$('#accordion div').remove();
				$('#sprint_id option[value!=""]').remove();
				$('#sprint_id').prop("disabled", true);
				
				if (board_id != "") {
					$.ajax({
						type: 'POST',
						url: '/module/admin/version/xhr/option_sprint.php',
						data: 'board_id=' + board_id,
						dataType: 'json',
						success: function(data) {
							$.each(data, function(key, val) {
								$('#sprint_id').append('<option value="' + val.id + '">' + val.name + ' (' + val.state + ')</option>');
							})
							$('#sprint_id').removeAttr("disabled");
						}
					});
				}
			}
			
			function updateJiraIssues() {
				$('#accordion div').remove();
				
				if ((board_id != "") && (sprint_id != "")) {
					var issue = '';
					
					$.ajax({
						type: 'POST',
						url: '/module/admin/version/xhr/collapse_issue.php',
						data: 'board_id=' + board_id + '&sprint_id=' + sprint_id,
						dataType: 'json',
						success: function(data) {
							$.each(data, function(key, val) {
								issue += '<div class="panel panel-default">' +
								         '	<div class="panel-heading">' +
								         '		<h4 class="panel-title">' +
								         '			<a data-toggle="collapse" data-parent="#accordion" href="#collapse'+val.id+'" class="collapsed" aria-expanded="false">'+val.key+' - '+val.summary+'</a>' +
								         '			<button type="button" class="btn btn-outline btn-warning btn-xs" onclick="addIssue(&apos;'+val.id+'&apos;,this);">Adicionar</button>' +
								         '		</h4>' +
								         '	</div>' +
								         '	<div id="collapse'+val.id+'" class="panel-collapse collapse" aria-expanded="false" style="height: 0px;">' +
								         '		<div class="panel-body">' +
								         '			'+val.description +
								         '		</div>' +
								         '	</div>' +
								         '</div>';
							})
							$('#accordion').html(issue);
						}
					});
				}
			}
			
			function addIssue(issue_id, button) {
				$(button).addClass('disabled');
				$(button).prop("onclick", null);
				$(button).html('Adicionando...');
				$(button).removeClass('btn-outline');
				$(button).toggleClass('btn-warning btn-default');
				
				$.ajax({
					type: 'POST',
					url: '/module/admin/version/xhr/add_issue.php',
					data: 'version_id=' + version_id + '&issue_id=' + issue_id,
					dataType: "json"
				})
				.done(function(data) {
					if (data.success == "true") {
						$(button).html('Adicionado');
						$(button).toggleClass('btn-default btn-success');
						
						datatable.ajax.reload();
					}
					else {
						$(button).html('Erro');
						$(button).toggleClass('btn-default btn-danger');
					}
				});
			}
			
			function removeIssue(id) {
				if (confirm("Deseja realmente remover essa Issue?")) {
					$.ajax({
						type: 'POST',
						url: '/module/admin/version/xhr/remove_issue.php',
						data: 'id=' + id,
						dataType: "json"
					})
					.done(function(data) {
						if (data.success == "true") {
							datatable.ajax.reload();
							$('#modal').modal('hide');
						}
						else {
							alert(data.message);
						}
					});
				}
			}
			
			function save() {
				$.ajax({
					type: "POST",
					url: "/module/admin/version/xhr/save_issue.php",
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
						<h1 class="page-header">Versão {$this->version_tag} - Changelog</h1>
					</div>
				</div>
				
				<table id="datatable" class="table table-striped table-condensed" cellspacing="0" width="100%">
					<thead>
						<tr>
							<th>ID</th>
							<th style="width: 80px;"><i class="fa fa-external-link"></i> Issue</th>
							<th style="width: 150px;"><i class="fa fa-compress"></i> Sumário</th>
							<th><i class="fa fa-expand"></i> Descrição</th>
							<th style="width: 40px;">&nbsp;</th>
						</tr>
					</thead>
				</table>
				
				<button type="button" class="btn btn-outline btn-primary" id="add-issue">Adicionar</button>
				
				<!-- BEGIN MODAL -->
				<div id="modal" class="modal fade">
					<!-- BEGIN MODAL-DIALOG -->
					<div class="modal-dialog modal-lg">
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
		$this->title = "Changelog";
	}
	
	private function init() {
		$this->version_id = $_POST["version_id"];
		$this->version_tag = Version::get_tag($this->version_id);
	}
}

?>