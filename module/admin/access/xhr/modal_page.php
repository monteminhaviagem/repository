<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Security.inc");
require_once($path_module_admin_access."/dm/UserType.inc");
require_once($path_module_admin_access."/dm/Page.inc");
require_once($path_module_admin_access."/dm/PageType.inc");
require_once($path_module_admin_access."/dm/Profile.inc");

use module\common\Security;
use module\admin\access\dm\Page;
use module\admin\access\dm\Profile;
use module\admin\access\dm\PageType;
use module\admin\access\dm\UserType;

$args = array();
$data = array();

$args["page"] = array();
$data["page"] = array();

$args["profile"] = array();
$data["profile"] = array();

if (isset($_GET["page_id"]) && $_GET["page_id"] != "") {
	$page_id = $_GET["page_id"];
	
	$args["page"]["id"] = $page_id;
	
	$dm = new Page();
	$dm->get_page_id(
		$args["page"],
		$data["page"]
	);
	
	$page_id = $data["page"]["id"];
	$page_name = $data["page"]["name"];
	$page_url = $data["page"]["url"];
	$page_file = $data["page"]["file"];
	$page_class = $data["page"]["class"];
	$page_namespace = $data["page"]["namespace"];
	$page_type_id = $data["page"]["page_type_id"];
	$page_type_name = $data["page"]["page_type_name"];
	$created = date("d/m/Y - H:i:s",$data["page"]["created"]);
	$modified = date("d/m/Y - H:i:s",$data["page"]["modified"]);
	$last_updated_name = $data["page"]["last_updated_name"];
	$ip = $data["page"]["ip"];
}
else
	return;

$dm = new Profile();
$dm->get_profile(
	$args["profile"],
	$data["profile"]
);

$return = <<<EOD
<!-- BEGIN MODAL-HEADER -->
<div class="modal-header">
	<button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
	<h4 class="modal-title">ALTERAÇÃO</h4>
</div>
<!-- END MODAL-HEADER -->

<!-- BEGIN MODAL-BODY -->
<div class="modal-body">
	<form class="form-horizontal">
		<input type="hidden" name="id" value="{$page_id}">
		
		<!-- BEGIN TAB -->
		<div class="panel-body">
			<ul class="nav nav-tabs">
				<li class="active"><a href="#pagina" data-toggle="tab"><i class="fa fa-laptop"></i> Pagina</a></li>
EOD;

if ($page_type_id != PageType::INFORMATIVA) {
	$return .= <<<EOD
				<li><a href="#perfil" data-toggle="tab"><i class="fa fa-user"></i> Perfil</a></li>
EOD;
}

$return .= <<<EOD
				<li><a href="#auditoria" data-toggle="tab"><i class="fa fa-database"></i> Auditoria</a></li>
			</ul>
			
			<div class="tab-content" style="padding-top: 20px;">
				<div class="tab-pane fade in active" id="pagina">
					<div class="form-group">
						<label class="col-sm-2 control-label">ID:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" value="{$page_id}" style="width: 300px;" disabled>
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Nome:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" value="{$page_name}" style="width: 300px;" disabled>
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">URL:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" name="url" value="{$page_url}" style="width: 300px;">
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Arquivo:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" value="{$page_file}:{$page_class}" disabled>
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Tipo:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" value="{$page_type_name}" style="width: 200px;" disabled>
						</div>
					</div>
				</div>
EOD;

if ($page_type_id != PageType::INFORMATIVA) {
	$return .= <<<EOD
				<div class="tab-pane fade" id="perfil">
					<select id="profile" name="profile[]" multiple="multiple">
EOD;
	
	for ($i = 0; $i<count($data["profile"]); $i++) {
		$display = false;
		
		if (($page_type_id == PageType::OPERACIONAL) &&
			($data["profile"][$i]["user_type_id"] == UserType::PADRAO ||
			 $data["profile"][$i]["user_type_id"] == UserType::AGENCIA ||
			 $data["profile"][$i]["user_type_id"] == UserType::VENDEDOR))
			$display = true;
		
		else if (($page_type_id == PageType::ADMINISTRATIVA) &&
				 ($data["profile"][$i]["user_type_id"] == UserType::ADMIN))
			$display = true;
		
		if ($display) {
			$selected = Security::get_authorization($page_id,$data["profile"][$i]["id"]) ? "selected=\"selected\"" : "";
			
			$return .= "<option value=\"{$data["profile"][$i]["id"]}\" {$selected}>{$data["profile"][$i]["name"]}</option>";
		}
	}
	
	$return .= <<<EOD
					</select>
				</div>
EOD;
}

$return .= <<<EOD
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