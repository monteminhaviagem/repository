<?php
namespace module\operation;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Page.inc");

use module\common\Page;

class Operation extends Page {
	protected $page_id;
	
	public function __construct($page_id) {
		parent::__construct();
		
		$this->page_id = $page_id;
	}
	
	public function get_js_common() {
		return array();
	}
	
	public function get_css_common() {
		return array(
			"roteiro.css"
		);
	}
	
	public function get_header() {
		return <<<EOD
			<div id="header">hh</div>
EOD;
	}
	
	public function get_footer() {}
}

?>