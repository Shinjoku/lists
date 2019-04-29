import java.util.Scanner;

public class E1113 {

	public static void main(String[] args) {
	    
	    //Criando o obj
		Scanner input;
		int x, y, i;
		
		input = new Scanner(System.in);
		
		do{
	        x = input.nextInt();
		    y = input.nextInt();
		    
		    		    
		    if(x < y)
		        System.out.println("Crescente");
		    else if(x == y)
		        break;
		    else
		        System.out.println("Decrescente");
		}while(x != y);
	}
}
