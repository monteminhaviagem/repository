<?php
namespace module\admin\guide\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_admin."/Admin.inc");

use module\admin\Admin;

class Program extends Admin {
	
	const ID = '9355b5016beabc840dda54cc7f4e643d';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {}
	
	public function get_js_page() {}
	
	public function get_js() {}
	
	public function get_content() {
		return <<<EOD
			<!-- PAGE CONTENT - BEGIN -->
			<div id="page-wrapper">
				<div class="container-fluid">
					<div class="row">
						<div class="col-lg-12">
							<h1 class="page-header">Programas</h1>
						</div>
					</div>
					
					<table class="table table-striped">
						<thead>
							<tr>
								<th><i class="fa fa-cog"></i> Programa</th>
								<th><i class="fa fa-code-fork"></i> Versão</th>
								<th><i class="fa fa-gears"></i> Plataforma</th>
								<th><i class="fa fa-download"></i> Download</th>
							</tr>
						</thead>
						<tbody>
							<tr>
								<td>Oracle VM VirtualBox</td>
								<td>5.0.16</td>
								<td>Windows (32-bit/64-bit)</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/VirtualBox-5.0.16-105871-Win.exe" target="_blank">Repositório</a> |
									<a href="http://www.oracle.com/technetwork/server-storage/virtualbox/downloads/index.html" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>Ubuntu Server</td>
								<td>14.04.4 LTS</td>
								<td>Linux</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/ubuntu-14.04.4-server-amd64.iso" target="_blank">Repositório</a> |
									<a href="http://www.ubuntu.com/download/server" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>Eclipse for PHP Developers</td>
								<td>Mars 2</td>
								<td>Windows (32-bit)</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/eclipse-php-mars-2-win32.zip" target="_blank">Repositório</a> |
									<a href="http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/mars/2/eclipse-php-mars-2-win32.zip" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>Eclipse for PHP Developers</td>
								<td>Mars 2</td>
								<td>Windows (64-bit)</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/eclipse-php-mars-2-win32-x86_64.zip" target="_blank">Repositório</a> |
									<a href="http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/mars/2/eclipse-php-mars-2-win32-x86_64.zip" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>mRemoteNG</td>
								<td>1.72</td>
								<td>Windows</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/mRemoteNG-Installer-1.72.exe" target="_blank">Repositório</a> |
									<a href="http://www.mremoteng.org/download" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>MySQL Workbench</td>
								<td>6.3.6</td>
								<td>Windows</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/mysql-workbench-community-6.3.6-win32.msi" target="_blank">Repositório</a> |
									<a href="http://dev.mysql.com/downloads/workbench/" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>FileZilla</td>
								<td>3.16.1</td>
								<td>Windows (32bit)</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/FileZilla_3.16.1_win32-setup.exe" target="_blank">Repositório</a> |
									<a href="https://filezilla-project.org/download.php?type=client" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>Bizagi Modeler</td>
								<td>3.0.0.022</td>
								<td>Windows (64bit)</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/BizagiModelerSetup_x64.exe" target="_blank">Repositório</a> |
									<a href="http://www.bizagi.com/pt/produtos/bpm-suite/modeler" target="_blank">Site Oficial</a>
								</td>
							</tr>
							<tr>
								<td>Erwin Data Modeler</td>
								<td>7.3</td>
								<td>Windows</td>
								<td>
									<a href="http://192.241.154.151/programas/desktop/erwin-data-modeler-7.3.rar" target="_blank">Repositório</a>
								</td>
							</tr>
						</tbody>
					</table>
				</div>
			</div>
			<!-- PAGE CONTENT - END -->
EOD;
	}
	
	public function set_title() {
		$this->title = "Programas";
	}
}

?>