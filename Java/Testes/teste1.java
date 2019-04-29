import java.util.Scanner;

public class teste1 {
    
    public static void main(String args[]){
        
        int i;
        String palavra;
        
        Scanner input = new Scanner(System.in);
        
        palavra = input.nextLine();
        
        for(i = 0; i < palavra.length(); i++){
            
            System.out.printf(palavra.charAt(i) + " ");
         
        }
    }
}