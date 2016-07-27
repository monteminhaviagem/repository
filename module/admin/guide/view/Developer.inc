<?php
namespace module\admin\guide\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");
require_once($path_module_admin_guide."/controller/Guide.inc");

use module\admin\Admin;
use module\admin\guide\controller\Guide;

class Developer extends Admin {
	
	const ID = '5277696be486b681ae5533ca5be76202';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_content() {
		$controller = new Guide();
		$file_pre = $controller->get_content("pre_dev.txt");
		$file_info = $controller->get_content("info_dev.txt");
		$file_config = $controller->get_content("config_dev.txt");
		$file_samba = $controller->get_content("samba.txt");
		$file_mysql = $controller->get_content("mysql_dev.txt");
		$file_apache = $controller->get_content("apache.txt");
		$file_php = $controller->get_content("php.txt");
		$file_git = $controller->get_content("git_dev.txt");
		
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="container-fluid">
					<div class="row">
						<div class="col-lg-12">
							<h1 class="page-header">Desenvolvimento</h1>
						</div>
					</div>
					
					<!-- BEGIN TAB -->
					<div class="panel-body">
						<ul class="nav nav-tabs">
							<li class="active"><a href="#info" data-toggle="tab"><i class="fa fa-info"></i> Info</a></li>
							<li><a href="#config" data-toggle="tab"><i class="fa fa-cog"></i> Configuração</a></li>
							<li><a href="#samba" data-toggle="tab"><i class="fa fa-folder"></i> Samba</a></li>
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
									<a href="/module/admin/guide/download/pre_dev.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<p>Pré-requisito</p>
								<pre>{$file_pre}</pre>
								
								<br>
								<p>Automatizada</p>
								<pre>echo mmv | sudo -S mkdir /home/mmv/script
sudo chown -R mmv:mmv /home/mmv/script
cd /home/mmv/script
wget -m --user "mmv" --password "?sos01@mmv!" -nd ftp://192.241.154.151/empresas/abadar/script/configure.sh -P /home/mmv/script
sudo chmod +x /home/mmv/script/configure.sh
./configure.sh</pre>
								<br>
								<div class="header">
									<a href="/module/admin/guide/download/config_dev.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<p>Manual</p>
								<pre>{$file_config}</pre>
							</div>
							
							<div class="tab-pane fade" id="samba">
								<p>Automatizada</p>
								<pre>./samba.sh</pre>
								<br>
								<div class="header">
									<a href="/module/admin/guide/download/samba.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<p>Manual</p>
								<pre>{$file_samba}</pre>
							</div>
							
							<div class="tab-pane fade" id="mysql">
								<p>Automatizada</p>
								<pre>./mysql.sh</pre>
								<br>
								<div class="header">
									<a href="/module/admin/guide/download/mysql_dev.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<p>Manual</p>
								<pre>{$file_mysql}</pre>
							</div>
							
							<div class="tab-pane fade" id="apache">
								<p>Automatizada</p>
								<pre>./apache.sh</pre>
								<br>
								<div class="header">
									<a href="/module/admin/guide/download/apache.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<p>Manual</p>
								<pre>{$file_apache}</pre>
							</div>
							
							<div class="tab-pane fade" id="php">
								<p>Automatizada</p>
								<pre>./php.sh</pre>
								<br>
								<div class="header">
									<a href="/module/admin/guide/download/php.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<p>Manual</p>
								<pre>{$file_php}</pre>
							</div>
							
							<div class="tab-pane fade" id="git">
								<p>Automatizada</p>
								<pre>./git.sh</pre>
								<br>
								<div class="header">
									<a href="/module/admin/guide/download/git_dev.txt" target="_blank">
										<small class="pull-right text-muted"><i class="fa fa-download"></i> download</small>
									</a>
								</div>
								<p>Manual</p>
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
		$this->title = "Desenvolvimento";
	}
}

?>
