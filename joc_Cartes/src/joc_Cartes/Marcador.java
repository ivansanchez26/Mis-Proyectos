package joc_Cartes;

public class Marcador {

	int puntos = 0;
	
	public Marcador(){
		
	}
	public void Sumar(int puntosASumar){
		puntos = puntos + puntosASumar;
	}
	public void Restar(int puntosARestar){
		puntos = puntos - puntosARestar;
	}
	public void MostrarPuntos(){
		System.out.println(puntos);
	}
}
