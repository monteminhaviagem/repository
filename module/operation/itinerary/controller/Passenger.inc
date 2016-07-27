<?php
namespace module\operation\itinerary\controller;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Log.inc");
require_once($path_module_operation_itinerary."/dm/Itinerary.inc");

use module\admin\access\dm\Itinerary;

class Passenger {
	
	public function __construct() {}
	
	public function get_data($itinerary_id = null, &$stat) {
		$args = array();
		$data = array();
		$stat = array();
		
		$adult = 0;
		$child = 0;
		$pet = 0;
		
		if (!is_null($itinerary_id)) {
			$args["id"] = $itinerary_id;
			
			$dm = new Itinerary();
			$dm->get_itinerary_id(
				$args,
				$data
			);
			
			$adult = $data["adult"];
			$child = $data["child"];
			$pet = $data["pet"];
		}
		
		$stat["success"] = "true";
		$stat["message"] = "";
		$stat["passenger"] = array();
		$stat["passenger"]["adult"] = $adult;
		$stat["passenger"]["child"] = $child;
		$stat["passenger"]["pet"] = $pet;
	}
}

?>