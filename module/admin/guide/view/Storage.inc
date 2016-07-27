<?php
namespace module\admin\guide\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_guide."/controller/Guide.inc");

use module\admin\Admin;
use module\admin\guide\controller\Guide;

class Storage extends Admin {
	
	const ID = '3ae3ba10b087474c1c384e4ad83f1b64';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_content() {
		$controller = new Guide();
		$file_info = $controller->get_content("info_storage.txt");
		$file_config = $controller->get_content("config_storage.txt");
		$file_ftp = $controller->get_content("ftp_storage.txt");
		$file_apache = $controller->get_content("apache_storage.txt");
		
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="container-fluid">
					<div class="row">
						<div class="col-lg-12">
							<h1 class="page-header">Armazenamento</h1>
						</div>
					</div>
					
					<!-- BEGIN TAB -->
					<div class="panel-body">
						<ul class="nav nav-tabs">
							<li class="active"><a href="#info" data-toggle="tab"><i class="fa fa-info"></i> Info</a></li>
							<li><a href="#config" data-toggle="tab"><i class="fa fa-cog"></i> Configuração</a></li>
							<li><a href="#ftp" data-toggle="tab"><i class="fa fa-upload"></i> FTP</a></li>
							<li><a href="#apache" data-toggle="tab"><i class="fa fa-cogs"></i> Apache</a></li>
						</ul>
						
						<div class="tab-content" style="padding-top: 20px;">
							<div class="tab-pane fade in active" id="info">
								<pre>{$file_info}</pre>
							</div>
							
							<div class="tab-pane fade" id="config">
								<div class="header">
									<a href="/module/admin/guide/download/config_prod.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<br>
								<pre>{$file_config}</pre>
							</div>
							
							<div class="tab-pane fade" id="ftp">
								<div class="header">
									<a href="/module/admin/guide/download/ftp.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<br>
								<pre>{$file_ftp}</pre>
							</div>
							
							<div class="tab-pane fade" id="apache">
								<div class="header">
									<a href="/module/admin/guide/download/apache.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<br>
								<pre>{$file_apache}</pre>
							</div>
						</div>
					</div>
					<!-- END TAB -->
				
					
				<div class="row">
						<div class="col-lg-12">
							
						</div>
					</div>
				</div>
			</div>
			<!-- PAGE CONTENT - END -->
EOD;
	}
	
	public function set_title() {
		$this->title = "Armazenamento";
	}
}

?>