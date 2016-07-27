function changeQty (componente,quantidade) {
	
	var total = parseInt($(componente).html());
	
	total = total + quantidade;
	
	$(componente).html(total);

}
				
				