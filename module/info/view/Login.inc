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
	
	protected $email  = "";
	protected $message  = "";
	
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
			$(document).ready(function() {
				if ($("#message").html() != "")
					$("#message").show();
			});
			
			$("#local").click(function() {
				if ($("#email").val() == "") {
					$("#email").focus();
					$("#message").html("Preencher E-mail e Password.");
					$("#message").show();
					return false;
				}
				
				if ($("#password").val() == "") {
					$("#password").focus();
					$("#message").html("Preencher E-mail e Password.");
					$("#message").show();
					return false;
				}
				
				$("form").submit();
			});
			
			$("#google").click(function() {
				$.ajax({
					type: "POST",
					url: "/module/common/google/xhr/authentication.php",
					dataType: "json"
				})
				.done(function(data) {
					url = data.url;
					url += "?scope=" + encodeURIComponent(data.scope);
					url += "&state=" + encodeURIComponent(data.state);
					url += "&redirect_uri=" + encodeURIComponent(data.redirect_uri);
					url += "&response_type=" + encodeURIComponent(data.response_type);
					url += "&client_id=" + encodeURIComponent(data.client_id);
					
					document.location = url;
				});
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
								<form role="form" method="POST" action="/authentication.php">
									<input type="hidden" name="token" value="">
									<fieldset>
										<div class="form-group">
											<input class="form-control" placeholder="E-mail" id="email" name="email" type="email" value="{$this->email}" autofocus>
										</div>
										<div class="form-group">
											<input class="form-control" placeholder="Password" id="password" name="password" type="password" value="">
										</div>
										<div class="checkbox">
											<label>
												<input name="remember" type="checkbox" value="Remember Me">Remember Me
											</label>
										</div>
										<button type="button" id="local" class="btn btn-lg btn-success btn-block">Login</button>
										<button type="button" id="google" class="btn btn-lg btn-success btn-block">Google</button>
										
										<br>
										
										<div id="message" class="alert alert-warning" style="display: none;">{$this->message}</div>
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
		if (isset($_POST["email"]))
			$this->email = $_POST["email"];
		
		if (isset($_POST["message"]))
			$this->message = $_POST["message"];
	}
}

?>