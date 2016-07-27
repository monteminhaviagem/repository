<?php
namespace module\info\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_info."/Info.inc");

use module\info\Info;

class Home extends Info {
	
	const ID = '076455825bc60d16762bf604b02fa7bc';
	
	public function __construct() {
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {}
	
	public function get_js_page() {}
	
	public function get_css() {}
	
	public function get_js() {}
	
	public function get_header() {}
	
	public function get_content() {
		return <<<EOD
EOD;
	}
	
	public function get_footer() {}
	
	public function set_title() {
		$this->title = "Monte Minha Viagem";
	}
}

?>