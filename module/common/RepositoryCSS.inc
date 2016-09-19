<?php
namespace module\common;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");

class RepositoryCSS {
	public function get_repository() {
		global $path_url_css;
		global $path_url_assets;
		
		$repository = array(
			"bootstrap.css" => array(
				"developer"  => $path_url_assets."/bootstrap/css/bootstrap-3.3.6.css",
				"production" => $path_url_assets."/bootstrap/css/bootstrap-3.3.6.min.css"
			),
			"jquery-ui.css" => array(
				"developer"  => $path_url_assets."/jquery-ui/css/jquery-ui-1.11.4.min.css",
				"production" => $path_url_assets."/jquery-ui/css/jquery-ui-1.11.4.min.css"
			),
			"metisMenu.css" => array(
				"developer"  => $path_url_assets."/metisMenu/css/metisMenu-1.1.3.css",
				"production" => $path_url_assets."/metisMenu/css/metisMenu-1.1.3.min.css"
			),
			"font-awesome.css" => array(
				"developer"  => $path_url_assets."/font-awesome/css/font-awesome-4.2.0.css",
				"production" => $path_url_assets."/font-awesome/css/font-awesome-4.2.0.min.css"
			),
			"admin-global.css" => array(
				"developer"  => $path_url_css."/admin-global-1.0.css",
				"production" => $path_url_css."/admin-global-1.0.css"
			),
			"info-global.css" => array(
				"developer"  => $path_url_css."/info-global-1.0.css",
				"production" => $path_url_css."/info-global-1.0.css"
			),
			"datepicker.css" => array(
				"developer"  => $path_url_assets."/jquery-ui/css/datepicker.css",
				"production" => $path_url_assets."/jquery-ui/css/datepicker.css"
			),
			"dataTables.bootstrap.css" => array(
				"developer" => $path_url_assets."/datatable/css/dataTables.bootstrap-1.10.11.min.css",
				"production" => $path_url_assets."/datatable/css/dataTables.bootstrap-1.10.11.min.css"
			),
			"responsive.bootstrap.css" => array(
				"developer" => $path_url_assets."/datatable/css/responsive.bootstrap-1.10.11.css",
				"production" => $path_url_assets."/datatable/css/responsive.bootstrap-1.10.11.min.css"
			),
			"picklist.css" => array(
				"developer" => $path_url_assets."/picklist/css/picklist-0.11.0-1.css",
				"production" => $path_url_assets."/picklist/css/picklist-0.11.0-1.css"
			),
			"nestable.css" => array(
				"developer" => $path_url_assets."/nestable/css/nestable-1.0.css",
				"production" => $path_url_assets."/nestable/css/nestable-1.0.css"
			),
			"highlight-zenburn.css" => array(
				"developer" => $path_url_assets."/highlight/css/zenburn-1.0.css",
				"production" => $path_url_assets."/highlight/css/zenburn-1.0.css"
			),
			"roteiro.css" => array(
				"developer" => $path_url_css."/roteiro-1.0.css",
				"production" => $path_url_css."/roteiro-1.0.css"
			),
			"porto-custom.css" => array(
					"developer" => $path_url_css."/porto-custom-1.0.css",
					"production" => $path_url_css."/porto-custom-1.0.css"
			),
			"porto-skin-default.css" => array(
					"developer" => $path_url_css."/porto-skin-default-1.0.css",
					"production" => $path_url_css."/porto-skin-default-1.0.css"
			),
			"porto-theme.css" => array(
					"developer" => $path_url_css."/porto-theme-1.0.css",
					"production" => $path_url_css."/porto-theme-1.0.css"
			),
			"porto-theme-animate.css" => array(
					"developer" => $path_url_css."/porto-theme-animate-1.0.css",
					"production" => $path_url_css."/porto-theme-animate-1.0.css"
			),
			"porto-theme-blog.css" => array(
					"developer" => $path_url_css."/porto-theme-blog-1.0.css",
					"production" => $path_url_css."/porto-theme-blog-1.0.css"
			),
			"porto-theme-elements.css" => array(
					"developer" => $path_url_css."/porto-theme-elements-1.0.css",
					"production" => $path_url_css."/porto-theme-elements-1.0.css"
			),
			"porto-theme-shop.css" => array(
					"developer" => $path_url_css."/porto-theme-shop-1.0.css",
					"production" => $path_url_css."/porto-theme-shop-1.0.css"
			)
		);
		
		return $repository;
	}
}

?>