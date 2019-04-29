import java.util.Scanner;

public class E1133 {

	public static void main(String[] args) {
        
        //Criando obj;
        Scanner input = new Scanner(System.in);
        int x, i, y;
        
        x = input.nextInt();
        y = input.nextInt();
        
        for(i = x; i < y; i++)
            if(i % 5 == 2 || i % 5 == 3)
                System.out.println(i);
	}
}

//Solved