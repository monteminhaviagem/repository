<?php
namespace module\common;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");

class RepositoryJS {
	public function get_repository() {
		global $path_url_js;
		global $path_url_assets;
		
		$repository = array(
			"jquery.js" => array(
				"developer" => $path_url_assets."/jquery/jquery-2.2.0.js",
				"production" => $path_url_assets."/jquery/jquery-2.2.0.min.js"
			),
			"jquery-ui.js" => array(
				"developer" => $path_url_assets."/jquery-ui/js/jquery-ui-1.11.4.js",
				"production" => $path_url_assets."/jquery-ui/js/jquery-ui-1.11.4.min.js"
			),
			"bootstrap.js" => array(
				"developer" => $path_url_assets."/bootstrap/js/bootstrap-3.3.6.js",
				"production" => $path_url_assets."/bootstrap/js/bootstrap-3.3.6.min.js"
			),
			"metisMenu.js" => array(
				"developer" => $path_url_assets."/metisMenu/js/metisMenu-1.1.3.js",
				"production" => $path_url_assets."/metisMenu/js/metisMenu-1.1.3.min.js"
			),
			"admin-global.js" => array(
				"developer"  => $path_url_js."/admin-global-1.0.js",
				"production" => $path_url_js."/admin-global-1.0.js"
			),
			"jquery.dataTables.js" => array(
				"developer" => $path_url_assets."/datatable/js/jquery.dataTables-1.10.11.js",
				"production" => $path_url_assets."/datatable/js/jquery.dataTables-1.10.11.min.js"
			),
			"dataTables.bootstrap.js" => array(
				"developer" => $path_url_assets."/datatable/js/dataTables.bootstrap-1.10.11.js",
				"production" => $path_url_assets."/datatable/js/dataTables.bootstrap-1.10.11.min.js"
			),
			"dataTables.responsive.js" => array(
				"developer" => $path_url_assets."/datatable/js/dataTables.responsive-1.10.11.js",
				"production" => $path_url_assets."/datatable/js/dataTables.responsive-1.10.11.min.js"
			),
			"picklist.js" => array(
				"developer" => $path_url_assets."/picklist/js/picklist-0.11.0.js",
				"production" => $path_url_assets."/picklist/js/picklist-0.11.0.min.js"
			),
			"nestable.js" => array(
				"developer" => $path_url_assets."/nestable/js/nestable-1.0.js",
				"production" => $path_url_assets."/nestable/js/nestable-1.0.js"
			),
			"highlight-zenburn.js" => array(
				"developer" => $path_url_assets."/highlight/js/zenburn-1.0.js",
				"production" => $path_url_assets."/highlight/js/zenburn-1.0.js"
			),
			"functions.js" => array(
				"developer" => $path_url_js."/functions.js",
				"production" => $path_url_js."/functions.js"
			)
		);
		
		return $repository;
	}
}

?>