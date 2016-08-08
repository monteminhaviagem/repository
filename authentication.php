<?php

header('Content-Type: text/html; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common_google."/API.inc");
require_once($path_module_admin_access."/dm/User.inc");
require_once($path_module_admin_access."/controller/Session.inc");

use module\admin\access\dm\User;
use module\admin\access\controller\Session;

function unauthorized($message = "", $email = "") {
	echo <<<EOD
		<html>
			<body onload="document.getElementById('login').submit()">
				<form id='login' method='POST' action='/login'>
					<input type='hidden' name='message' value='{$message}'/>
					<input type='hidden' name='email' value='{$email}'/>
				</form>
			</body>
		</html>
}
EOD;
}

function authorized($session) {
	session_start();
	
	$_SESSION['id'] = $session["id"];
	$_SESSION['token'] = $session["token"];
	$_SESSION['user_id'] = $session["user_id"];
	$_SESSION['profile_id'] = $session["profile_id"];
	$_SESSION['user_type_id'] = $session["user_type_id"];
	$_SESSION['page_type_id'] = $session["page_type_id"];
	
	echo <<<EOD
		<html>
			<head>
				<script type="text/javascript">
					document.location = "/";
				</script>
			</head>
		</html>
EOD;
}

function local() {
	$email = $_POST["email"] ?? "";
	$password = $_POST["password"] ?? "";
	
	if (($email == "") || ($password == "")) {
		unauthorized("Preencher E-mail e Password.", $email);
		return;
	}
	
	$data["get_user_email"] = array();
	$args["get_user_email"] = array();
	$args["get_user_email"]["email"] = $email;
	
	$dm = new User();
	$dm->get_user_email(
		$args["get_user_email"],
		$data["get_user_email"]
	);
	
	if (empty($data["get_user_email"]["id"])) {
		unauthorized("Usuário não cadastrado. Clique aqui para realizar o cadastro.", $email);
		return;
	}
	
	$data["get_user_credential"] = array();
	$args["get_user_credential"] = array();
	$args["get_user_credential"]["email"] = $email;
	$args["get_user_credential"]["password"] = md5($password);
	
	$dm = new User();
	$dm->get_user_credential(
		$args["get_user_credential"],
		$data["get_user_credential"]
	);
	
	if (empty($data["get_user_credential"]["id"])) {
		unauthorized("Senha inválida. Clique aqui para alterar a senha.", $email);
		return;
	}
	
	$controller = new Session();
	$controller->create_session(
		$data["get_user_credential"]["id"],
		1,
		$stat
	);
		
	if ($stat["success"] == "false") {
		unauthorized($stat["message"], $email);
		return;
	}
	
	authorized($stat["session"]);
}

function google() {
	$authentication = $_GET;
	
	if (isset($authentication["error"])) {
		unauthorized("Falha na autenticação do Google");
		return;
	}
	
	$mod = new API();
	
	$token = json_decode($mod->get_token($authentication["code"]), true);
	
	if (isset($token["error"])) {
		unauthorized($token["error_description"]);
		return;
	}
	
	$userinfo = json_decode($mod->get_userinfo($token["access_token"]), true);
	
	if (isset($userinfo["error"])) {
		unauthorized("Falha na autenticação do Google");
		return;
	}
	
	$data["get_user_email"] = array();
	$args["get_user_email"] = array();
	$args["get_user_email"]["email"] = $userinfo["email"];
	
	$dm = new User();
	$dm->get_user_email(
		$args["get_user_email"],
		$data["get_user_email"]
	);
	
	if (empty($data["get_user_email"]["id"])) {
		$stat["set_user"] = array();
		$data["set_user"] = array();
		$data["set_user"]["id"] = null;
		$data["set_user"]["name"] = $userinfo["name"];
		$data["set_user"]["email"] = $userinfo["email"];
		$data["set_user"]["password"] =null;
		$data["set_user"]["profile_id"] = 2;
		$data["set_user"]["last_updated"] = 1;
		$data["set_user"]["ip"] = $_SERVER["REMOTE_ADDR"] ?? "0.0.0.0";
		
		$dm = new User();
		$dm->set_user(
			$data["set_user"],
			$stat["set_user"]
		);
		
		if ($stat["set_user"]["success"] == "false") {
			unauthorized($stat["set_user"]["message"]);
			return;
		}
		
		$user_id = $stat["set_user"]["id"];
	}
	else
		$user_id = $data["get_user_email"]["id"];
	
	$controller = new Session();
	$controller->create_session(
		$user_id,
		2,
		$stat
	);
	
	if ($stat["success"] == "false") {
		unauthorized($stat["message"], $email);
		return;
	}
	
	authorized($stat["session"]);
}

$args = array();
$data = array();
$stat = array();

if (count($_POST))
	local();
else
	google();

?>