<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_version."/dm/Changelog.inc");

use module\admin\version\dm\Changelog;

$id = $_GET["id"];

$load_args = array();
$load_data = array();

$load_args["id"] = $id;

$dm = new Changelog();
$dm->get_changelog_id(
	$load_args,
	$load_data
);

$title = $load_data["issue_key"];
$issue_summary = $load_data["issue_summary"];
$issue_description = $load_data["issue_description"];
$created = date("d/m/Y - H:i:s",$load_data["created"]);
$modified = date("d/m/Y - H:i:s",$load_data["modified"]);
$last_updated_name = $load_data["last_updated_name"];
$ip = $load_data["ip"];

$return = <<<EOD
<!-- BEGIN MODAL-HEADER -->
<div class="modal-header">
	<button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
	<h4 class="modal-title">{$title}</h4>
</div>
<!-- END MODAL-HEADER -->

<!-- BEGIN MODAL-BODY -->
<div class="modal-body">
	<form class="form-horizontal">
		<input type="hidden" name="id" value="{$id}">
		
		<!-- BEGIN TAB -->
		<div class="panel-body">
			<ul class="nav nav-tabs">
				<li class="active"><a href="#perfil" data-toggle="tab"><i class="fa fa-external-link"></i> Issue</a></li>
				<li><a href="#auditoria" data-toggle="tab"><i class="fa fa-database"></i> Auditoria</a></li>
			</ul>
			
			<div class="tab-content" style="padding-top: 20px;">
				<div class="tab-pane fade in active" id="perfil">
					<div class="form-group">
						<label class="col-sm-2 control-label">Sumário:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" name="issue_summary" value="{$issue_summary}">
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Descrição:</label>
						<div class="col-sm-10">
							<textarea class="form-control" rows="6" name="issue_description">{$issue_description}</textarea>
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label"></label>
						<div class="col-sm-10">
							<button type="button" class="btn btn-outline btn-danger btn-lg btn-block" onclick="removeIssue('{$id}');">Remover Issue</button>
						</div>
					</div>
				</div>
				
				<div class="tab-pane fade" id="auditoria">
					<table class="table table-condensed">
						<tbody>
							<tr>
								<td style="border-top: none; width: 150px;"><strong>Criado em:</strong></td>
								<td style="border-top: none;"><span class="text-highlight-green">{$created}</span></td>
							</tr>
							<tr>
								<td><strong>Alterado em:</strong></td>
								<td><span class="text-highlight-red">{$modified}</span></td>
							</tr>
							<tr>
								<td><strong>Usuário:</strong></td>
								<td><span class="text-highlight-dark">{$last_updated_name}</span></td>
							</tr>
							<tr>
								<td><strong>IP:</strong></td>
								<td><span class="text-highlight-blue">{$ip}</span></td>
							</tr>
						</tbody>
					</table>
				</div>
			</div>
		</div>
		<!-- END TAB -->
	</form>
</div>
<!-- END MODAL-BODY -->

<!-- BEGIN MODAL-FOOTER -->
<div class="modal-footer">
	<button type="button" class="btn btn-default" data-dismiss="modal">Fechar</button>
	<button type="button" class="btn btn-primary" onclick="save();">Salvar</button>
</div>
<!-- END MODAL-FOOTER -->
EOD;

echo $return;

?>