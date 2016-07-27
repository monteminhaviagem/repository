<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Security.inc");
require_once($path_module_admin_access."/dm/PageType.inc");
require_once($path_module_admin_access."/dm/UserType.inc");
require_once($path_module_admin_access."/dm/Profile.inc");
require_once($path_module_admin_access."/dm/Page.inc");

use module\common\Security;
use module\admin\access\dm\Page;
use module\admin\access\dm\PageType;
use module\admin\access\dm\UserType;
use module\admin\access\dm\Profile;

$args = array();
$data = array();

$args["user_type"] = array();
$data["user_type"] = array();

$args["profile"] = array();
$data["profile"] = array();

$args["page"] = array();
$data["page"] = array();

$dm = new UserType();
$dm->get_user_type(
	$args["user_type"],
	$data["user_type"]
);

$title = "INCLUSÃO";
$profile_id = "";
$profile_name = "";
$user_type_id = "";
$description = "";

if (isset($_GET["profile_id"]) && $_GET["profile_id"] != "") {
	$profile_id = $_GET["profile_id"];
	
	$args["profile"]["id"] = $profile_id;
	
	$dm = new Profile();
	$dm->get_profile_id(
		$args["profile"],
		$data["profile"]
	);
	
	$title = "ALTERAÇÃO";
	$profile_name = $data["profile"]["name"];
	$user_type_id = $data["profile"]["user_type_id"];
	$description = $data["profile"]["description"];
	$created = date("d/m/Y - H:i:s",$data["profile"]["created"]);
	$modified = date("d/m/Y - H:i:s",$data["profile"]["modified"]);
	$last_updated_name = $data["profile"]["last_updated_name"];
	$ip = $data["profile"]["ip"];
}

$dm = new Page();
$dm->get_page(
	$args["page"],
	$data["page"]
);

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
		<input type="hidden" name="id" value="{$profile_id}">
		
		<!-- BEGIN TAB -->
		<div class="panel-body">
			<ul class="nav nav-tabs">
				<li class="active"><a href="#perfil" data-toggle="tab"><i class="fa fa-users"></i> Perfil</a></li>
EOD;

if ($profile_id != "") {
	$return .= <<<EOD
				<li><a href="#pagina" data-toggle="tab"><i class="fa fa-laptop"></i> Página</a></li>
				<li><a href="#auditoria" data-toggle="tab"><i class="fa fa-database"></i> Auditoria</a></li>
EOD;
}

$return .= <<<EOD
			</ul>
			
			<div class="tab-content" style="padding-top: 20px;">
				<div class="tab-pane fade in active" id="perfil">
					<div class="form-group">
						<label class="col-sm-2 control-label">Nome:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" name="name" value="{$profile_name}" style="width: 300px;">
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Tipo:</label>
						<div class="col-sm-10">
							<select class="form-control" name="user_type_id" style="width: 150px;">
EOD;
	
	for ($i = 0; $i<count($data["user_type"]); $i++) {
		$selected = (($user_type_id != "") && ($user_type_id == $data["user_type"][$i]["id"])) ? 'selected="selected"' : '';
		
		$return .= "<option value=\"{$data["user_type"][$i]["id"]}\" {$selected}>{$data["user_type"][$i]["name"]}</option>";
	}
	
$return .= <<<EOD
							</select>
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Descrição:</label>
						<div class="col-sm-10">
							<textarea class="form-control" name="description" rows="4">{$description}</textarea>
						</div>
					</div>
EOD;

if (($profile_id != "") && ($profile_id > 6)) {
	$return .= <<<EOD
					<button type="button" class="btn btn-outline btn-danger btn-lg btn-block" id="excluir" profile="{$profile_id}">Excluir</button>
EOD;
}

$return .= <<<EOD
				</div>
EOD;

if ($profile_id != "") {
	$return .= <<<EOD
				<div class="tab-pane fade" id="pagina">
					<select id="page" name="page[]" multiple="multiple">
EOD;
	
	for ($i = 0; $i<count($data["page"]); $i++) {
		$display = false;
		
		if (($data["page"][$i]["page_type_id"] == PageType::OPERACIONAL) &&
			($user_type_id == UserType::PADRAO ||
			 $user_type_id == UserType::AGENCIA ||
			 $user_type_id == UserType::VENDEDOR))
			$display = true;
		
		else if (($data["page"][$i]["page_type_id"] == PageType::ADMINISTRATIVA) &&
				 ($user_type_id == UserType::ADMIN))
			$display = true;
		
		if ($display) {
			$selected = Security::get_authorization($data["page"][$i]["id"],$profile_id) ? "selected=\"selected\"" : "";
			
			$return .= "<option value=\"{$data["page"][$i]["id"]}\" {$selected}>{$data["page"][$i]["name"]}</option>";
		}
	}
	
	$return .= <<<EOD
					</select>
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