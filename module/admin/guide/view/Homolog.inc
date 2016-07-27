<?php
namespace module\admin\guide\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_guide."/controller/Guide.inc");

use module\admin\Admin;
use module\admin\guide\controller\Guide;

class Homolog extends Admin {
	
	const ID = 'c5c7455f872de05f4a2c6a296df90c19';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_content() {
		$controller = new Guide();
		$file_info = $controller->get_content("info_homolog.txt");
		$file_config = $controller->get_content("config_homolog.txt");
		$file_ftp = $controller->get_content("ftp_homolog.txt");
		$file_mysql = $controller->get_content("mysql_homolog.txt");
		$file_apache = $controller->get_content("apache.txt");
		$file_php = $controller->get_content("php.txt");
		$file_git = $controller->get_content("git_homolog.txt");
		
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="container-fluid">
					<div class="row">
						<div class="col-lg-12">
							<h1 class="page-header">Homologação</h1>
						</div>
					</div>
					
					<!-- BEGIN TAB -->
					<div class="panel-body">
						<ul class="nav nav-tabs">
							<li class="active"><a href="#info" data-toggle="tab"><i class="fa fa-info"></i> Info</a></li>
							<li><a href="#config" data-toggle="tab"><i class="fa fa-cog"></i> Configuração</a></li>
							<li><a href="#ftp" data-toggle="tab"><i class="fa fa-upload"></i> FTP</a></li>
							<li><a href="#mysql" data-toggle="tab"><i class="fa fa-database"></i> MySQL</a></li>
							<li><a href="#apache" data-toggle="tab"><i class="fa fa-cogs"></i> Apache</a></li>
							<li><a href="#php" data-toggle="tab"><i class="fa fa-code"></i> PHP</a></li>
							<li><a href="#git" data-toggle="tab"><i class="fa fa-code-fork"></i> Git</a></li>
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
							
							<div class="tab-pane fade" id="mysql">
								<div class="header">
									<a href="/module/admin/guide/download/mysql_prod.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<br>
								<pre>{$file_mysql}</pre>
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
							
							<div class="tab-pane fade" id="php">
								<div class="header">
									<a href="/module/admin/guide/download/php.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<br>
								<pre>{$file_php}</pre>
							</div>
							
							<div class="tab-pane fade" id="git">
								<div class="header">
									<a href="/module/admin/guide/download/git_homolog.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<br>
								<pre>{$file_git}</pre>
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
		$this->title = "Homologação";
	}
}

?>