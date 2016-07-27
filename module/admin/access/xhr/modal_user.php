<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Security.inc");
require_once($path_module_admin_access."/dm/User.inc");
require_once($path_module_admin_access."/dm/Profile.inc");

use module\common\Security;
use module\admin\access\dm\User;
use module\admin\access\dm\Profile;

$load_args = array();
$load_data = array();

$load_args["user"] = array();
$load_data["user"] = array();

$load_args["profile"] = array();
$load_data["profile"] = array();

$dm = new Profile();
$dm->get_profile(
	$load_args["profile"],
	$load_data["profile"]
);

$title = "INCLUSÃO";
$user_id = "";
$user_name = "";
$user_email = "";
$user_status_id = "";
$user_status_name = "";
$user_type_id = "";
$user_type_name = "";
$profile_id = "";
$profile_name = "";

if (isset($_GET["user_id"]) && $_GET["user_id"] != "") {
	$user_id = $_GET["user_id"];
	
	$load_args["user"]["id"] = $user_id;
	
	$dm = new User();
	$dm->get_user_id(
		$load_args["user"],
		$load_data["user"]
	);
	
	$title = "ALTERAÇÃO";
	$user_name = $load_data["user"]["name"];
	$user_email = $load_data["user"]["email"];
	$user_status_id = $load_data["user"]["user_status_id"];
	$user_status_name = $load_data["user"]["user_status_name"];
	$user_type_id = $load_data["user"]["user_type_id"];
	$user_type_name = $load_data["user"]["user_type_name"];
	$profile_id = $load_data["user"]["profile_id"];
	$profile_name = $load_data["user"]["profile_name"];
	$created = date("d/m/Y - H:i:s",$load_data["user"]["created"]);
	$modified = date("d/m/Y - H:i:s",$load_data["user"]["modified"]);
	$last_updated_name = $load_data["user"]["last_updated_name"];
	$ip = $load_data["user"]["ip"];
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
		<input type="hidden" name="id" value="{$user_id}">
		
		<!-- BEGIN TAB -->
		<div class="panel-body">
			<ul class="nav nav-tabs">
				<li class="active"><a href="#perfil" data-toggle="tab"><i class="fa fa-user"></i> Usuário</a></li>
EOD;

if ($user_id != "") {
	$return .= <<<EOD
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
							<input type="text" class="form-control" name="name" value="{$user_name}">
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Email:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" name="email" value="{$user_email}">
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Perfil:</label>
						<div class="col-sm-10">
							<select class="form-control" name="profile_id" style="width: 200px;">
EOD;
	
	for ($i = 0; $i<count($load_data["profile"]); $i++) {
		$selected = (($profile_id != "") && ($profile_id == $load_data["profile"][$i]["id"])) ? 'selected="selected"' : '';
		
		$return .= "<option value=\"{$load_data["profile"][$i]["id"]}\" {$selected}>{$load_data["profile"][$i]["name"]}</option>";
	}
	
$return .= <<<EOD
							</select>
						</div>
					</div>
				</div>
EOD;

if ($user_id != "") {
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