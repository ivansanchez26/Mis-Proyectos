package joc_Cartes;
import java.util.Random;

public class Jugadors {
	private String nom;
	private Cartes [] ma;
	
	public Jugadors(String nom, int numCartes){
		this.nom = nom;
		ma = new Cartes[numCartes];
		
		GeneraCartes();
		
		
	}
	private String GeneraTipus(){
		String pals [] = {"bastos","copes","ors","espases"};
		Random rand = new Random();
		int index= rand.nextInt(4);
		
		return pals[index];
	}
	
	public void GeneraCartes(){
		Random rand = new Random();
		int num;
		String tipus;
		for(int i=0;i<ma.length;i++){
			num= rand.nextInt(12) + 1;
			tipus = GeneraTipus();
			ma[i] = new Cartes(tipus,num);
		}
		/*num= rand.nextInt(12) + 1;
		tipus = GeneraTipus();
		ma[0] = new Cartes(tipus,num);
		num= rand.nextInt(12) + 1;
		tipus = GeneraTipus();
		ma[1] = new Cartes(tipus,num);
		num= rand.nextInt(12) + 1;
		tipus = GeneraTipus();
		ma[2] = new Cartes(tipus,num);
		num= rand.nextInt(12) + 1;
		tipus = GeneraTipus();
		ma[3] = new Cartes(tipus,num);
		num= rand.nextInt(12) + 1;
		tipus = GeneraTipus();
		ma[4] = new Cartes(tipus,num);*/
		
	}
	
	public void MostraCartes() {
		System.out.println("Cartes del jugador " + nom);
		for (int i=0;i<ma.length;i++){
			ma[i].Mostra();
		}
	}
}
