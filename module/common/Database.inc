<?php
namespace module\common;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Config.inc");

use PDO;
use module\common\Config;

class Database {
	
	protected $host;
	protected $port;
	protected $name;
	protected $user;
	protected $pass;
	protected $string_connection;
	
	protected $connection;
	protected $close_flag;
	
	public function __construct($connection, $close_flag) {
		$this->connection = $connection;
		$this->close_flag = $close_flag;
		
		$environment = Config::get_environment();
		
		if ($environment == Config::ENV_DEVELOPMENT) {
			$this->host = Config::D_DB_HOST;
			$this->port = Config::D_DB_PORT;
			$this->name = Config::D_DB_NAME;
			$this->user = Config::D_DB_USER;
			$this->pass = Config::D_DB_PASS;
		}
		else if ($environment == Config::ENV_HOMOLOG) {
			$this->host = Config::H_DB_HOST;
			$this->port = Config::H_DB_PORT;
			$this->name = Config::H_DB_NAME;
			$this->user = Config::H_DB_USER;
			$this->pass = Config::H_DB_PASS;
		}
		else if ($environment == Config::ENV_PRODUCTION) {
			$this->host = Config::P_DB_HOST;
			$this->port = Config::P_DB_PORT;
			$this->name = Config::P_DB_NAME;
			$this->user = Config::P_DB_USER;
			$this->pass = Config::P_DB_PASS;
		}
		
		$this->string_connection = "mysql:host=".$this->host.";port=".$this->port.";dbname=".$this->name;
	}
	
	protected function db_open() {
		if (empty($this->connection)) {
			$this->connection = new PDO($this->string_connection, $this->user, $this->pass);
			$this->connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
			$this->connection->exec('set names utf8');
			$this->connection->exec('set time_zone = "-03:00"');
		}
		
		return true;
	}
	
	protected function db_close() {
		if ($this->connection)
			$this->connection = null;
	}
}

?>