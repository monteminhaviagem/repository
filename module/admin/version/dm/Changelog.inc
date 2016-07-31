<?php
namespace module\admin\version\dm;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_common."/Database.inc");

use PDO;
use module\common\Log;
use module\common\Database;

class Changelog extends Database {
	
	protected $log;
	
	public function __construct($connection = "", $close_flag = true) {
		parent::__construct($connection, $close_flag);
		
		$this->db_open();
		$this->log = new Log();
	}
	
	public function get_changelog($args, &$data) {
		$data = array();
		$order = (isset($args["order"]) && $args["order"] != "") ? $args["order"] : 'version_changelog.id';
		
		$sql = "
			select version_changelog.id,
			       version_changelog.version_id,
			       version.tag,
			       version_changelog.issue_id,
			       version_changelog.issue_key,
			       version_changelog.issue_summary,
			       version_changelog.issue_description
			  from version_changelog,
			       version
			 where version_changelog.version_id = version.id
			 order by $order";
		
		$rs = $this->connection->prepare($sql);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data[] = array(
						'id' => $row->id,
						'version_id' => $row->version_id,
						'tag' => $row->tag,
						'issue_id' => $row->issue_id,
						'issue_key' => $row->issue_key,
						'issue_summary' => $row->issue_summary,
						'issue_description' => $row->issue_description
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function get_changelog_id($args, &$data) {
		$data = array();
		
		$sql = "
			select version_changelog.id,
			       version_changelog.version_id,
			       version.tag,
			       version_changelog.issue_id,
			       version_changelog.issue_key,
			       version_changelog.issue_summary,
			       version_changelog.issue_description,
			       version_changelog.created,
			       version_changelog.modified,
			       version_changelog.last_updated,
			       user.name last_updated_name,
			       version_changelog.ip
			  from version_changelog,
			       version,
			       user
			 where version_changelog.version_id = version.id
			   and version_changelog.last_updated = user.id
			   and version_changelog.id = :version_changelog_id";
		
		$rs = $this->connection->prepare($sql);
		$rs->bindParam(':version_changelog_id', $args["id"]);
		
		if ($rs->execute()) {
			if ($rs->rowCount() > 0) {
				while ($row = $rs->fetch(PDO::FETCH_OBJ)) {
					$data = array(
						'id' => $row->id,
						'version_id' => $row->version_id,
						'tag' => $row->tag,
						'issue_id' => $row->issue_id,
						'issue_key' => $row->issue_key,
						'issue_summary' => $row->issue_summary,
						'issue_description' => $row->issue_description,
						'created' => strtotime($row->created),
						'modified' => strtotime($row->modified),
						'last_updated' => $row->last_updated,
						'last_updated_name' => $row->last_updated_name,
						'ip' => $row->ip
					);
				}
			}
		}
		else{
			$this->log->save("Statement => " . print_r($rs->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
		}
	}
	
	public function set_changelog(&$data, &$stat) {
		if (is_null($data["id"])) {
			$st_insert = $this->connection->prepare("insert into version_changelog (version_id, issue_id, issue_key, issue_summary, issue_description, created, modified, last_updated, ip) values (:version_id, :issue_id, :issue_key, :issue_summary, :issue_description, now(), now(), :last_updated, :ip)");
			$st_insert->bindParam(':version_id', $data["version_id"]);
			$st_insert->bindParam(':issue_id', $data["issue_id"]);
			$st_insert->bindParam(':issue_key', $data["issue_key"]);
			$st_insert->bindParam(':issue_summary', $data["issue_summary"]);
			$st_insert->bindParam(':issue_description', $data["issue_description"]);
			$st_insert->bindParam(':last_updated', $data["last_updated"]);
			$st_insert->bindParam(':ip', $data["ip"]);
			
			if (!$st_insert->execute()) {
				$this->log->save("Statement => " . print_r($st_insert->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_insert->errorInfo();
				return;
			}
			
			$stat["id"] = $this->connection->lastInsertId();
		}
		else {
			$st_update = $this->connection->prepare("update version_changelog set issue_summary = :issue_summary, issue_description = :issue_description, modified = now(), last_updated = :last_updated, ip = :ip where id = :id");
			$st_update->bindParam(':issue_summary', $data["issue_summary"]);
			$st_update->bindParam(':issue_description', $data["issue_description"]);
			$st_update->bindParam(':last_updated', $data["last_updated"]);
			$st_update->bindParam(':ip', $data["ip"]);
			$st_update->bindParam(':id', $data["id"]);
			
			if (!$st_update->execute()) {
				$this->log->save("Statement => " . print_r($st_update->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
				
				$stat["success"] = "false";
				$stat["message"] = $st_update->errorInfo();
				return;
			}
			
			$stat["id"] = $data["id"];
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
	
	public function remove_changelog(&$data, &$stat) {
		$st_delete = $this->connection->prepare("delete from version_changelog where id = :id");
		$st_delete->bindParam(':id', $data["id"]);
		
		if (!$st_delete->execute()) {
			$this->log->save("Statement => " . print_r($st_delete->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			$this->log->save("Connection => " . print_r($this->connection->errorInfo(),true), __FILE__, __METHOD__, __LINE__);
			
			$stat["success"] = "false";
			$stat["message"] = $st_delete->errorInfo();
			return;
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
	}
}

?>