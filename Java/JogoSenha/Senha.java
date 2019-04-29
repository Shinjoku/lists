import java.util.Random;

public class Senha{
	
	private int[] resposta;
	private Random generator = new Random();
	
	Senha(int tam){
		this.resposta = new int[tam];
	}
	
	public void printResposta(){
		
		System.out.println("Vetor de resposta:");
		for(int i : resposta){
			System.out.printf(i + " ");
		}
		System.out.println("\n");
	}
	
	//Gera vetor de resposta aleatório:
	public void randomSenha(int tam){
		for(int i = 0; i < tam; i++){
			resposta[i] = generator.nextInt(6);
		}
	}
	
	//Checa a validade da entrada do usuário
	public int verificaSenha(int entrada, int i){
		
		if(entrada == resposta[i]){		//Se acertou cor e posição
			return 2;
		}
		else{
			for(int j = 0; j < resposta.length; j++){
				if(entrada == resposta[j]){		//Se acertou cor
					return 1;
				}
			}
		}
		return 0;
	}
}
/*
int tentativa[] = tenta;
		contPreto = 0;
		contCinza = 0;

		if (senha.length == 4) {
			if (senha[0] == tentativa[0]) {
				contPreto++;
				tentativa[0] = -1;
				y++;
			} else {
				if (senha[0] == tentativa[1]) {
					contCinza++;
					tentativa[1] = -1;
					y++;
				} else {
					if (senha[0] == tentativa[2]) {
						contCinza++;
						tentativa[2] = -1;
						y++;
					} else {
						if (senha[0] == tentativa[3]) {
							contCinza++;
							tentativa[3] = -1;
							y++;
						}
					}
				}
			}

			if (senha[1] == tentativa[1]) {
				contPreto++;
				tentativa[1] = -1;
				y++;
			} else {
				if (senha[1] == tentativa[0]) {
					contCinza++;
					tentativa[0] = -1;
					y++;
				} else {
					if (senha[1] == tentativa[2]) {
						contCinza++;
						tentativa[2] = -1;
						y++;
					} else {
						if (senha[1] == tentativa[3]) {
							contCinza++;
							tentativa[3] = -1;
							y++;
						}
					}
				}
			}

			if (senha[2] == tentativa[2]) {
				contPreto++;
				tentativa[2] = -1;
				y++;
			} else {
				if (senha[2] == tentativa[0]) {
					contCinza++;
					tentativa[0] = -1;
					y++;
				} else {
					if (senha[2] == tentativa[1]) {
						contCinza++;
						tentativa[1] = -1;
						y++;
					} else {
						if (senha[2] == tentativa[3]) {
							contCinza++;
							tentativa[3] = -1;
							y++;
						}
					}
				}
			}

			if (senha[3] == tentativa[3]) {
				contPreto++;
				tentativa[3] = -1;
				y++;
			} else {
				if (senha[3] == tentativa[0]) {
					contCinza++;
					tentativa[0] = -1;
					y++;
				} else {
					if (senha[3] == tentativa[1]) {
						contCinza++;
						tentativa[1] = -1;
						y++;
					} else {
						if (senha[3] == tentativa[2]) {
							contCinza++;
							tentativa[2] = -1;
							y++;
						}
					}
				}
			}

			x++;

		}
		*/