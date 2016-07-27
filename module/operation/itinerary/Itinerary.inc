<?php
namespace module\operation\itinerary;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_operation."/Operation.inc");

use module\operation\Operation;
use module\operation\itinerary\view\Passenger;
use module\operation\itinerary\view\Accommodation;

class Itinerary extends Operation {
	protected $page_id;
	
	public function __construct($page_id) {
		parent::__construct($page_id);
		
		$this->page_id = $page_id;
	}
	
	public function get_js_common() {
		return array();
	}
	
	public function get_css_common() {
		return array(
			"roteiro.css"
		);
	}
	
	public function get_header() {
		return <<<EOD
			<div id="header">hh</div>
EOD;
	}
	
	public function get_footer() {
		global $path_url_img_itinerary;
		
		$next = "";
		$previous = "";
		
		if ($this->page_id == Passenger::ID) {
			$next = "/roteiro/hospedagem";
			$previous = "";
		}
		else if ($this->page_id == Accommodation::ID) {
			$next = "";
			$previous = "/roteiro/passageiro";
		}
		
		return <<<EOD
		<div id="footer">
			<div id="midContent">
				<div id="left">
					<a href="/roteiro/passageiro">Voltar</a>
					<div class="nomePagina">(Origem)</div>
				</div>
				<div id="mid">
					<img src="{$path_url_img_itinerary}/origem-t.png" />
					<img src="{$path_url_img_itinerary}/destino-ts2.png" />
					<img src="{$path_url_img_itinerary}/periodo-t.png" />
					<img src="{$path_url_img_itinerary}/passageiros-t.png" />
					<img src="{$path_url_img_itinerary}/hospedagem-t.png" />
					<img src="{$path_url_img_itinerary}/aereo-t.png" />
					<img src="{$path_url_img_itinerary}/servicos-t.png" />
					<img src="{$path_url_img_itinerary}/info-t.png" />
				</div>
				<div id="right">
					<a href="javascript:next('{$next}');">Avançar</a>
					<div class="nomePagina">(Período)</div>
				</div>			
			</div>
		</div>
EOD;
	}
}

?>