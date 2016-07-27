<?php
namespace module\info;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Page.inc");

use module\common\Page;

class Info extends Page {
	protected $page_id;
	
	public function __construct($page_id) {
		parent::__construct();
		
		$this->page_id = $page_id;
	}
	
	public function get_js_common() {
		return array();
	}
	
	public function get_css_common() {
		return array();
	}
	
	public function get_header() {}
	
	public function get_footer() {}
}

?>