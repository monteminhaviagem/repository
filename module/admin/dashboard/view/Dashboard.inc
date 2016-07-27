<?php
namespace module\admin\dashboard\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Security.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_dashboard."/controller/Dashboard.inc");

use module\admin\Admin;
use module\admin\dashboard\controller\Dashboard;
use module\common\Security;

class Dashboard extends Admin {
	
	const ID = 'f98f998f73bd563a6e75f9e3ba2b9a66';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {}
	
	public function get_js_page() {}
	
	public function get_js() {
		return <<<EOD
			
EOD;
	}
	
	public function get_content() {
		$controller = new Dashboard();
		$data = $controller->get_info();
		
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="container-fluid">
					<div class="row">
						<div class="col-lg-12">
							<h1 class="page-header">Dashboard</h1>
						</div>
					</div>
					
					<div class="row">
						<div class="col-lg-3 col-md-6">
							<div class="panel panel-primary">
								<div class="panel-heading">
									<div class="row">
										<div class="col-xs-3">
											<i class="fa fa-users fa-4x"></i>
										</div>
										<div class="col-xs-9 text-right">
											<div class="huge">{$data["count_user"]}</div>
											<div>Usuários</div>
										</div>
									</div>
								</div>
								<a href="{$data["url_user"]}">
									<div class="panel-footer">
										<span class="pull-left">View Details</span>
										<span class="pull-right"><i class="fa fa-arrow-circle-right"></i></span>
										<div class="clearfix"></div>
									</div>
								</a>
							</div>
						</div>
						
						<div class="col-lg-3 col-md-6">
							<div class="panel panel-green">
								<div class="panel-heading">
									<div class="row">
										<div class="col-xs-3">
											<i class="fa fa-building-o fa-4x"></i>
										</div>
										<div class="col-xs-9 text-right">
											<div class="huge">{$data["count_agency"]}</div>
											<div>Agências</div>
										</div>
									</div>
								</div>
								<a href="#">
									<div class="panel-footer">
										<span class="pull-left">View Details</span>
										<span class="pull-right"><i class="fa fa-arrow-circle-right"></i></span>
										<div class="clearfix"></div>
									</div>
								</a>
							</div>
						</div>
						
						<div class="col-lg-3 col-md-6">
							<div class="panel panel-red">
								<div class="panel-heading">
									<div class="row">
										<div class="col-xs-3">
											<i class="fa fa-cogs fa-4x"></i>
										</div>
										<div class="col-xs-9 text-right">
											<div class="huge">{$data["count_session"]}</div>
											<div>Sessões Ativas</div>
										</div>
									</div>
								</div>
								<a href="{$data["url_session"]}">
									<div class="panel-footer">
										<span class="pull-left">View Details</span>
										<span class="pull-right"><i class="fa fa-arrow-circle-right"></i></span>
										<div class="clearfix"></div>
									</div>
								</a>
							</div>
						</div>
					</div>
				</div>
			</div>
			<!-- PAGE CONTENT - END -->
EOD;
	}
	
	public function set_title() {
		$this->title = "Dashboard";
	}
}

?>