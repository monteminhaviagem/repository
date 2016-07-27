<?php
namespace module\admin\dashboard\controller;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_admin_access."/dm/User.inc");
require_once($path_module_admin_access."/dm/Session.inc");
require_once($path_module_admin_access."/dm/Page.inc");
require_once($path_module_admin_access."/view/User.inc");
require_once($path_module_admin_access."/view/Session.inc");

use module\admin\access\dm\Page;
use module\admin\access\dm\User as dm_User;
use module\admin\access\view\User as view_User;
use module\admin\access\view\Session as view_Session;
use module\admin\access\dm\Session as dm_Session;

class Dashboard {
	
	public function __construct() {}
	
	public function get_info() {
		$data = array();
		
		// COUNT
		$count_user = dm_User::get_count();
		$data["count_user"] = $count_user;
		
		$count_agency = 0;
		$data["count_agency"] = $count_agency;
		
		$count_session = dm_Session::get_count();
		$data["count_session"] = $count_session;
		
		// LINKS
		$url_user = Page::get_url(view_User::ID);
		$data["url_user"] = $url_user;
		
		$url_session = Page::get_url(view_Session::ID);
		$data["url_session"] = $url_session;
		
		return $data;
	}
}

?>