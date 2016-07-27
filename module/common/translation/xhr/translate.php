<?php

header('Content-Type: application/json; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"]."/Path.inc");
require_once($path_root."/ErrorHandler.inc");
require_once($path_root_common."/Function.inc");
require_once($path_root_module_translate."/service/Translate.inc");

$source = "en";
$target = "pt";
$text = (isset($_POST["text"]) && $_POST["text"] != "") ? $_POST["text"] : null;

if (isset($text)) {
	$mod = new Translate();
	$data = $mod->get_translation($source, $target, $text);
	
	$return["success"] = "true";
	$return["message"] = "";
	$return["translated"] = $data["translated"];
	$return["cache"] = $data["cache"];
}
else {
	$return["success"] = "false";
	$return["message"] = "parameter not found";
}

echo my_json_encode($return);

?>