package joc_Cartes;

public class Cartes {
	private String tipus;
	private int numero;
	private String material = "papel";
	private String [] pals = {"ors","bastos","espases","copes"};
	
	public Cartes(String tipus, int numero){
		
		//assert(numero > 0 && numero < 13);
		if(numero > 0 && numero < 13){
			this.numero = numero;
		}
		else{
			System.err.println("Valor " + numero + " incorrecte!");
		}
		boolean tipusOK = false;
		for (int i=0;i<4;i++){
			if (tipus.equals(pals[i])){
				tipusOK = true;
			}
		}
		
		if (tipusOK){
			this.tipus = tipus;
		}
		else{
			System.err.println("Tipus " + tipus + " incorrecte!");
		}
		
	}
	
	public void Mostra(){
		System.out.println(CrearStringParaMostrar());
	}
	
	private String CrearStringParaMostrar(){
		
		String numeroConLetras = ""; 
		
		switch(numero)
		{
			case 1:
				numeroConLetras = "uno";
				break;
			case 2:
				numeroConLetras = "dos";
				break;
			case 3:
				numeroConLetras = "tres";
				break;
			case 4:
				numeroConLetras = "cuatro";
				break;
			default:
				numeroConLetras = "otronumero";
				break;
		}
		
		return numeroConLetras + " de " + tipus + ". Material de la carta: "+ material;
	}
}
