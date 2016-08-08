<?php

header('Content-Type: text/html; charset=utf-8');

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common_google."/API.inc");

$authentication = $_GET;

if (isset($authentication["error"])) {
	$error = "Falha na autenticação do Google";
}
else {
	$mod = new API();
	
	$token = json_decode($mod->get_token($authentication["code"]), true);
	
	if (isset($token["error"])) {
		$error = $token["error_description"];
	}
	else {
		$userinfo = json_decode($mod->get_userinfo($token["access_token"]), true);
		
		if (isset($userinfo["error"])) {
			$error = "Falha na autenticação do Google";
		}
		else {
			print_r($authentication);
			print_r($token);
			print_r($userinfo);
			return;
		}
	}
}

if ($error != "") {
	echo <<<EOD
	<html>
		<body onload="document.getElementById('login').submit()">
			<form id='login' method='POST' action='/login'>
				<input type='hidden' name='message' value='{$error}'/>
			</form>
		</body>
	</html>
EOD;
}

?>