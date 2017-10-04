package joc_Cartes;

public class Joc_cartes {

	/*public static void main(String[] args){
		Jugadors j1 = new Jugadors("Pere",5);
		
		j1.MostraCartes();
	}
	*/
	
	public static void main(String[] args){
		Cartes c1 = new Cartes("ors", 7);
		Cartes c2 = new Cartes("espases", 3);
		Cartes c3 = new Cartes("copes", 1);
		
		c1.Mostra();
		c2.Mostra();
		c3.Mostra();
		
		Marcador m1 = new Marcador();
		m1.Sumar(25);
		m1.MostrarPuntos();
	}
}
