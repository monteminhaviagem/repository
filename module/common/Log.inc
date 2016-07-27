<?php
namespace module\common;

$DOCUMENT_ROOT = $_SERVER["DOCUMENT_ROOT"];

class Log {
	public function save($message, $file, $method, $line) {
		global $DOCUMENT_ROOT;
		
		$date = date("Ymd");
		$hour = date("H:i:s");
		$ip = $_SERVER['REMOTE_ADDR'] ?? "0.0.0.0";
		
		$log_file_name = "{$DOCUMENT_ROOT}/repository/log/{$date}.log";
		
		$log = "[{$hour}][{$ip}]";
		
		if ($file != "")
			$log .= "[{$file}]";
		
		if ($method != "")
			$log .= "[{$method}]";
		
		if ($line != "")
			$log .= "[{$line}]";
		
		$log .= "> $message \n";
		
		$log_file = fopen("{$log_file_name}", "a+b");
		fwrite($log_file, $log);
		fclose($log_file);
	}
}

?>