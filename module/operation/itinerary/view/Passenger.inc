<?php
namespace module\operation\itinerary\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_operation_itinerary."/Itinerary.inc");
require_once($path_module_operation_itinerary."/controller/Passenger.inc");

use module\operation\itinerary\Itinerary;
use module\operation\itinerary\controller\Passenger;

class Passenger extends Itinerary {
	
	const ID = 'd4f36d5a931453883117fccac6cea8c3';
	
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
	
	public function get_js() {
		return <<<EOD
			$(document).ready(function() {});
		
			function changeQty (componente,quantidade) {
				var total = parseInt($(componente).html());
				
				total = total + quantidade;
				
				$(componente).html(total);
				
				if (componente == "#qtyAdulto")
					$("#adult").val(total);
				else if (componente == "#qtyCrianca")
					$("#child").val(total);
				else if (componente == "#qtyPet")
					$("#pet").val(total);
			}
				
			function next(url) {
				$.ajax({
					type: "POST",
					url: "/module/operation/itinerary/xhr/save_passenger.php",
					data: $("form").serialize(),
					dataType: "json"
				})
				.done(function(data) {
					if (data.success == "true")
						document.location = url;
					else
						alert(data.message);
				});
			}
EOD;
	}
	
	public function get_content() {
		//global $path_url_img_itinerary;
		
		//$passenger = array();
		
		//$controller = new Passenger();
		//$controller->get_data(1, $passenger); // Recuperar o profile_id da sessão
		
		return <<<EOD
		<div id="pagewrap">
			<form>
				<input type="hidden" name="itinerary_id" value="1" />
				<input type="hidden" id="adult" name="adult" value="{$passenger["passenger"]["adult"]}" />
				<input type="hidden" id="child" name="child" value="{$passenger["passenger"]["child"]}" />
				<input type="hidden" id="pet" name="pet" value="{$passenger["passenger"]["pet"]}" />
				
			<section id="middle">
				<h2>PASSAGEIRO</h2>
										
				<fieldset class="catSelected">
					<legend>Passageiros Selecionad</legend>

					<div style="font-size : 28px;">
						<span id="qtyAdulto">{$passenger["passenger"]["adult"]}</span> Adulto(s), <span id="qtyCrianca">{$passenger["passenger"]["child"]}</span> Criança, <span id="qtyPet">{$passenger["passenger"]["pet"]}</span> Pet
					</div>
					
				</fieldset>
										
				<fieldset class="category">
					<legend>Opções</legend>
					
					<table>
						<tr>
							<th>Adulto</th>
							<th>Criança</th>
							<th>Pet</th>
						</tr>
						<tr>
							<td valign="bottom">
								<img src="{$path_url_img_itinerary}/adulto2.png" />
							</td>
							<td valign="bottom">
								<img src="{$path_url_img_itinerary}/crianca.png" />					
							</td>							
							<td valign="bottom">
								<img src="{$path_url_img_itinerary}/pet.png" />
							</td>							
						<tr>
						<tr>
							<td valign="top">
								<img onclick="javascript:changeQty('#qtyAdulto',-1);" src="{$path_url_img_itinerary}/minus.png" />
								<img onclick="javascript:changeQty('#qtyAdulto',1);" src="{$path_url_img_itinerary}/plus.png" /></a>
							</td>
							<td valign="bottom">
								<img onclick="javascript:changeQty('#qtyCrianca',-1);" src="{$path_url_img_itinerary}/minus.png" />
								<img onclick="javascript:changeQty('#qtyCrianca',1);" src="{$path_url_img_itinerary}/plus.png" />
							</td>
							<td valign="bottom">
								<img onclick="javascript:changeQty('#qtyPet',-1);" src="{$path_url_img_itinerary}/minus.png" />
								<img onclick="javascript:changeQty('#qtyPet',1);" src="{$path_url_img_itinerary}/plus.png" />							
							</td>
						</tr>						
					</table>					

				</fieldset>
				
				<div style="text-align : left; width:100%; font-size: 14px;">					
					<a href="#">detalhar passageiros?</a>
				</div>
				
			</section>
						

			<section id="content"></section>

			<aside id="sidebar">

				<h2>RESUMO</h2>
				
				<h4>ORIGEM</h4>
				<div class="itemCart">
					Santo André - SP
					<img src="{$path_url_img_itinerary}/delete-item.png" />
				</div>
				
				<h4>DESTINOS</h4>
				<div class="itemCart">
					Roma, Itália
					<img src="{$path_url_img_itinerary}/delete-item.png" />
				</div>
				<div class="itemCart">
					Praga, República Tcheca
					<img src="{$path_url_img_itinerary}/delete-item.png" />
				</div>
				
				<h4>PERÍODO</h4>
				<div class="itemCart">
					De: <strong>21/10/2016</strong> à <strong>26/10/2016</strong>
					<img src="{$path_url_img_itinerary}/delete-item.png" />
				</div>
				
				<h4>PASSAGEIROS</h4>
				<h4>HOSPEDAGEM</h4>
				<h4>AÉREO</h4>
				<h4>SERVIÇOS</h4>
				<h4>INFORMAÇÕES</h4>
			</aside>		
			</form>
		</div>
EOD;
	}
	
	public function set_title() {
		$this->title = "Passageiros";
	}
}

?>