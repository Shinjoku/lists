import java.util.Scanner;
import java.util.Random;

public class Jogo{
	
	//Utilitários:
	Scanner input = new Scanner(System.in);
	int escolha;

	//Constructor:
	Jogo() {
		menu();
	}
	
	// Recebe um valor do usuário, que define a dificuldade do jogo
	public void menu(){
		
		
		System.out.println("Digite a dificuldade (0 - Fácil, 1 - Difícil:");
		
		escolha = input.nextInt();
		
		int tam = 0, lim = 0;
		
		switch(escolha){
			case 0:
				tam = 4;
				lim = 8;
				break;
				
			case 1:
				tam = 8;
				lim = 12;
				break;
			default:
				break;
		}
		
		Senha senha = new Senha(tam);
		senha.randomSenha(tam);
		
		//Debugger------------------------------
		senha.printResposta();
		//Debugger------------------------------
		
		start(tam, 0, lim, senha);
	}
	
	// Inicializa o jogo
	public void start(int tam, int rodada, int lim, Senha senha){
		
		int debug, i;
		
		if(rodada != lim){
			//Vetores:

			int[] entrada = new int[tam];
			int[] pontos = new int[tam];
			
			//Ints:
			int total = 0;
			

			System.out.println("Digite as entradas:");
			//Recebe entrada do usuário e já pontua a rodada:
			for(i = 0; i < entrada.length; i++){
				
				entrada[i] = input.nextInt();
				
				debug = senha.verificaSenha(entrada[i], i);
				
				System.out.printf(debug + " ");

				total += debug;
			}
			
			System.out.println("\n");
			
			if(total == tam * 2){
				System.out.println("VENCEU!");
			}
			else{
				start(tam, rodada + 1, lim, senha);
			}
		}
		else{
			System.out.println("PERDEU!");
		}
	}
}