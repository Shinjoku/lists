import java.util.Scanner;

public class carro{
	public static void main(String args[]){
		
		Hiunday hb20 = new Hiunday();
		
		hb20.ronco();
		hb20.acel();
		hb20.speed();
		System.out.println(hb20.marca);
	}
}

class Carros{
	
	int vel;
	String marca;
	
	public void acel(){
		this.vel++;
	}
	
	public void dec(){
		this.vel--;
	}
	
	public void speed(){
		System.out.println(this.vel);
	}
}


class Hiunday extends Carros{
	
	public Hiunday(){
		marca = "Hiunday"; 		//Agora funciona
		vel = 45;
	}
	
	public void ronco(){
		System.out.println("VRUUUUUUUUUM");
	}
}