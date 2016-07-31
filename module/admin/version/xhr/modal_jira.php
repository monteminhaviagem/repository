<?php

session_start();

if (!isset($_SESSION['user_id']))
	return;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Security.inc");

use module\common\Security;

$load_args = array();
$load_data = array();

$load_args["user"] = array();
$load_data["user"] = array();

$load_args["profile"] = array();
$load_data["profile"] = array();

$return = <<<EOD
<!-- BEGIN MODAL-HEADER -->
<div class="modal-header">
	<button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
	<h4 class="modal-title">JIRA ISSUES</h4>
</div>
<!-- END MODAL-HEADER -->

<!-- BEGIN MODAL-BODY -->
<div class="modal-body">
	<form class="form-inline">
		<div class="form-group">
			<select class="form-control" id="board_id" name="board_id" disabled>
				<option value="">BOARD</option>
			</select>
		</div>
		<div class="form-group">
			<select class="form-control" id="sprint_id" name="sprint_id" disabled>
				<option value="">SPRINT</option>
			</select>
		</div>
		<hr>
		<div class="jira-issues"><div class="panel-group" id="accordion"></div></div>
	</form>
</div>
<!-- END MODAL-BODY -->

<!-- BEGIN MODAL-FOOTER -->
<div class="modal-footer">
	<button type="button" class="btn btn-outline btn-primary" data-dismiss="modal">Fechar</button>
</div>
<!-- END MODAL-FOOTER -->
EOD;

echo $return;

?>