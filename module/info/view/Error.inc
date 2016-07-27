<?php
namespace module\info\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
//require_once($path_module_common."/Handler.inc");
require_once($path_module_common."/Page.inc");

use module\common\Page;

class Error extends Page {
	
	const ID = '1bb56fee46e5f195f5d535bbf8b27179';
	
	const FATAL_ERROR = 1;
	const ACCESS_DENIED = 2;
	const PAGE_NOT_FOUND = 3;
	
	protected $message_title;
	protected $message_description;
	
	public function __construct($type = 1) {
		parent::__construct();
		
		if ($type == Error::FATAL_ERROR) {
			$this->message_title = "505 - Erro";
			$this->message_description = "Sorry, an error has occured, Requested page not found!";
		}
		else if ($this->type == Error::ACCESS_DENIED) {
			$this->message_title = "Acesso Negado";
			$this->message_description = "Sorry, an error has occured, Requested page not found!";
		}
		else {
			$this->message_title = "404 - Página não Encontrada";
			$this->message_description = "Sorry, an error has occured, Requested page not found!";
		}
	}
	
	public function get_css_page() {
		return array(
			"bootstrap.css",
		);
	}
	
	public function get_css() {
		return <<<EOD
			body {
				background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAALEgAACxIB0t1+/AAAABZ0RVh0Q3JlYXRpb24gVGltZQAxMC8yOS8xMiKqq3kAAAAcdEVYdFNvZnR3YXJlAEFkb2JlIEZpcmV3b3JrcyBDUzVxteM2AAABHklEQVRIib2Vyw6EIAxFW5idr///Qx9sfG3pLEyJ3tAwi5EmBqRo7vHawiEEERHS6x7MTMxMVv6+z3tPMUYSkfTM/R0fEaG2bbMv+Gc4nZzn+dN4HAcREa3r+hi3bcuu68jLskhVIlW073tWaYlQ9+F9IpqmSfq+fwskhdO/AwmUTJXrOuaRQNeRkOd5lq7rXmS5InmERKoER/QMvUAPlZDHcZRhGN4CSeGY+aHMqgcks5RrHv/eeh455x5KrMq2yHQdibDO6ncG/KZWL7M8xDyS1/MIO0NJqdULLS81X6/X6aR0nqBSJcPeZnlZrzN477NKURn2Nus8sjzmEII0TfMiyxUuxphVWjpJkbx0btUnshRihVv70Bv8ItXq6Asoi/ZiCbU6YgAAAABJRU5ErkJggg==);
			}
			.error-template {
				padding: 40px 15px;
				text-align: center;
			}
			.error-actions {
				margin-top: 15px;
				margin-bottom: 15px;
			}
			.error-actions .btn {
				margin-right: 10px;
			}
EOD;
	}
	
	public function get_content() {
		
		
		return <<<EOD
			<div class="container">
				<div class="row">
					<div class="col-md-12">
						<div class="error-template">
							<h1>Oops!</h1>
							<h2>{$this->message_title}</h2>
							<div class="error-details">{$this->message_description}</div>
							<div class="error-actions">
								<a href="/" class="btn btn-primary btn-lg"><span class="glyphicon glyphicon-home"></span>vTake Me Home </a>
								<a href="/" class="btn btn-default btn-lg"><span class="glyphicon glyphicon-envelope"></span> Contact Support</a>
							</div>
						</div>
					</div>
				</div>
			</div>
EOD;
	}
	
	public function set_title() {
		$this->title = $this->message_title;
	}
}

?>