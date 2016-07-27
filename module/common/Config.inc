<?php
namespace module\common;

class Config {
	// ENV_DEVELOPMENT
	const D_DB_HOST = '127.0.0.1';
	const D_DB_PORT = '3306';
	const D_DB_USER = 'mmv';
	const D_DB_PASS = '?ddb01@mmv!';
	const D_DB_NAME = 'mmv';
	
	// ENV_HOMOLOG
	const H_DB_HOST = '127.0.0.1';
	const H_DB_PORT = '3306';
	const H_DB_USER = 'mmv';
	const H_DB_PASS = '?hdb01@mmv!';
	const H_DB_NAME = 'mmv';
	
	// ENV_PRODUCTION
	const P_DB_HOST = '127.0.0.1';
	const P_DB_PORT = '3306';
	const P_DB_USER = 'mmv';
	const P_DB_PASS = '?pdb01@mmv!';
	const P_DB_NAME = 'mmv';
	
	const ENV_DEVELOPMENT = 1;
	const ENV_HOMOLOG = 2;
	const ENV_PRODUCTION = 3;
	
	public static function get_environment() {
		if (gethostname() == "mmv-prod-01")
			return Config::ENV_PRODUCTION;
		else if (gethostname() == "mmv-homolog-01")
			return Config::ENV_HOMOLOG;
		else
			return Config::ENV_DEVELOPMENT;
	}
}

?>
