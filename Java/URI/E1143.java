import java.util.Scanner;

public class E1143 {

	public static void main(String[] args) {
	    
	    //Criando o obj
		Scanner input;
		int x, i;
		
		input = new Scanner(System.in);
		x = input.nextInt();
		
		for(i = 1; i <= x; i++)
		    System.out.println(i + " " + (int) Math.pow(i, 2.0) + " " + (int) Math.pow(i, 3));
	}
}

//Solved