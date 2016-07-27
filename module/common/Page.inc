<?php
namespace module\common;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Config.inc");
require_once($path_module_common."/RepositoryCSS.inc");
require_once($path_module_common."/RepositoryJS.inc");
require_once($path_module_common."/Security.inc");
require_once($path_module_admin_access."/dm/Page.inc");

use module\admin\access\dm\Page;
use module\info\view\Error;

class Page {
	protected $css;
	protected $css_linked_info;
	protected $css_linked_used;
	protected $css_is_local;
	protected $css_common;
	protected $css_page;
	
	protected $js;
	protected $js_linked_info;
	protected $js_linked_used;
	protected $js_is_local;
	protected $js_common;
	protected $js_page;
	protected $js_is_top;
	
	protected $title;
	protected $body;
	protected $body_id;
	protected $container_id;
	
	public function __construct($screen_id = null) {
		if (!is_null($screen_id)) {
			$profile_id = $_SESSION['profile_id'] ?? null;
			
			if (is_null($profile_id) || !Security::get_authorization($screen_id, $profile_id)) {
				header("Location: " . Page::get_url(Error::ID));
				exit;
			}
		}
		
		$this->css = "";
		$this->css_linked_info = array();
		$this->css_linked_used = array();
		$this->css_common = "";
		$this->css_page = "";
		
		$this->js = "";
		$this->js_linked_info = array();
		$this->js_linked_used = array();
		$this->js_common = "";
		$this->js_page = "";
		$this->js_is_top = false;
		
		if (Config::get_environment() == Config::ENV_PRODUCTION) {
			$this->css_is_local = false;
			$this->js_is_local = false;
		}
		else {
			$this->css_is_local = true;
			$this->js_is_local = true;
		}
		
		$this->title = "";
		$this->body_id = "";
		$this->container_id = "";
	}
	
	public function get_page() {
		$this->register_links();
		
		$this->set_title();
		$this->set_body_id();
		$this->set_container_id();
		
		$this->set_js_common();
		$this->set_js_page();
		$this->set_css_common();
		$this->set_css_page();
		
		$doctype = $this->get_doctype();
		$meta = $this->get_meta();
		$title = $this->get_title();
		
		$header = $this->get_header();
		$content = $this->get_content();
		$footer = $this->get_footer();
		
		$this->body = <<<EOD
$header
$content
$footer
EOD;
		
		if ($this->body_id == "")
			$body_id = "";
		else
			$body_id = " id=\"".$this->body_id."\"";
		
		if ($this->container_id == "")
			$container_id = "";
		else
			$container_id = " id=\"".$this->container_id."\"";
		
		if ($this->js_is_top) {
			$js_top = $this->get_all_js();
			$js_btm = "";
		}
		else {
			$js_top = "";
			$js_btm = $this->get_all_js();
		}
		
		$css = $this->get_all_css();
		
		return <<<EOD
$doctype
	<head>
$meta
$title
$css
$js_top
	</head>
	<body{$body_id}>
		<div{$container_id}>
$this->body
$js_btm
		</div>
	</body>
</html>
EOD;
	}
	
	public function register_links() {
		$repositoryCSS = new RepositoryCSS();
		$repositoryJS = new RepositoryJS();
		
		$this->css_linked_info = $repositoryCSS->get_repository();
		$this->js_linked_info = $repositoryJS->get_repository();
	}
	
	public function get_doctype() {
		return <<<EOD
<!DOCTYPE html>
<html lang="pt-br">
EOD;
	}
	
	public function get_meta() {
		$meta = <<<EOD
			<meta charset="utf-8"/>
			<meta http-equiv="X-UA-Compatible" content="IE=edge">
			<meta name="viewport" content="width=device-width, initial-scale=1">
EOD;
		return $meta;
	}
	
	public function get_title() {
		return <<<EOD
			<title>{$this->title}</title>
EOD;
	}
	
	private function set_js_common() {
		$this->js_common = $this->manage_js_linked($this->get_js_common());
	}
	
	private function set_js_page() {
		$this->js_page = $this->manage_js_linked($this->get_js_page());
		$this->js_page .= $this->create_js($this->get_js());
	}
	
	private function manage_js_linked($keys) {
		$js = "";
		
		if (empty($keys))
			return "";
			
			if (!is_array($keys))
				$keys = array($keys);
					
				foreach ($keys as $k) {
					if (!array_key_exists($k, $this->js_linked_info)) {
						continue;
					}
						
					if (array_search($k, $this->js_linked_used) === false) {
						$this->js_linked_used[] = $k;
						$js .= $this->create_js_linked($k);
					}
				}
				
				return $js;
	}
	
	private function create_js_linked($k) {
		if ($this->js_is_local)
			$path = $this->js_linked_info[$k]["developer"];
			else
				$path = $this->js_linked_info[$k]["production"];
				
				return <<<EOD
			<script src="$path" type="text/javascript"></script>
EOD;
	}
	
	private function create_js($js) {
		if (!empty($js)) {
			return <<<EOD
				<script type="text/javascript">
$js
				</script>
EOD;
		}
		else {
			return "";
		}
	}
	
	public function get_all_js() {
		return <<<EOD
$this->js_common
$this->js_page
EOD;
	}
	
	public function set_js_top() {
		$this->js_is_top = true;
	}
	
	private function set_css_common() {
		$this->css_common = $this->manage_css_linked($this->get_css_common());
	}
	
	private function set_css_page() {
		$this->css_page = $this->manage_css_linked($this->get_css_page());
		$this->css_page .= $this->create_css($this->get_css());
	}
	
	private function manage_css_linked($keys) {
		$css = "";
		
		if (empty($keys))
			return "";
			
			if (!is_array($keys))
				$keys = array($keys);
				
				foreach ($keys as $k) {
					if (!array_key_exists($k, $this->css_linked_info)) {
						continue;
					}
					
					if (array_search($k, $this->css_linked_used) === false) {
						$this->css_linked_used[] = $k;
						$css .= $this->create_css_linked($k);
					}
				}
	
				return $css;
	}
	
	private function create_css_linked($k) {
		if ($this->css_is_local)
			$path = $this->css_linked_info[$k]["developer"];
			else
				$path = $this->css_linked_info[$k]["production"];
	
				return <<<EOD
			<link rel="stylesheet" type="text/css" href="$path">
EOD;
	}
	
	private function create_css($css) {
		if (!empty($css)) {
			return <<<EOD
				<style type="text/css">
$css
				</style>
EOD;
		}
		else {
			return "";
		}
	}
	
	public function get_all_css() {
		return <<<EOD
$this->css_common
$this->css_page
EOD;
	}
	
	public function get_header() {}
	
	public function get_content() {}
	
	public function get_footer() {}
	
	public function set_title() {}
	
	public function set_body_id() {}
	
	public function set_container_id() {}
	
	public function get_css_common() {}
	
	public function get_css_page() {}
	
	public function get_css() {}
	
	public function get_js_common() {}
	
	public function get_js_page() {}
	
	public function get_js() {}
}

?>