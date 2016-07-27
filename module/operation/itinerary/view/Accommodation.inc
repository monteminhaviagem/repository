<?php
namespace module\operation\itinerary\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_operation_itinerary."/Itinerary.inc");

use module\operation\itinerary\Itinerary;

class Accommodation extends Itinerary {
	
	const ID = 'cad9d900b73be478c9502bd4f7781b87';
	
	public function __construct() {
		session_start();
		
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {}
	
	public function get_js_page() {
		return array(
			"jquery.js",
			"functions.js"
		);
	}
	
	public function get_js() {}
	
	public function get_content() {
		global $path_url_img_itinerary;
		
		return <<<EOD
<div id="pagewrap">
			<section id="middle">
				<h2>HOSPEDAGENS</h2>					
					
				<fieldset class="catSelected">
					<legend>Características Selecionad</legend>
					<ul class="catList">
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /><br />Wi-Fi</li>
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /><br />Piscina</li>
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /><br />Praias</li>
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /><br />Transportes</li>
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /><br />TV</li>
					</ul>
				</fieldset>					
					
				<fieldset class="category">
					<legend>Categoria</legend>
					<ul class="catList">
						<li>
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							Wi-Fi
						</li>
						<li>
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							Praias						
						</li>
						<li style="background-color : rgb(200,255,200);">
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							Piscina				
						</li>
						<li>
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							Transportes Públicos
						</li>						
						<li>
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							TV	
						</li>
						<li>
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							Ar Condicionado
						</li>
						<li>
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							Cofre					
						</li>						
						<li style="background-color : rgb(200,255,200);">
							<img src="$path_url_img_itinerary/teste1.png" /><br />
							Cofre					
						</li>						
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>											
					</ul>
				</fieldset>
				<br />
				<fieldset class="category">
					<legend>Conforto</legend>
					<ul class="catList">
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>						
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
					</ul>
				</fieldset>
				<br />
				<fieldset class="category">
					<legend>Serviços</legend>
					<ul class="catList">
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>						
						<li style="background-color : rgb(200,255,200);"><$path_url_img_itinerary src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
					</ul>
				</fieldset>				
				<br />
				<fieldset class="category">
					<legend>Proximidade</legend>
					<ul class="catList">
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>						
						<li style="background-color : rgb(200,255,200);"><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
						<li><img src="$path_url_img_itinerary/teste1.png" /></li>
					</ul>
				</fieldset>				
			</section>

			<section id="content"></section>

			<aside id="sidebar">

				<h2>RESUMO</h2>
				
				<h4>ORIGEM</h4>
				<div class="itemCart">
					Santo André - SP
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>
				
				<h4>DESTINOS</h4>
				<div class="itemCart">
					Roma, Itália
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>
				<div class="itemCart">
					Praga, República Tcheca
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>
				
				<h4>PERÍODO</h4>
				<div class="itemCart">
					De: <strong>21/10/2016</strong> à <strong>26/10/2016</strong>
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>
				
				<h4>PASSAGEIROS</h4>
				<h4>HOSPEDAGEM</h4>
				<div class="itemCart">
					Wi-Fi
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>	
				<div class="itemCart">
					Próximo à Praias
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>
				<div class="itemCart">
					Piscina
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>
				<div class="itemCart">
					Próximo à Transportes Públicos
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>				
				<div class="itemCart">
					TV
					<img src="$path_url_img_itinerary/delete-item.png" />
				</div>				
				<h4>AÉREO</h4>
				<h4>SERVIÇOS</h4>
				<h4>INFORMAÇÕES</h4>
			</aside>		
			
		</div>
EOD;
	}
	
	public function set_title() {
		$this->title = "Hospedagem";
	}
}

?>