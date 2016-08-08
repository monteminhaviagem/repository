<?php

error_reporting(0);

date_default_timezone_set('America/Sao_Paulo');

$path = $_SERVER["DOCUMENT_ROOT"];
$path_log = $path."/repository/log";
$path_module = $path."/module";

$path_module_admin = $path_module."/admin";
$path_module_admin_access = $path_module_admin."/access";
$path_module_admin_dashboard = $path_module_admin."/dashboard";
$path_module_admin_log = $path_module_admin."/log";
$path_module_admin_menu = $path_module_admin."/menu";
$path_module_admin_guide = $path_module_admin."/guide";
$path_module_admin_version = $path_module_admin."/version";
$path_module_admin_jira = $path_module_admin."/jira";

$path_module_common = $path_module."/common";
$path_module_common_google = $path_module_common."/google";
$path_module_common_system = $path_module_common."/system";

$path_module_info = $path_module."/info";
$path_module_operation = $path_module."/operation";
$path_module_operation_itinerary = $path_module_operation."/itinerary";

$path_url_assets = "/assets";
$path_url_css = "/css";
$path_url_js = "/js";

$path_url_img_itinerary = "/module/operation/itinerary/img";
$path_url_img_guide = "/module/admin/guide/img";

?>