<?php
namespace module\info\view;

require_once($_SERVER["DOCUMENT_ROOT"] . "/path.php");
require_once($path_module_common."/Handler.inc");
require_once($path_module_info."/Info.inc");

use module\info\Info;

class Home extends Info {
	
	const ID = '076455825bc60d16762bf604b02fa7bc';
	
	public function __construct() {
		parent::__construct($this::ID);
	}
	
	public function get_css_page() {
		return array(
			"info-global.css"
		);
	}
	
	public function get_js_page() {}
	
	public function get_css() {}
	
	public function get_js() {}
	
	public function get_header() {}
	
	public function get_content() {
		global $path_url_repository_img;
		global $path_url_repository_info_img;
		
		
		return <<<EOD

		<div id="header">
            <div class="content">
                <div>        
                    <img src="{$path_url_repository_img}/abadar_logo.png" style="width:75px; float:left;" />
                </div>                 
                <div style="float:left; height:75px; padding-top:10px; padding-left:5px;">        
                    <font style="font-size:30px;">ABADAR</font> <br />
                    A maneira mais fácil de montar sua viagem.
                </div>
                <div style="float:right;">        
                    <button class="login" style="width:100px; margin-top: 15px;" onclick="document.location = '/login'">Login</div>
                </div>                                   

            </div>
        </div>					
		
        <section class="background" style="background-image:url('{$path_url_repository_info_img}/bgsaofrancisco.jpg');">
		    <div class="opcty">
                <div class="content2">
                    <h1>
                        <strong style="font-size : 70px; color: rgb(255,255,255);">Não consulte,</strong> <br />
                        <span style="font-size : 90px; color: rgb(255,255,255);">VIAJE!</span> 
                        <br />
                        <br />
                        Pense em sua viagem ou apenas nos diga seus desejos.
                        <br />
                        <br />
                        Receba diversas indicações e preços de milhares de agentes.
                        <br />
                        <br />
                        Escolha a melhor!
                        <br />
                        <br />                        
                            <input type="text" style="border-radius: 5px; 
                                                      -moz-border-radius: 5px; 
                                                      -webkit-border-radius: 5px; 
                                                      border: 1px solid #C2B8D9;
                                                      height : 39px; 
                                                      font-size:22px; 
                                                      font-weight:normal; 
                                                      color:rgb(140,140,140);
                                                      padding: 0px 15px 4px 15px;
                                                      width : 350px;" value="Seu e-mail"/>
                            <button class="cadastro" onclick="document.location = '/registration'">Cadastre-se</button>                                                   
                    </h1>
                <div>        
		    </div>
        </section>            		
				
		
EOD;
	}
	
	public function get_footer() {}
	
	public function set_title() {
		$this->title = "Abadar - Monte sua Viagem";
	}
}

?>