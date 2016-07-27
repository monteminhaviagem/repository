<?php
namespace module\common;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Log.inc");
require_once($path_module_info."/view/Error.inc");
require_once($path_module_admin_access."/dm/Page.inc");

use module\admin\access\dm\Page;
use module\info\view\Error;

function fatal_error_shutdown_handler() {
	$last_error = error_get_last();
	
	if ($last_error != null) {
		$log = new Log();
		$log->save(print_r($last_error,true), __FILE__, __METHOD__, __LINE__);
		
		header("Location: " . Page::get_url(Error::ID));
	}
}

register_shutdown_function('module\common\fatal_error_shutdown_handler');

?>