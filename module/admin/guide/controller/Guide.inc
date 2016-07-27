<?php
namespace module\admin\guide\controller;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");

class Guide {
	
	public function __construct() {}
	
	public function get_content($file_name) {
		global $path_module_admin_guide;
		
		if ($file_name != "") {
			if (file_exists($path_module_admin_guide . "/download/" . $file_name)) {
				$file = fopen($path_module_admin_guide . "/download/" . $file_name, "r");
				
				$content = fgets($file);
				
				while(!feof($file)) {
					$content .= fgets($file);
				}
				
				fclose($file);
				
				return htmlentities($content);
			}
		}
	}
}

?>