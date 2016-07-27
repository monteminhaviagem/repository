<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin_menu."/dm/Menu.inc");
require_once($path_module_admin_menu."/controller/Category.inc");
require_once($path_module_admin_access."/dm/Page.inc");

use module\admin\menu\dm\Menu;
use module\admin\access\dm\Page;
use module\admin\menu\controller\Category;

$args = array();
$data = array();

$args["link"] = array();
$data["link"] = array();

$args["page"] = array();
$data["page"] = array();

$title = "INCLUSÃO";
$link_id = "";
$link_name = "";
$parent_id = 2;
$page_id = "";
$page_name = "";
$icon = "";
$target = "";
$target_self = "";
$target_blank = "";

if (isset($_GET["link_id"]) && $_GET["link_id"] != "") {
	$link_id = $_GET["link_id"];
	
	$args["link"]["id"] = $link_id;
	$args["link"]["include_page"] = "true";
	
	$dm = new Menu();
	$dm->get_link_id(
		$args["link"],
		$data["link"]
	);
	
	$title = "ALTERAÇÃO";
	$link_name = $data["link"]["name"];
	$parent_id = $data["link"]["parent_id"];
	$page_id = $data["link"]["page_id"];
	$page_name = $data["link"]["page"]["name"];
	$icon = $data["link"]["icon"];
	$target = $data["link"]["target"];
	$target_self = ($target == "_self") ? "selected" : "";
	$target_blank = ($target == "_blank") ? "selected" : "";
	$created = date("d/m/Y - H:i:s",$data["link"]["created"]);
	$modified = date("d/m/Y - H:i:s",$data["link"]["modified"]);
	$last_updated_name = $data["link"]["last_updated_name"];
	$ip = $data["link"]["ip"];
}

$dm = new Page();
$dm->get_page_available(
	$args["page"],
	$data["page"]
);

$controller = new Category();
$category_option = $controller->get_category_option($parent_id);

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
		<input type="hidden" name="id" value="{$link_id}">
		
		<!-- BEGIN TAB -->
		<div class="panel-body">
			<ul class="nav nav-tabs">
				<li class="active"><a href="#link" data-toggle="tab"><i class="fa fa-link"></i> Link</a></li>
EOD;

if ($link_id != "") {
	$return .= <<<EOD
				<li><a href="#auditoria" data-toggle="tab"><i class="fa fa-database"></i> Auditoria</a></li>
EOD;
}

$return .= <<<EOD
			</ul>
			
			<div class="tab-content" style="padding-top: 20px;">
				<div class="tab-pane fade in active" id="link">
					<div class="form-group">
						<label class="col-sm-2 control-label">Nome:</label>
						<div class="col-sm-10">
							<input type="text" class="form-control" name="name" value="{$link_name}">
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Categoria:</label>
						<div class="col-sm-10">
							<select class="form-control" name="parent_id">
{$category_option}
							</select>
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Página:</label>
						<div class="col-sm-10">
							<select class="form-control" name="page_id">
								<option value="{$page_id}" selected>{$page_name}</option>
EOD;

for ($i=0; $i<count($data["page"]); $i++) {
	$selected = (($page_id != "") && ($page_id == $data["page"][$i]["id"])) ? 'selected="selected"' : '';
	
	$return .= "<option value=\"{$data["page"][$i]["id"]}\" {$selected}>{$data["page"][$i]["name"]}</option>";
}

$return .= <<<EOD
							</select>
						</div>
					</div>
					<div class="form-group">
						<label class="col-sm-2 control-label">Target:</label>
						<div class="col-sm-10">
							<select class="form-control" name="target" style="width: 100px;">
								<option value=""></option>
								<option value="_self" {$target_self}>_self</option>
								<option value="_blank" {$target_blank}>_blank</option>
							</select>
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

if ($link_id != "") {
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