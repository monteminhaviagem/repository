<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_menu."/dm/Menu.inc");

use module\admin\menu\dm\Menu;

$args = array();
$data = array();

$args["category"] = array();
$data["category"] = array();

$title = "INCLUSÃO";
$id = "";
$name = "";
$icon = "";

if (isset($_GET["id"]) && $_GET["id"] != "") {
	$id = $_GET["id"];
	
	$args["category"]["id"] = $id;
	
	$dm = new Menu();
	$dm->get_category_id(
		$args["category"],
		$data["category"]
	);
	
	$title = "ALTERAÇÃO";
	$name = $data["category"]["name"];
	$icon = $data["category"]["icon"];
	$created = date("d/m/Y - H:i:s",$data["category"]["created"]);
	$modified = date("d/m/Y - H:i:s",$data["category"]["modified"]);
	$last_updated_name = $data["category"]["last_updated_name"];
	$ip = $data["category"]["ip"];
}

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
				<li class="active"><a href="#tab-category" data-toggle="tab"><i class="fa fa-folder"></i> Categoria</a></li>
EOD;

if ($id != "") {
	$return .= <<<EOD
				<li><a href="#tab-audit" data-toggle="tab"><i class="fa fa-database"></i> Auditoria</a></li>
EOD;
}

$return .= <<<EOD
			</ul>
			
			<div class="tab-content" style="padding-top: 20px;">
				<div class="tab-pane fade in active" id="tab-category">
					<div class="form-group">
						<label class="col-sm-2 control-label">Nome:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" name="name" value="{$name}">
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Icon:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" name="icon" value="{$icon}" style="width: 200px;">
						</div>
					</div>
				</div>
EOD;

if ($id != "") {
	$return .= <<<EOD
				<div class="tab-pane fade" id="tab-audit">
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
EOD;
}

$return .= <<<EOD
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