<?php
namespace module\info\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_info."/Info.inc");
require_once($path_module_admin_access."/controller/Session.inc");

use module\info\Info;
use module\admin\access\controller\Session;

class Login extends Info {
	
	const ID = '9194f5f3fd830b9c5af98978f9939036';
	
	protected $message  = "";
	protected $warning  = "";
	
	public function __construct() {
		parent::__construct($this::ID);
		
		$this->init();
	}
	
	public function get_css_page() {
		return array(
			"bootstrap.css",
			"metisMenu.css",
			"admin-global.css",
			"font-awesome.css"
		);
	}
	
	public function get_js_page() {
		return array(
			"jquery.js",
			"bootstrap.js",
			"metisMenu.js",
			"admin-global.js"
		);
	}
	
	public function get_css() {}
	
	public function get_js() {
		return <<<EOD
			$("button").click(function() {
				$("form").submit();
			});
EOD;
	}
	
	public function get_header() {}
	
	public function get_content() {
		return <<<EOD
			<div class="container">
				<div class="row">
					<div class="col-md-4 col-md-offset-4">
						<div class="login-panel panel panel-default">
							<div class="panel-heading">
								<h3 class="panel-title">Please Sign In</h3>
							</div>
							<div class="panel-body">
								<form role="form" method="POST">
									<input type="hidden" name="token" value="">
									<fieldset>
										<div class="form-group">
											<input class="form-control" placeholder="E-mail" name="email" type="email" autofocus>
										</div>
										<div class="form-group">
											<input class="form-control" placeholder="Password" name="password" type="password" value="">
										</div>
										<div class="checkbox">
											<label>
												<input name="remember" type="checkbox" value="Remember Me">Remember Me
											</label>
										</div>
										<button type="button" class="btn btn-lg btn-success btn-block">Login</button>
										
										<br>
										
										{$this->warning}
									</fieldset>
								</form>
							</div>
						</div>
					</div>
				</div>
			</div>
EOD;
	}
	
	public function get_footer() {}
	
	public function set_title() {
		$this->title = "Login";
	}
	
	private function init() {
		if (isset($_POST["token"])) {
			$stat = array();
			
			$email = $_POST["email"] ?? "";
			$password = $_POST["password"] ?? "";
			
			$controller = new Session();
			$controller->create_session(
				$email,
				$password,
				$stat
			);
			
			if ($stat["success"] == "false") {
				$this->message = $stat["message"];
			}
			else {
				session_start();
				
				$_SESSION['id'] = $stat["session"]["id"];
				$_SESSION['token'] = $stat["session"]["token"];
				$_SESSION['user_id'] = $stat["session"]["user_id"];
				$_SESSION['profile_id'] = $stat["session"]["profile_id"];
				$_SESSION['user_type_id'] = $stat["session"]["user_type_id"];
				$_SESSION['page_type_id'] = $stat["session"]["page_type_id"];
				
				header("Location: /");
			}
		}
		
		if ($this->message != "") {
			$this->warning = <<<EOD
				<div class="alert alert-warning">
					{$this->message}
				</div>
EOD;
		}
	}
}

?>